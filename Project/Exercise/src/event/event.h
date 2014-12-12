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
 
//! \note do not move this pre-processor statement to other places
#include ".\app_cfg.h"

#ifndef __EVENT_H__
#define __EVENT_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
#define SET_EVENT(__EVENT)         set_event(__EVENT)
#define WAIT_EVENT(__EVENT)        wait_event(__EVENT)
#define RESET_EVENT(__EVENT)       reset_event(__EVENT)
#define INIT_EVENT(__EVENT, __EVENT_VALUE, __MANUAL)                            \
            init_event(__EVENT,__EVENT_VALUE,__MANUAL)

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
extern void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel);
extern void set_event(event_t *ptEvent);
extern void reset_event(event_t *ptEvent);
extern bool wait_event(event_t *ptEvent);

#endif
