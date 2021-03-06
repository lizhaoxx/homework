/***************************************************************************
 *   Copyright(C)2009-2012 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
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
#include "..\app_cfg.h"

#ifndef __USE_SERVICE_MSGMAP_CFG_H__
#define __USE_SERVICE_MSGMAP_CFG_H__

/*============================ INCLUDES ======================================*/

/*============================ MACROS ========================================*/
EXTERN_QUEUE(MsgMapQueue,uint8_t,uint8_t);

//! \brief msgmaps config
//! @{
#define INSERT_MSG_MAP_FUNC_EXRERN                                          \
    extern bool msg_apple_handler(const msg_t *ptMSG);                      \
    extern bool msg_orange_handler(const msg_t *ptMSG);                     \
    extern bool msg_hello_handler(const msg_t *ptMSG);

#define INSERT_MSG_MAP_CMD  {"apple", &msg_apple_handler},                  \
                            {"orange", &msg_orange_handler},                \
                            {"hello", &msg_hello_handler},

#define CHECK_BYTE_QUEUE     g_tFIFOin

//! @}

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#endif
/* EOF */

