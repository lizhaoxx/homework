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
bool queue_init(byte_queue_t *ptQueue, uint8_t *pchBuffer, uint16_t hwSize)
{
    if (NULL == ptQueue || NULL == pchBuffer || 0 == hwSize) {
        return false;
    }
    
    ptQueue->pchBuffer = pchBuffer;
    ptQueue->hwSize = hwSize;
    ptQueue->hwHead = 0;
    ptQueue->hwTail = 0;
    ptQueue->hwLength = 0; 
 
    ptQueue->hwPeekHead = 0;  
    ptQueue->hwPeekLen = 0; 
 
    return true;
}

/*! \brief add byte queue 
 *! \param ptQueue  queue point
 *! \param pchBuffer  queue buffer
 *! \param hwSize  queue size
 *! \return false initialize faile
 *! \return true initialize success
 */
bool enqueue(byte_queue_t *ptQueue, uint8_t tObj)
{
    if (NULL == ptQueue) {
        return false;
    }

    if ((ptQueue->hwHead == ptQueue->hwTail) && (0 != ptQueue->hwLength)) { 
        return false;
    }
     
    //!< add tObj to queue
    ptQueue->pchBuffer[ptQueue->hwTail++] = tObj;
    if (ptQueue->hwTail >= ptQueue->hwSize) {
        ptQueue->hwTail = 0;
    }
    ptQueue->hwLength++;
    ptQueue->hwPeekLen++; 
    
    return true;
}

/*! \brief del one byte from queue 
 *! \param ptQueue  queue point
 *! \param ptObj  recive the data from buffer
 *! \return true del success
 */
bool dequeue(byte_queue_t *ptQueue, uint8_t *ptObj)
{
    if ((NULL == ptQueue)||(NULL == ptObj)) {
        return false;
    }

    if ((ptQueue->hwHead == ptQueue->hwTail) && (!ptQueue->hwLength)) {  
        return false;
    }
      
    *ptObj = ptQueue->pchBuffer[ptQueue->hwHead];  
    ptQueue->hwHead++;
    if (ptQueue->hwHead >= ptQueue->hwSize) {
        ptQueue->hwHead = 0;
    } 
    ptQueue->hwLength--;
    
    //!< reset peek point
    ptQueue->hwPeekHead = ptQueue->hwHead;
    ptQueue->hwPeekLen  = ptQueue->hwLength;

    return true;
} 


/*! \brief check the queue is empyt 
 *! \param ptQueue  queue point
 *! \return true the queue is empyt 
 */
bool is_type_queue_empty(byte_queue_t *ptQueue)
{
    if (NULL == ptQueue ) {
        return false;
    }
      
    if ((ptQueue->hwHead == ptQueue->hwTail) && (!ptQueue->hwLength)) {  
        return true;
    }
      
    return false;
}

/*! \brief peek the queue  
 *! \param ptQueue  queue point
 *! \param pchObj  recive the peek data buffer point
 *! \return true peek queue is sucess 
 */
bool peek_byte_queue(byte_queue_t *ptQueue, uint8_t *pchObj)
{
    if((NULL == ptQueue) || (NULL == pchObj)) {
        return false;
    }
      
    if((ptQueue->hwPeekHead == ptQueue->hwTail) && (!ptQueue->hwPeekLen )){ 
        return false;
    }
      
    *pchObj = ptQueue->pchBuffer[ptQueue->hwPeekHead];
    ptQueue->hwPeekHead ++;
    if (ptQueue->hwPeekHead >= ptQueue->hwSize) {
        ptQueue->hwPeekHead = 0;
    } 
    ptQueue->hwPeekLen--;
    
    return true;
}

/*! \brief del all the peek data  
 *! \param ptQueue  queue point
 *! \return true del peek data is sucess 
 */
bool get_all_peek_byte(byte_queue_t *ptQueue)
{
    if(NULL == ptQueue) {
        return false;
    }
          
    ptQueue->hwHead = ptQueue->hwPeekHead;
    ptQueue->hwLength = ptQueue->hwPeekLen;
    
    return true;
}

/*! \brief reset peek point  
 *! \param ptQueue  queue point
 *! \return true reset peek queue sucess
 */
bool reset_peek_byte(byte_queue_t *ptQueue)
{
    if(NULL == ptQueue) {
        return false;
    }
    
    ptQueue->hwPeekHead = ptQueue->hwHead;
    ptQueue->hwPeekLen  = ptQueue->hwLength;

    return true;
}

