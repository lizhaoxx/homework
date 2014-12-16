/* ************************************************************************ *\

Copyright (c) 2006, Atmel Corporation All rights reserved. 

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer. 

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. The name of ATMEL may not be used to endorse or promote products derived 
from this software without specific prior written permission.  

THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED 
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND 
SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

\* ************************************************************************ */

//! \note do not move this pre-processor statement to other places
#include "..\app_cfg.h"

#ifndef __USE_SERVICE_APP_CFG_H__
#define __USE_SERVICE_APP_CFG_H__

/*============================ INCLUDES ======================================*/
#include ".\utilities\template\template.h"

/*============================ MACROS ========================================*/

EXTERN_QUEUE(MsgMapQueue,uint8_t,uint8_t);

#define INSERT_MSG_MAP_FUNC_EXRERN                                          \
    extern bool msg_apple_handler(const msg_t *ptMSG);                      \
    extern bool msg_orange_handler(const msg_t *ptMSG);                     \
    extern bool msg_hello_handler(const msg_t *ptMSG);

#define INSERT_MSG_MAP_CMD  {"apple", &msg_apple_handler},                  \
                        {"orange", &msg_orange_handler},                    \
                        {"hello", &msg_hello_handler},
                        
#define CHECK_BYTE_QUEUE  g_tFIFOin
                        
/*============================ MACROFIED FUNCTIONS ===========================*/
#define SERIAL_OUT_HANDLE(__PCH)   serial_out(__PCH)

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#endif
/* EOF */

