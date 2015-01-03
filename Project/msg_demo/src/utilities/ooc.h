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

#ifndef __OBJECT_ORIENTED_C_H__
#define __OBJECT_ORIENTED_C_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

#define CLASS(__NAME)               __##__NAME


#define DEF_CLASS(__NAME,...)\
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    typedef struct __##__NAME __##__NAME;\
    struct __##__NAME {

#define END_DEF_CLASS(__NAME) \
    };\
    union __NAME {\
        uint_fast8_t chMask[(sizeof(__##__NAME) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };
    
#define EXTERN_CLASS(__NAME,...) \
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    union __NAME {\
        uint_fast8_t chMask[(sizeof(struct {

#define END_EXTERN_CLASS(__NAME) \
        }) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
    
#endif
    