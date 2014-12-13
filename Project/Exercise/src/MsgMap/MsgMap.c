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
 
#include ".\app_cfg.h"

/*============================ INCLUDES ======================================*/
#include "..\byte_queue\byte_queue.h"

/*============================ MACROS ========================================*/
#ifndef INSERT_MSG_MAP_CMD
    #error "No define macro INSERT_MSG_CMD for MsgMap.c !" 
#endif

#ifndef INSERT_MSG_MAP_FUNC_EXRERN
    #error MSG_MAP_FUNC_EXTERN
#endif

#ifndef CHECK_BYTE_QUEUE
    #error Macro CHECK_BYTE_QUEUE is not define for MsgMap.c!
#endif

#ifndef QUEUE_TYPE
    #error Macro QUEUE_TYPE is not define for MsgMap.c!
#endif

#define DEQUEUE_BYTE(__QUEUE, __OBJ)                                        \
            dequeue((__QUEUE),(__OBJ))
  
#define PEEK_BYTE_QUEUE(__QUEUE, __DATA)                                    \
            peek_byte_queue((__QUEUE),(__DATA))  
                              
#define RESET_PEEK_BYTE(__QUEUE)                                            \
            reset_peek_byte(__QUEUE)
            
#define GET_ALL_PEEKED_BYTE(__QUEUE)                                        \
            get_all_peek_byte(__QUEUE)

extern QUEUE_TYPE  CHECK_BYTE_QUEUE;
    
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct _msg_t msg_t;
typedef bool MSG_HANDLER(const msg_t *ptMSG);

struct _msg_t {
    uint8_t* chMSG;                 //!< 
    MSG_HANDLER *fnHandler;         //!< 
};

typedef struct _DynaMsg_t DynaMsg_t;
struct _DynaMsg_t {
    uint8_t         chDynCmdCount;
    msg_t           *ptMsgPtr;
};

typedef struct{
    enum {
        CHECK_STR_START = 0,
        CHECK_SRT_CHECK
    }tState;
    uint8_t* pchSTR;
    uint8_t* pchIndex;
    byte_queue_t* ptQueue; 
}check_str_t;
 
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
INSERT_MSG_MAP_FUNC_EXRERN
const static msg_t c_tMSGMap[] = {
    INSERT_MSG_MAP_CMD
};

static DynaMsg_t s_tDynaMsgConfig = {
    .chDynCmdCount = 0, 
    .ptMsgPtr = NULL };


/*============================ PROTOTYPES ====================================*/
static fsm_rt_t CheckEngine(const msg_t *ptMSG,bool* pbIsCheckFail);
static bool init_CHK_string(check_str_t *ptCHK,uint8_t* pchStr,byte_queue_t* ptQueue);
static fsm_rt_t check_string(check_str_t *ptCHK, bool *pbIsRequestDrop);


/*! \brief add user msg 
 *! \param ptMsg :user msg point
 *! \param chItemNum : user msg Item num
 *! \return ture :add success
 */
bool cmd_register(msg_t * ptMsg,uint8_t chItemNum)
{
    if((0 == chItemNum) || (NULL == ptMsg)){
        return false;
    }
    
    if(!s_tDynaMsgConfig.ptMsgPtr) {
        s_tDynaMsgConfig.chDynCmdCount = chItemNum; 
        s_tDynaMsgConfig.ptMsgPtr = ptMsg;
        return true;
    }
    
    return false;
}

/*! \brief del user msg map
 *! \param none
 *! \return none
 */
void cmd_unregister(void)
{
    s_tDynaMsgConfig.chDynCmdCount = 0; 
    s_tDynaMsgConfig.ptMsgPtr = NULL;
}

/*! \brief message map search
 *! \param ptMessageQueue
 *! \param ptSuccessMsg
 *! \return fsm_rt_t status
 */
#define TASK_CHECK_USE_PEEK_FSM_RESET() do { s_tState = TASK_CHECK_USE_PEEK_START;}while(0)
fsm_rt_t MsgMapSearch(const msg_t **ptSuccessMsg)
{
    fsm_rt_t tRes;
    uint8_t chByte = 0;
    bool bIsCheckFail = false;
    static const msg_t *c_ptMsg = NULL;
    static uint8_t s_chMsgIndex = 0;
    static enum {
        TASK_CHECK_USE_PEEK_START = 0,
        TASK_CHECK_USE_PEEK_SEARCH,
        TASK_CHECK_USE_PEEK_CHK_STR,
        TASK_CHECK_USE_PEEK_USER_SEARCH,
        TASK_CHECK_USE_PEEK_USER_CHK_STR
    }s_tState = TASK_CHECK_USE_PEEK_START;
    
    switch(s_tState) {
        case TASK_CHECK_USE_PEEK_START:
            if(!ptSuccessMsg) {
                return fsm_rt_err;
            }
            
            s_tState = TASK_CHECK_USE_PEEK_SEARCH;
            s_chMsgIndex = 0;
            //break;
            
        case TASK_CHECK_USE_PEEK_SEARCH:
            if ( s_chMsgIndex < UBOUND(c_tMSGMap) ) {
                c_ptMsg = &c_tMSGMap[s_chMsgIndex];
                s_chMsgIndex++;
                s_tState = TASK_CHECK_USE_PEEK_CHK_STR;
            } else if (s_tDynaMsgConfig.ptMsgPtr) {
                s_chMsgIndex   = 0, 
                s_tState = TASK_CHECK_USE_PEEK_USER_SEARCH;
            } else {
                DEQUEUE_BYTE(&CHECK_BYTE_QUEUE,&chByte);
                s_chMsgIndex = 0;
            }
            break;
    
        case TASK_CHECK_USE_PEEK_CHK_STR:
            tRes = CheckEngine(c_ptMsg,&bIsCheckFail);
            if(tRes == fsm_rt_cpl) {
                GET_ALL_PEEKED_BYTE(&CHECK_BYTE_QUEUE);
                *ptSuccessMsg = c_ptMsg;
                TASK_CHECK_USE_PEEK_FSM_RESET();
                return fsm_rt_cpl;
            } else if (bIsCheckFail) {
                RESET_PEEK_BYTE(&CHECK_BYTE_QUEUE);
                s_tState = TASK_CHECK_USE_PEEK_SEARCH;
            }
            break;
            
        case TASK_CHECK_USE_PEEK_USER_SEARCH:
            if ( s_chMsgIndex < s_tDynaMsgConfig.chDynCmdCount)  {
                c_ptMsg = &((s_tDynaMsgConfig.ptMsgPtr)[s_chMsgIndex]);
                s_chMsgIndex++;
                s_tState = TASK_CHECK_USE_PEEK_USER_CHK_STR;
            } else {
                DEQUEUE_BYTE(&CHECK_BYTE_QUEUE,&chByte);
                s_chMsgIndex = 0;
                s_tState = TASK_CHECK_USE_PEEK_SEARCH;
            }
            break;
    
        case TASK_CHECK_USE_PEEK_USER_CHK_STR:
            tRes = CheckEngine(c_ptMsg,&bIsCheckFail);
            if(tRes == fsm_rt_cpl) {
                GET_ALL_PEEKED_BYTE(&CHECK_BYTE_QUEUE);
                *ptSuccessMsg = c_ptMsg;
                TASK_CHECK_USE_PEEK_FSM_RESET();
                return fsm_rt_cpl;
            } else if (bIsCheckFail) {
                RESET_PEEK_BYTE(&CHECK_BYTE_QUEUE);
                s_tState = TASK_CHECK_USE_PEEK_USER_SEARCH;
            }
            break;
    }
    
    return fsm_rt_on_going;
}

#define TASK_CHECK_ENGINE_FSM_RESET() do { s_tState = TASK_CHECK_ENGINE_START;}while(0)
static fsm_rt_t CheckEngine(const msg_t *ptMSG,bool* pbIsCheckFail)
{
    fsm_rt_t tRes;
    bool bIsRequestDrop = false;
    static check_str_t s_tCHK;
    static enum {
        TASK_CHECK_ENGINE_START = 0,
        TASK_CHECK_ENGINE_CHECK
    }s_tState = TASK_CHECK_ENGINE_START;
    
    if((NULL == ptMSG) || (NULL == pbIsCheckFail)){
        return fsm_rt_err ;
    }
    
    switch(s_tState) {
        case TASK_CHECK_ENGINE_START:
            if(init_CHK_string(&s_tCHK,ptMSG->chMSG,&CHECK_BYTE_QUEUE)) {  
                s_tState = TASK_CHECK_ENGINE_CHECK;
            } else {
                return fsm_rt_err;
            }
            //break;
            
        case TASK_CHECK_ENGINE_CHECK:
            tRes = check_string(&s_tCHK,&bIsRequestDrop);
            if(tRes == fsm_rt_cpl) {
                TASK_CHECK_ENGINE_FSM_RESET();
                return fsm_rt_cpl;
            } else if (bIsRequestDrop) {
                *pbIsCheckFail = true;
                TASK_CHECK_ENGINE_FSM_RESET();
            }
            break;
    }
    
    return fsm_rt_on_going;
}



#define CHECK_STR_FSM_RESET() do {ptCHK->tState = CHECK_STR_START;}while(0)
static fsm_rt_t check_string(check_str_t *ptCHK, bool *pbIsRequestDrop)
{
    static uint8_t chByte = 0;
    
    if( (NULL == ptCHK) || (NULL == pbIsRequestDrop) ){ 
        return fsm_rt_err;
    }
    
    switch(ptCHK->tState){
        case CHECK_STR_START:
            if(NULL == ptCHK->pchSTR) {
                return fsm_rt_err;
            } else {
                ptCHK->pchIndex = ptCHK->pchSTR;
                ptCHK->tState = CHECK_SRT_CHECK;
            }
            //break;
            
        case CHECK_SRT_CHECK:
            if(PEEK_BYTE_QUEUE(ptCHK->ptQueue,&chByte)) {
                *pbIsRequestDrop = true;
                if(chByte == *(ptCHK->pchIndex)) {
                    if('\0' == *(++(ptCHK->pchIndex))){
                        CHECK_STR_FSM_RESET();
                        return fsm_rt_cpl;
                    }
                    *pbIsRequestDrop = false;
                } 
            }
            break;
    }
    
    return fsm_rt_on_going;
}

static bool init_CHK_string(check_str_t *ptCHK,uint8_t* pchStr,byte_queue_t* ptQueue)
{
    if((NULL == ptCHK)||(NULL == pchStr)||(NULL == ptQueue)){
        return false;
    }
    
    ptCHK->pchSTR   = pchStr;
    ptCHK->pchIndex = NULL;
    ptCHK->tState   = CHECK_STR_START;
    ptCHK->ptQueue  = ptQueue;

    return true;
}

WEAK bool peek_byte_queue(byte_queue_t *ptQueue, uint8_t *pchObj)
{    
    if(NULL == ptQueue) {
        return false;
    }
    return false;
}

WEAK bool get_all_peek_byte(byte_queue_t *ptQueue)
{
    if(NULL == ptQueue) {
        return false;
    }
    return false;
}
WEAK bool reset_peek_byte(byte_queue_t *ptQueue)
{
    if(NULL == ptQueue) {
        return false;
    }
    return false;
}
WEAK bool dequeue(byte_queue_t *ptQueue, uint8_t *ptObj)
{
    if(NULL == ptQueue) {
        return false;
    }
    return false;
}
