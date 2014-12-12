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

/*发生一条消息到邮箱*/
void Post_Mail(mailbox_t *pMbox,void *pTarget)
{
    if((NULL != pMbox) && (NULL != pTarget)){
        pMbox->bSealed = true;
        pMbox->pTarget = pTarget;
    }
}

/*打开邮箱*/
void* Open_Mail(mailbox_t *pMbox)
{
    if(NULL == pMbox){
        return NULL;
    }
    
    if(pMbox->bSealed){
        pMbox->bSealed = false;
        return pMbox->pTarget;
    }
    
    return NULL;
}

/*邮箱是否被打开*/
bool Is_Mail_Opend(mailbox_t *pMbox)
{
    if(NULL == pMbox) {
        return true;
    }
    
    return !(pMbox->bSealed);
}

/*初始化邮箱*/
void Init_Mail(mailbox_t *pMbox)
{
    if(NULL != pMbox){
        pMbox->bSealed = false;
        pMbox->pTarget = NULL;
    }
}
