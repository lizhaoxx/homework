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


#ifndef __MAIL_BOX_H__
#define __MAIL_BOX_H__
/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"

/*============================ MACROS ========================================*/
#define POST_MAIL(__MAIL,__TARGET)      Post_Mail(__MAIL,__TARGET)
#define OPEN_MAIL(__MAIL)               Open_Mail(__MAIL)
#define IS_MAIL_OPENED(__MAIL)          Is_Mail_Opend(__MAIL)
#define INIT_MAIL(__MAIL)               Init_Mail(__MAIL)

#define MAIL_BOX_SIZE                   10

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! @{
typedef struct {
    bool bSealed;           //false: opend ture:sealed
    void *pTarget;
}mailbox_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*����һ����Ϣ������*/
extern void Post_Mail(mailbox_t *tMbox,void *pTarget);

/*������*/
extern void* Open_Mail(mailbox_t *tMbox);

/*�����Ƿ񱻴�*/
extern bool Is_Mail_Opend(mailbox_t *tMbox);

/*��ʼ������*/
extern void Init_Mail(mailbox_t *tMbox);

#endif
