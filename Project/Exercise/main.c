
#include ".\app_cfg.h"
#include "src\CheckString\CheckString.h"
#include "src\Port\Port.h"
#include "src\print_string\print_string.h"
#include "src\USART\USART1.h"
#include "src\event\event.h"
#include "src\byte_queue\byte_queue.h"
#include ".\src\MsgMap\MsgMap.h"

#define BYTE_QUE_BUF_LEN        16
#define BYTE_PIPE_BUF_LEN       16

static void system_init(void);
static fsm_rt_t print_world(void);
static fsm_rt_t print_apple(void);
static fsm_rt_t print_orange(void);
  
static fsm_rt_t serial_in_task(void);
static fsm_rt_t serial_out_task(void);

// bool msg_orange_handler(const msg_t *ptMSG);
// bool msg_hello_handler(const msg_t *ptMSG);
// bool msg_apple_handler(const msg_t *ptMSG);

bool msg_use2_handler(const msg_t *ptMSG);
bool msg_use1_handler(const msg_t *ptMSG);

static fsm_rt_t task_a(void);
static fsm_rt_t task_b(void);
static fsm_rt_t task_c(void);


 byte_queue_t s_tFIFOin;
 byte_queue_t s_tFIFOout;

static event_t s_tEventApple;
static event_t s_tEventOrange;
static event_t s_tEventWorld;

static uint8_t s_tBuf[BYTE_QUE_BUF_LEN];
static uint8_t s_tPiPeBuf[BYTE_PIPE_BUF_LEN];
static  fsm_rt_t CheckSringUseMsgMap(void);

static msg_t s_tUserMSGMap[] = {
    {"use1", &msg_use1_handler},
    {"use2", &msg_use2_handler},
};

int main(void)
{
    system_init();
    
    INIT_EVENT(&s_tEventApple,false,MANUAL);
    INIT_EVENT(&s_tEventOrange,false,MANUAL);
    INIT_EVENT(&s_tEventWorld,false,MANUAL);
    
    INIT_BYTE_QUEUE(&s_tFIFOin,s_tBuf, UBOUND(s_tBuf));
    INIT_BYTE_QUEUE(&s_tFIFOout,s_tPiPeBuf, UBOUND(s_tPiPeBuf));
    
    add_dynamic_command(s_tUserMSGMap,UBOUND(s_tUserMSGMap));
    
    while(1) {
        LEDBreath(); 

        task_a();
        task_b();
        task_c();
        CheckSringUseMsgMap();
        serial_in_task();
        serial_out_task();
    }
}
static  fsm_rt_t CheckSringUseMsgMap(void)
{
    const msg_t *ptMsg = NULL;

    if(fsm_rt_cpl == MsgMapSearch(&s_tFIFOin,&ptMsg)) {
        ptMsg->fnHandler(ptMsg);
    }
        
    return fsm_rt_on_going;
}
bool msg_apple_handler(const msg_t *ptMSG)
{
    if(NULL == ptMSG) {
        return false ;
    }
                    
    SET_EVENT(&s_tEventApple);
    return  true;
}

bool msg_hello_handler(const msg_t *ptMSG)
{
    if(NULL == ptMSG) {
        return false ;
    }
                    
    SET_EVENT(&s_tEventWorld);
    return  true;
}

bool msg_use1_handler(const msg_t *ptMSG)
{
    if(NULL == ptMSG) {
        return false ;
    }
    
    SET_EVENT(&s_tEventApple);
    SET_EVENT(&s_tEventWorld);
    return  true;
}

bool msg_use2_handler(const msg_t *ptMSG)
{
    if(NULL == ptMSG) {
        return false ;
    }
    SET_EVENT(&s_tEventWorld);
    SET_EVENT(&s_tEventOrange);
    return  true;
}


bool msg_orange_handler(const msg_t *ptMSG)
{
    if(NULL == ptMSG) {
        return false ;
    }
                    
    SET_EVENT(&s_tEventOrange);
    return  true;
}

#define SERIAL_IN_TASK_FSM_RESET() do {s_tState = SERIAL_IN_TASK_START;} while(0)
static fsm_rt_t serial_in_task(void)
{
    static uint8_t s_chByte = 0;
    static enum {
        SERIAL_IN_TASK_START = 0,
        SERIAL_IN_TASK_READ
    }s_tState = SERIAL_IN_TASK_START;
    
    switch(s_tState) {
        case SERIAL_IN_TASK_START:
            s_tState = SERIAL_IN_TASK_READ;
            //breka;
        case SERIAL_IN_TASK_READ:
            if(serial_in(&s_chByte)){
                ENQUEUE_BYTE(&s_tFIFOin,s_chByte);
                SERIAL_IN_TASK_FSM_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}

#define SERIAL_OUT_TASK_FSM_RESET() do {s_tState = SERIAL_OUT_TASK_START;} while(0)
static fsm_rt_t serial_out_task(void)
{
    static uint8_t s_chByte = 0;
    static enum {
        SERIAL_OUT_TASK_START = 0,
        SERIAL_OUT_TASK_READ_QUE,
        SERIAL_OUT_TASK_OUTPUT
    }s_tState = SERIAL_OUT_TASK_START;
    
    switch(s_tState) {
        case SERIAL_OUT_TASK_START:
            s_tState = SERIAL_OUT_TASK_READ_QUE;
            //breka;
        case SERIAL_OUT_TASK_READ_QUE:
            if(DEQUEUE_BYTE(&s_tFIFOout,&s_chByte)){
                s_tState = SERIAL_OUT_TASK_OUTPUT;
            }
            break;        
            
        case SERIAL_OUT_TASK_OUTPUT:
            if(serial_out(s_chByte)) {
                SERIAL_OUT_TASK_FSM_RESET();
                return fsm_rt_cpl;
            }
            break;
    }
    
    return fsm_rt_on_going;
}

#define TASK_A_FSM_RESET() do {s_tState = TASK_A_START;} while(0)
static fsm_rt_t task_a(void)
{
    static enum {
        TASK_A_START                    = 0,
        TASK_A_WAIT_EVENT,
        TASK_A_PRINT
    }s_tState = TASK_A_START;
    
    switch(s_tState) {
        case TASK_A_START:
            s_tState = TASK_A_WAIT_EVENT;
            //break;
        
        case TASK_A_WAIT_EVENT:
            if(WAIT_EVENT(&s_tEventApple)){
                s_tState = TASK_A_PRINT;
            }
            break;
          
        case TASK_A_PRINT:
            if(fsm_rt_cpl == print_apple()){
                RESET_EVENT(&s_tEventApple);
                TASK_A_FSM_RESET();
                return fsm_rt_cpl; 
            }
            break;               
    }
    
    return fsm_rt_on_going;
}

#define TASK_B_FSM_RESET() do {s_tState = TASK_B_START;} while(0)
static fsm_rt_t task_b(void)
{
    static enum {
        TASK_B_START                    = 0,
        TASK_B_WAIT_EVENT,
        TASK_B_PRINT
    }s_tState = TASK_B_START;
    
    switch(s_tState) {
        case TASK_B_START:
            s_tState = TASK_B_WAIT_EVENT;
            //break;
        
        case TASK_B_WAIT_EVENT:
            if(WAIT_EVENT(&s_tEventOrange)){
                s_tState = TASK_B_PRINT;
            }
            break;
          
        case TASK_B_PRINT:
            if(fsm_rt_cpl == print_orange()){
                RESET_EVENT(&s_tEventOrange);
                TASK_B_FSM_RESET();
                return fsm_rt_cpl; 
            }
            break;               
    }
    
    return fsm_rt_on_going;
}

#define TASK_C_FSM_RESET() do {s_tState = TASK_C_START;} while(0)
static fsm_rt_t task_c(void)
{
    static enum {
        TASK_C_START            = 0,
        TASK_C_WAIT_EVENT,
        TASK_C_PRINT
    }s_tState = TASK_C_START;
    
    switch(s_tState) {
        case TASK_C_START:
            s_tState = TASK_C_WAIT_EVENT;
            //break;
        
        case TASK_C_WAIT_EVENT:
            if(WAIT_EVENT(&s_tEventWorld)){
                s_tState = TASK_C_PRINT;
            }
            break;
          
        case TASK_C_PRINT:
            if(fsm_rt_cpl == print_world()){
                RESET_EVENT(&s_tEventWorld);
                TASK_C_FSM_RESET();
                return fsm_rt_cpl; 
            }
            break; 
    }
    
    return fsm_rt_on_going;
}


#define PRINT_WORLD_RESET_FSM()     do { s_tState = PRINT_WORLD_START;} while(0)
static fsm_rt_t print_world(void)
{
    static enum {
        PRINT_WORLD_START = 0,
        PRINT_WORLD_INIT,
        PRINT_WORLD_SEND
    }s_tState = PRINT_WORLD_START;
    
    static uint8_t *s_pchString = (uint8_t *)"world\r\n";
    static print_str_t s_tPrintStruct;
    
    switch(s_tState) {
        case PRINT_WORLD_START:
            s_tState = PRINT_WORLD_INIT;
            //break;
            
        case PRINT_WORLD_INIT:
            if(INIT_SRT_OUTPUT(&s_tPrintStruct,s_pchString)){
                s_tState = PRINT_WORLD_SEND;
            }else {
                return fsm_rt_err;
            }
            break;
        
        case PRINT_WORLD_SEND:
            if(fsm_rt_cpl == print_string(&s_tPrintStruct)){
                PRINT_WORLD_RESET_FSM();
                return fsm_rt_cpl;
            } 
            break;
    }
        
    return fsm_rt_on_going;
}

#define PRINT_APPLE_RESET_FSM() do { s_tState = PRINT_APPLE_START; } while(0)
static fsm_rt_t print_apple(void)
{
    static enum {
        PRINT_APPLE_START = 0,
        PRINT_APPLE_INIT,
        PRINT_APPLE_SEND
    }s_tState = PRINT_APPLE_START;
    
    static uint8_t *s_pchString = (uint8_t *)"apple\r\n";
    static print_str_t s_tPrintStruct;
    
    switch(s_tState) {
        case PRINT_APPLE_START:
            s_tState = PRINT_APPLE_INIT;
            //break;
            
        case PRINT_APPLE_INIT:
            if(INIT_SRT_OUTPUT(&s_tPrintStruct,s_pchString)){
                s_tState = PRINT_APPLE_SEND;
            }else {
                return fsm_rt_err;
            }
            break;
        
        case PRINT_APPLE_SEND:
            if(fsm_rt_cpl == print_string(&s_tPrintStruct)){
                PRINT_APPLE_RESET_FSM();
                return fsm_rt_cpl;
            } 
            break;
    }
        
    return fsm_rt_on_going;
}

#define PRINT_ORANGE_RESET_FSM() do { s_tState = PRINT_ORANGE_START; } while(0)
static fsm_rt_t print_orange(void)
{
    static enum {
        PRINT_ORANGE_START = 0,
        PRINT_ORGNGE_INIT,
        PRINT_ORGNGE_SEND
    }s_tState = PRINT_ORANGE_START;
    static uint8_t *s_pchString = (uint8_t *)"orange\r\n";
    static print_str_t s_tPrintStruct;
    
    switch(s_tState) {
        case PRINT_ORANGE_START:
            s_tState = PRINT_ORGNGE_INIT;
            //break;
            
        case PRINT_ORGNGE_INIT:
            if(INIT_SRT_OUTPUT(&s_tPrintStruct,s_pchString)){
                s_tState = PRINT_ORGNGE_SEND;
            }else {
                return fsm_rt_err;
            }
            break;
        
        case PRINT_ORGNGE_SEND:
            if(fsm_rt_cpl == print_string(&s_tPrintStruct)){
                PRINT_ORANGE_RESET_FSM();
                return fsm_rt_cpl;
            } 
            break;
    }
        
    return fsm_rt_on_going;
}
static void system_init(void)
{
    Port_Init();
    serial_init();
}
