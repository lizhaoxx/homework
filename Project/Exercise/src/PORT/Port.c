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
#define LED2_ON()        do{GPIOF->BRR = GPIO_Pin_7;}while(0)
#define LED2_OFF()       do{GPIOF->BSRR = GPIO_Pin_7;}while(0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static void GPIO_LED_Init(void);
static void GPIO_Key_Init(void);

void Port_Init(void)
{
    GPIO_LED_Init();
    GPIO_Key_Init();
}

void LEDBreath(void)
{
    static uint16_t s_hwCount1 = 0;
    static uint16_t s_hwCount2 = 0;
    static uint8_t  s_chFlag = 0;
    uint16_t Mask   = 0x3ff;

    if((s_hwCount1 & Mask) < s_hwCount2){
        LED2_ON();
    }else{
        LED2_OFF();
    }
    s_hwCount1++;

    if(!(s_hwCount1 & Mask)){
        if(!s_chFlag){
            s_hwCount2 += 10;
        }else{
            s_hwCount2 -= 10;
        }

        if((s_hwCount2 > Mask) && (!s_chFlag)){
            s_chFlag = 1;
        }else if((!s_hwCount2 ) && (s_chFlag)){
            s_chFlag = 0;
        }

        s_hwCount2 &= Mask;
    }
}

static void GPIO_Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

static void GPIO_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIOF->BSRR = GPIO_Pin_6;
    GPIOF->BSRR = GPIO_Pin_7;
}

