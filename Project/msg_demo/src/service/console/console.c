/***************************************************************************
 *   Copyright(C)2009-2012 by   xxxx xxxx<xxxxx@xxxxx.com>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include ".\app_cfg.h"

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
#define CONSOLE_BUF_SIZE        32

/*============================ MACROFIED FUNCTIONS ===========================*/
EXTERN_QUEUE(InOutQueue,uint8_t,uint8_t);

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
extern QUEUE(InOutQueue) g_tFIFOin;
extern QUEUE(InOutQueue) g_tFIFOout;

/*============================ LOCAL VARIABLES ===============================*/
const uint8_t c_chRN[]      = {'\r','\n'};
const uint8_t c_chpropmt[]  = {'\r','\n','>'};
const uint8_t c_chDelChar[] = {'\b',' ','\b'};

static uint8_t s_chCmdBuf[CONSOLE_BUF_SIZE] = {'\r','\n'};
static uint8_t s_chCmdBufIndex;

/*============================ PROTOTYPES ====================================*/
static fsm_rt_t console_print(const uint8_t *pchBuf,uint8_t chNum);
static fsm_rt_t console_check(void);

#define TASK_COSOLE_RESET() do{s_tState = TASK_CONSOLE_START;} while(0)
fsm_rt_t task_console(void)
{
    static enum {
        TASK_CONSOLE_START = 0,
        TASK_CONSOLE_PRT_CMD_PROMPT,
        TASK_CONSOLE_CHECK,
        TASK_CONSOLE_PARSE
    }s_tState;
    
    switch(s_tState) {
        case TASK_CONSOLE_START:
            s_chCmdBufIndex = 2;
            s_tState = TASK_CONSOLE_START;
            //break;
            
        case TASK_CONSOLE_PRT_CMD_PROMPT:
            if(fsm_rt_cpl == console_print(c_chpropmt,UBOUND(c_chpropmt))) {
                s_tState = TASK_CONSOLE_CHECK;
            }
            break;
            
        case TASK_CONSOLE_CHECK:
            if(fsm_rt_cpl == console_check() ){
                s_tState = TASK_CONSOLE_PARSE;
            }
            break;
        
        case TASK_CONSOLE_PARSE:
            if(fsm_rt_cpl == console_print(s_chCmdBuf,s_chCmdBufIndex)) {
                TASK_COSOLE_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}


#define COSOLE_CHECK_RESET() do{s_tState = CONSOLE_CHECK_START;} while(0)
static fsm_rt_t console_check(void)
{
    static uint8_t s_chTemp = 0;
    static uint8_t s_chNum  = 0;
    static uint8_t *s_pchPRT = NULL;
    static enum {
        CONSOLE_CHECK_START = 0,
        CONSOLE_CHECK_CMD,
        CONSOLE_CHECK_PRT,
    }s_tState;
    
    switch(s_tState) {
        case CONSOLE_CHECK_START:
            s_pchPRT = NULL;
            s_tState = CONSOLE_CHECK_CMD;
            //break;
            
        case CONSOLE_CHECK_CMD:
            if(DEQUEUE(InOutQueue,&g_tFIFOin,&s_chTemp)) {
                if ((s_chTemp >= 32) && (s_chTemp <= 127) ){
                    if(s_chCmdBufIndex >= CONSOLE_BUF_SIZE) {
                        break;
                    }
                    s_chCmdBuf[s_chCmdBufIndex++] = s_chTemp;
                    s_pchPRT = &s_chTemp;
                    s_chNum = 1;
                } else if('\r' == s_chTemp ) {
                    COSOLE_CHECK_RESET();
                    return fsm_rt_cpl;
                } else if('\b' == s_chTemp ){
                    if(s_chCmdBufIndex <= 2) {
                        break;
                    }
                    s_chCmdBufIndex--;
                    s_pchPRT = (uint8_t*)c_chDelChar;
                    s_chNum = UBOUND(c_chDelChar);
                }
                s_tState = CONSOLE_CHECK_PRT;
            }
            break;
        
        case CONSOLE_CHECK_PRT:
            if(fsm_rt_cpl == console_print(s_pchPRT,s_chNum)) {
                s_tState = CONSOLE_CHECK_CMD;
            }
            break;
    }
    
    return fsm_rt_on_going;
}

#define CONSOLE_PRT_RESET()   do {s_tState = CONSOLE_PRT_START;} while(0)
static fsm_rt_t console_print(const uint8_t *pchBuf,uint8_t chNum)
{
    static uint8_t s_chPrintIndex ;
    static enum {
        CONSOLE_PRT_START = 0,
        CONSOLE_PRT_PRINT
    }s_tState = CONSOLE_PRT_START;
    
    if((NULL == pchBuf) || (!chNum)) {
        return fsm_rt_err;
    }
    
    switch(s_tState) {
        case CONSOLE_PRT_START:
            s_chPrintIndex = 0;
            s_tState = CONSOLE_PRT_PRINT;
            //break;
            
        case CONSOLE_PRT_PRINT:
            if(s_chPrintIndex < chNum) {
                if(ENQUEUE(InOutQueue,&g_tFIFOout,pchBuf[s_chPrintIndex])) {
                    s_chPrintIndex++;
                }
            } else {
                CONSOLE_PRT_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}
































