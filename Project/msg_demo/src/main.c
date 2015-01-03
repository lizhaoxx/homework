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
#include ".\service\service.h"
#include ".\hal\hal.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
static uint8_t s_tSteamInBuf[16];
static uint8_t s_tSteamOutBuf[16];

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static void system_init(void);



int main(void)
{
    system_init();
    
    QUEUE_INIT(InOutQueue,&g_tFIFOin,s_tSteamInBuf, UBOUND(s_tSteamInBuf)); 
    QUEUE_INIT(InOutQueue,&g_tFIFOout,s_tSteamOutBuf, UBOUND(s_tSteamOutBuf)); 
   
    
    while(1) {
        
        task_console();
        stream_in_out();
    }
}


static void system_init(void)
{
    serial_init();
}
