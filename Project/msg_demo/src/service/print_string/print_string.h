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
 
#ifndef __PRINT_STRING_H__
#define __PRINT_STRING_H__
/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
#define INIT_SRT_OUTPUT(__STRCONFIG,__STR)                                     \
                init_STR_output((__STRCONFIG),(__STR))

#define STR_OUTPUT(__STR)                                                      \
                print_string((__STR))

/*============================ TYPES =========================================*/
//! \brief define print string struct 
//! @{
typedef struct{
    enum {
        PRINT_STRING_START = 0,
        PRINT_STRING_SEND
    }tState;                        //!<存储被调用任务的状态
    uint8_t*   pSTRAddr;            //!<存储待打印字符串的地址。
    uint8_t*   pIndex;              //!<存储当前打印的字符地址。
}print_str_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief initialize  string output function
 *! \param ptPRN  print string struct point
 *! \param fnSerialOut  output function string point
 *! \return fsm_rt_cpl print string cpl
 *! \return fsm_rt_err print faile
 */
extern fsm_rt_t print_string(print_str_t *ptPRN);

/*! \brief initialize  string output function
 *! \param print_str_t  print string struct point
 *! \param pchSTR  output string point
 *! \return false initialize faile
 *! \return true initialize success
 */
extern bool init_STR_output(print_str_t *ptPRN,uint8_t * pchSTR);

#endif


/* EOF */
