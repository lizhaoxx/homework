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
 
 #ifndef __TEMPLATE_QUEUE_H__
 #define __TEMPLATE_QUEUE_H__
 
/*=========================== INSTRUCTION=====================================*/
/*
    config:
        insert DEF_QUEUE(BYTE,uint8_t,uint8_t,ATOM_ACESS); in xxx_queue.c
        insert EXTERN_QUEUE(BYTE,uint8_t,uint8_t); in xxx_queue.h
    
    application:
        include "xxx_queue.h"
        uint8_t chBuffer[10];
        uint8_t chByte;
        QUEUE(BYTE) Fifo;
        
        QUEUE_INIT(BYTE, &Fifo, chBuffer, 10);
        ENQUEUE(BYTE, &Fifo, 2);
        PEEK_QUEUE(BYTE, &Fifo, &chByte);
        RESET_PEEK(BYTE, &Fifo);
        GET_ALL_PEEK(BYTE, &Fifo);
        DEQUEUE(BYTE, &Fifo, &chByte);
*/

/*=========================== INCLUDES =======================================*/
/*============================ MACROS ========================================*/
//! @{
#define QUEUE_INIT(__NAME, __QUEUE, __BUFFER, __SIZE)                       \
            __NAME##_queue_init((__QUEUE), (__BUFFER), (__SIZE))

#define DEQUEUE(__NAME, __QUEUE, __ADDR)                                    \
            __NAME##_dequeue((__QUEUE),(__ADDR))

#define ENQUEUE(__NAME, __QUEUE, __VALUE)                                   \
            __NAME##_enqueue((__QUEUE), (__VALUE))

#define PEEK_QUEUE(__NAME, __QUEUE, __ADDR)                                 \
            __NAME##_peek_queue((__QUEUE),(__ADDR))

#define RESET_PEEK(__NAME, __QUEUE)                                         \
            __NAME##_reset_peek((__QUEUE))

#define GET_ALL_PEEK(__NAME, __QUEUE)                                       \
            __NAME##_get_all_peek((__QUEUE))

#define QUEUE(__NAME)   __NAME##_queue_t
//!@}

#define EXTERN_QUEUE(__NAME,__TYPE,__PTR_TYPE)                              \
EXTERN_CLASS(__NAME##_queue_t)                                              \
    __TYPE          *ptBuffer;                                              \
    __PTR_TYPE      tSize;                                                  \
    __PTR_TYPE      tHead;                                                  \
    __PTR_TYPE      tTail;                                                  \
    __PTR_TYPE      tLength;                                                \
    __PTR_TYPE      tPeekHead;                                              \
    __PTR_TYPE      tPeekLen;                                               \
END_EXTERN_CLASS(__NAME##_queue_t)                                          \
                                                                            \
extern bool __NAME##_reset_peek(__NAME##_queue_t *ptQueue);                 \
extern bool __NAME##_get_all_peek(__NAME##_queue_t *ptQueue);               \
extern bool __NAME##_peek_queue(__NAME##_queue_t *ptQueue, __TYPE *pchObj); \
extern bool __NAME##_dequeue(__NAME##_queue_t *ptQueue, __TYPE *ptObj);     \
extern bool __NAME##_enqueue(__NAME##_queue_t *ptQueue, __TYPE tObj);       \
extern bool __NAME##_queue_init(                                            \
    __NAME##_queue_t *ptQueue, __TYPE *ptBuffer, __PTR_TYPE tSize);         \

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#define DEF_QUEUE(__NAME,__TYPE,__PTR_TYPE,__ATOM_ACCESS)                   \
DEF_CLASS(__NAME##_queue_t)                                                 \
    __TYPE          *ptBuffer;                                              \
    __PTR_TYPE      tSize;                                                  \
    __PTR_TYPE      tHead;                                                  \
    __PTR_TYPE      tTail;                                                  \
    __PTR_TYPE      tLength;                                                \
    __PTR_TYPE      tPeekHead;                                              \
    __PTR_TYPE      tPeekLen;                                               \
END_DEF_CLASS(__NAME##_queue_t)                                             \
                                                                            \
bool __NAME##_reset_peek(__NAME##_queue_t *ptQueue)                         \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t) *)ptQueue;   \
                                                                            \
    if(NULL == ptThis) {                                                    \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        ptThis->tPeekHead = ptThis->tHead;                                  \
        ptThis->tPeekLen  = ptThis->tLength;                                \
    )                                                                       \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_get_all_peek(__NAME##_queue_t *ptQueue)                       \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t) *)ptQueue;   \
                                                                            \
    if(NULL == ptThis) {                                                    \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        ptThis->tHead = ptThis->tPeekHead;                                  \
        ptThis->tLength = ptThis->tPeekLen;                                 \
    )                                                                       \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_peek_queue(__NAME##_queue_t *ptQueue, __TYPE *pchObj)         \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t) *)ptQueue;   \
                                                                            \
    if((NULL == ptThis) || (NULL == pchObj)) {                              \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if((ptThis->tPeekHead == ptThis->tTail) && (!ptThis->tPeekLen )){       \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        *pchObj = ptThis->ptBuffer[ptThis->tPeekHead];                      \
        ptThis->tPeekHead ++;                                               \
        if (ptThis->tPeekHead >= ptThis->tSize) {                           \
            ptThis->tPeekHead = 0;                                          \
        }                                                                   \
        ptThis->tPeekLen--;                                                 \
    )                                                                       \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_dequeue(__NAME##_queue_t *ptQueue, __TYPE *ptObj)             \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t)*)ptQueue;    \
                                                                            \
    if ((NULL == ptThis)||(NULL == ptObj)) {                                \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if ((ptThis->tHead == ptThis->tTail) && (!ptThis->tLength)) {           \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        *ptObj = ptThis->ptBuffer[ptThis->tHead];                           \
        ptThis->tHead++;                                                    \
        if (ptThis->tHead >= ptThis->tSize) {                               \
            ptThis->tHead = 0;                                              \
        }                                                                   \
        ptThis->tLength--;                                                  \
                                                                            \
        ptThis->tPeekHead = ptThis->tHead;                                  \
        ptThis->tPeekLen  = ptThis->tLength;                                \
    )                                                                       \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_enqueue(__NAME##_queue_t *ptQueue, __TYPE tObj)               \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t)*)ptQueue;    \
                                                                            \
    if (NULL == ptThis) {                                                   \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if ((ptThis->tHead == ptThis->tTail) && (0 != ptThis->tLength)) {       \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        ptThis->ptBuffer[ptThis->tTail++] = tObj;                           \
        if (ptThis->tTail >= ptThis->tSize) {                               \
            ptThis->tTail = 0;                                              \
        }                                                                   \
        ptThis->tLength++;                                                  \
        ptThis->tPeekLen++;                                                 \
    )                                                                       \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_queue_init(                                                   \
    __NAME##_queue_t *ptQueue, __TYPE *ptBuffer, __PTR_TYPE tSize)          \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptThis = (CLASS(__NAME##_queue_t)*)ptQueue;    \
                                                                            \
    if (NULL == ptThis || NULL == ptBuffer || 0 == tSize) {                 \
        return false;                                                       \
    }                                                                       \
                                                                            \
    ptThis->ptBuffer = ptBuffer;                                            \
    ptThis->tSize = tSize;                                                  \
    ptThis->tHead = 0;                                                      \
    ptThis->tTail = 0;                                                      \
    ptThis->tLength = 0;                                                    \
                                                                            \
    ptThis->tPeekHead = 0;                                                  \
    ptThis->tPeekLen = 0;                                                   \
                                                                            \
    return true;                                                            \
}                                                                           \

#endif
