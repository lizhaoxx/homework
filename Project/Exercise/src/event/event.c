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
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! @{
typedef enum {
    MANUAL  = 0,
    AUTOSET 
}even_model_t;
//! @}

//! @{
typedef struct{
    bool bAutoReset;
    bool bIsSet;
}event_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
void set_event(event_t *ptEvent)
{
    if(NULL != ptEvent){
        ptEvent->bIsSet = true;
    }
}

void reset_event(event_t *ptEvent)
{
    if(NULL != ptEvent){
        ptEvent->bIsSet = false;
    }    
}

bool wait_event(event_t *ptEvent)
{
    if(NULL == ptEvent ){
        return false;
    }
    
    if( AUTOSET == ptEvent->bAutoReset ){
        if(ptEvent->bIsSet){
            ptEvent->bIsSet = false;
            return true;
        }
    }
    
    return ptEvent->bIsSet;
}

void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel)
{
    if( NULL != ptEvent ){
        ptEvent->bIsSet     = bInitValue;
        ptEvent->bAutoReset = tModel;
    } 
}




