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

#ifndef __BYTE_QUEUE_H__
#define __BYTE_QUEUE_H__
/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"

/*============================ MACROS ========================================*/
#define INIT_BYTE_QUEUE(__QUEUE, __BUFFER, __SIZE)                          \
            queue_init((__QUEUE), (__BUFFER), (__SIZE))

#define DEQUEUE_BYTE(__QUEUE, __OBJ)                                        \
            dequeue((__QUEUE),(__OBJ))

#define ENQUEUE_BYTE(__QUEUE, __OBJ)                                        \
            enqueue((__QUEUE), (__OBJ))
    
#define IS_TYPE_QUEUE_EMPTY(__QUEUE)                                        \
            is_type_queue_empty((__QUEUE))

#define PEEK_BYTE_QUEUE(__QUEUE, __DATA)                                    \
            peek_byte_queue((__QUEUE),(__DATA))  
                              
#define RESET_PEEK_BYTE(__QUEUE)                                            \
            reset_peek_byte(__QUEUE)
            
#define GET_ALL_PEEKED_BYTE(__QUEUE)                                        \
            get_all_peek_byte(__QUEUE)


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! \name define queue struct type byte_queue_t
//! @{
typedef struct {
    uint8_t *pchBuffer;
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;
    uint16_t hwPeekHead;
    uint16_t hwPeekLen ;
}byte_queue_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*! \brief initialize  byte queue
 *! \param ptQueue  queue point
 *! \param pchBuffer  queue buffer
 *! \param hwSize  queue size
 *! \return false initialize faile
 *! \return true initialize success
 */
extern bool queue_init(byte_queue_t *ptQueue, uint8_t *pchBuffer, uint16_t hwSize);  

/*! \brief add byte queue 
 *! \param ptQueue  queue point
 *! \param pchBuffer  queue buffer
 *! \param hwSize  queue size
 *! \return false initialize faile
 *! \return true initialize success
 */
extern bool enqueue(byte_queue_t *ptQueue, uint8_t tObj);

/*! \brief del one byte from queue 
 *! \param ptQueue  queue point
 *! \param ptObj  recive the data from buffer
 *! \return true del success
 */
 
extern bool dequeue(byte_queue_t *ptQueue, uint8_t *ptObj);

/*! \brief check the queue is empyt 
 *! \param ptQueue  queue point
 *! \return true the queue is empyt 
 */
extern bool is_type_queue_empty(byte_queue_t *ptQueue);

/*! \brief peek the queue  
 *! \param ptQueue  queue point
 *! \param pchObj  recive the peek data buffer point
 *! \return true peek queue is sucess 
 */
extern bool peek_byte_queue(byte_queue_t *ptQueue, uint8_t *pchObj) ;  

/*! \brief del all the peek data  
 *! \param ptQueue  queue point
 *! \return true del peek data is sucess 
 */
extern bool get_all_peek_byte(byte_queue_t *ptQueue);

/*! \brief reset peek point  
 *! \param ptQueue  queue point
 *! \return true reset peek queue sucess
 */
extern bool reset_peek_byte(byte_queue_t *ptQueue);

#endif



/* EOF */

