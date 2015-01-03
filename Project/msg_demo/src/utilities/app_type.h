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


#ifndef __USE_APP_TYPE__H__
#define __USE_APP_TYPE__H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/*============================ MACROS ========================================*/
#define  ENABLED                0
#define  DISABLE                1

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
# define ENABLE_GLOBAL_INTERRUPT()
# define DISABLE_GLOBAL_INTERRUPT()
# define ATOM_ACESS(__CODE)      {\
                DISABLE_GLOBAL_INTERRUPT();\
                __CODE;\
                ENABLE_GLOBAL_INTERRUPT();\
            }

#define UBOUND(__Array__)       ( sizeof(__Array__)/sizeof(__Array__[0]) )

//! @{
typedef enum {
    fsm_rt_err          = -1,    //!< fsm error, error code can be get from other interface
    fsm_rt_cpl          = 0,     //!< fsm complete
    fsm_rt_on_going     = 1,     //!< fsm on-going
} fsm_rt_t;
//! @}

    
/*
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;
 */
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#endif
/* EOF */

