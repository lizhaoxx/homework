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

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
DEF_QUEUE(InOutQueue,uint8_t,uint8_t,ATOM_ACESS);

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
QUEUE(InOutQueue) g_tFIFOin;
QUEUE(InOutQueue) g_tFIFOout;

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static fsm_rt_t serial_in_task(void);
static fsm_rt_t serial_out_task(void);

void stream_in_out(void)
{
    serial_in_task();
    serial_out_task();
}

#define SERIAL_IN_TASK_FSM_RESET() do {s_tState = SERIAL_IN_TASK_START;} while(0)
static fsm_rt_t serial_in_task(void)
{
    static uint8_t s_chByte = 0;
    static enum {
        SERIAL_IN_TASK_START = 0,
        SERIAL_IN_TASK_READ
    }s_tState = SERIAL_IN_TASK_START;
    
    switch(s_tState) {
        case SERIAL_IN_TASK_START:
            s_tState = SERIAL_IN_TASK_READ;
            //breka;
        case SERIAL_IN_TASK_READ:
            if(serial_in(&s_chByte)){
                ENQUEUE(InOutQueue,&g_tFIFOin,s_chByte);
                SERIAL_IN_TASK_FSM_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}

#define SERIAL_OUT_TASK_FSM_RESET() do {s_tState = SERIAL_OUT_TASK_START;} while(0)
static fsm_rt_t serial_out_task(void)
{
    static uint8_t s_chByte = 0;
    static enum {
        SERIAL_OUT_TASK_START = 0,
        SERIAL_OUT_TASK_READ_QUE,
        SERIAL_OUT_TASK_OUTPUT
    }s_tState = SERIAL_OUT_TASK_START;
    
    switch(s_tState) {
        case SERIAL_OUT_TASK_START:
            s_tState = SERIAL_OUT_TASK_READ_QUE;
            //breka;
        case SERIAL_OUT_TASK_READ_QUE:
            if(DEQUEUE(InOutQueue,&g_tFIFOout,&s_chByte)){
                s_tState = SERIAL_OUT_TASK_OUTPUT;
            }
            break;        
            
        case SERIAL_OUT_TASK_OUTPUT:
            if(serial_out(s_chByte)) {
                SERIAL_OUT_TASK_FSM_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}
