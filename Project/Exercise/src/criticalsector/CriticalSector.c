/**
  ******************************************************************************
  * @file    USART/Printf/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body
  ******************************************************************************
  * Test 3A 临界区
  * 背景知识提要：
  * 1、	CRITICAL_SECTOR的基本知识
  * typedef struct {
  * bool bLocked;
  * }critical_sector_t;
  * typedef critical_sector_t mutex_t;
  * 2、	CRITICAL_SECTOR的基本操作
  * a)	Enter：	ENTER_CRITICAL_SECTOR(__CRITICAL)
  * b)	Leave: 	LEAVE_CRITICAL_SECTOR(__CRITICAL)
  * c)	Init:		INIT_CRITICAL_SECTOR(__CRITICAL)，返回值是bool型，返回true表示成功进入临界区
  * 注：这里的参数宏都要求传入的参数是指针，例如ENTER_CRITICAL_SECTOR(&s_tCritical);
  * 基本要求：
  * 1、	编写三个状态机print_apple(), print_orange()和print_world()分别独立的输出”apple\r\n”, “orange\r\n”, “world\r\n”。
  * 要求三个状态机必须采用最简单最直接的多状态输出模式，比如”apple\r\n”就应该由7个状态组成，每个状态只负责输出一个字符。
  * 2、	编写三个独立的任务tast_a(), task_b()和task_c()分别调用三个状态机，并保证输出单词的完整性
  * Framework
  * 
  * static fsm_rt_t print_apple(void);
  * static fsm_rt_t print_orange(void);
  * static fsm_rt_t print_world(void);
  * static fsm_rt_t task_a(critical_sector_t *ptCritical);
  * static fsm_rt_t task_b(critical_sector_t *ptCritical);
  * static fsm_rt_t task_c(critical_sector_t *ptCritical);
  * 
  * 
  * void main(void)
  * {
  * 	critical_sector_t tPrintCriticalSector;
  * 	INIT_CRITICAL_SECTOR(&tPrintCriticalSector);
  * 	…
  * 	while(1) {
  * 		breath_led();
  * 		task_a(&tPrintCriticalSector);
  * 		task_b(&tPrintCriticalSector);
  * 		task_c(&tPrintCriticalSector);
  * 	}
  * }
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "CriticalSector.h"

/* Private macro -------------------------------------------------------------*/

/* Private typedef -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
bool enter_critical_sector(critical_sector_t *ptSignal)
{
    if((NULL != ptSignal) && (!(ptSignal ->bLocked))){
        ptSignal -> bLocked = true;
        return true;
    }
    return false;
}

void leave_critical_sector(critical_sector_t *ptSignal)
{
    if(NULL != ptSignal) {
        ptSignal -> bLocked = false;
    }
}
void init_critical_sector(critical_sector_t *ptSignal)
{
    if(NULL != ptSignal) {
        ptSignal -> bLocked = false;
    }
}
