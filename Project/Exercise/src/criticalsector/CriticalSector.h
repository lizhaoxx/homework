#ifndef __CRITICAL_SECTOR__
#define __CRITICAL_SECTOR__
/******************************************************************************
  * Test 3A �ٽ���
  * ����֪ʶ��Ҫ��
  * 1��	CRITICAL_SECTOR�Ļ���֪ʶ
  * typedef struct {
  * bool bLocked;
  * }critical_sector_t;
  * typedef critical_sector_t mutex_t;
  * 2��	CRITICAL_SECTOR�Ļ�������
  * a)	Enter��	ENTER_CRITICAL_SECTOR(__CRITICAL)
  * b)	Leave: 	LEAVE_CRITICAL_SECTOR(__CRITICAL)
  * c)	Init:		INIT_CRITICAL_SECTOR(__CRITICAL)������ֵ��bool�ͣ�����true��ʾ�ɹ������ٽ���
  * ע������Ĳ����궼Ҫ����Ĳ�����ָ�룬����ENTER_CRITICAL_SECTOR(&s_tCritical);
  * ����Ҫ��
  * 1��	��д����״̬��print_apple(), print_orange()��print_world()�ֱ�����������apple\r\n��, ��orange\r\n��, ��world\r\n����
  * Ҫ������״̬��������������ֱ�ӵĶ�״̬���ģʽ�����硱apple\r\n����Ӧ����7��״̬��ɣ�ÿ��״ֻ̬�������һ���ַ���
  * 2��	��д��������������tast_a(), task_b()��task_c()�ֱ��������״̬��������֤������ʵ�������
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
  * 	��
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
#include "stm32f10x.h"
#include <stdbool.h>
#include <stdlib.h>
/* extern macro -------------------------------------------------------------*/
#define ENTER_CRITICAL_SECTOR(__CRITICAL)           enter_critical_sector(__CRITICAL)
#define LEAVE_CRITICAL_SECTOR(__CRITICAL)           leave_critical_sector(__CRITICAL)
#define INIT_CRITICAL_SECTOR(__CRITICAL)            init_critical_sector(__CRITICAL)


/* extern typedef -------------------------------------------------------------*/
//! @{
typedef struct {
    bool bLocked;
}critical_sector_t;
//! @}


/* extern variables ---------------------------------------------------------*/

/* extern function prototypes -----------------------------------------------*/

/* extern functions ---------------------------------------------------------*/
bool enter_critical_sector(critical_sector_t *ptSignal);
void leave_critical_sector(critical_sector_t *ptSignal);
void init_critical_sector(critical_sector_t *ptSignal);
#endif

