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
 

/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"
#include "..\USART\USART1.h"
/*============================ MACROS ========================================*/
#ifndef SERIAL_OUT_HANDLE
#   error No defined SERIAL_OUT_HANDLE
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! \brief define print string struct 
//! @{
typedef struct{
    enum {
        PRINT_STRING_START = 0,
        PRINT_STRING_SEND
    }tState;                        //>! 存储被调用任务的状态
    uint8_t*   pSTRAddr;            //>! 存储待打印字符串的地址。
    uint8_t*   pIndex;              //>! 存储当前打印的字符地址。
}print_str_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief initialize  string output function
 *! \param print_str_t  print string struct point
 *! \param pchSTR  output string point
 *! \return false initialize faile
 *! \return true initialize success
 */
bool init_STR_output(print_str_t *ptPRN,uint8_t * pchSTR)
{
    if((NULL == ptPRN)||(NULL == pchSTR)){
        return false;
    }
    
    ptPRN->pSTRAddr = pchSTR;
    ptPRN->pIndex = NULL;
    ptPRN->tState = PRINT_STRING_START;
    
    return true;
}

/*! \brief initialize  string output function
 *! \param ptPRN  print string struct point
 *! \param fnSerialOut  output function string point
 *! \return fsm_rt_cpl print string cpl
 *! \return fsm_rt_err print faile
 */
#define PRINT_STRING_FSM_RESET() do{ptPRN->tState = PRINT_STRING_START;} while(0)
fsm_rt_t print_string(print_str_t *ptPRN)
{
    if(NULL == ptPRN) {
        return fsm_rt_err;
    }
    
    switch(ptPRN->tState) {
        case PRINT_STRING_START:
            if(ptPRN->pSTRAddr){
                ptPRN->pIndex = ptPRN->pSTRAddr;
                ptPRN->tState = PRINT_STRING_SEND;
            } else {
                return fsm_rt_err;
            }
            break;
         
        case PRINT_STRING_SEND:
            if('\0' != *(ptPRN->pIndex)){
                if(SERIAL_OUT_HANDLE(*ptPRN->pIndex)) {
                    (ptPRN->pIndex)++;
                }
                break;
            }
            PRINT_STRING_FSM_RESET();
            return fsm_rt_cpl;
    }

    return fsm_rt_on_going;
}


