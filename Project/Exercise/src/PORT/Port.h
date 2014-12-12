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


#ifndef __PORT_H__
#define __PORT_H__
/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"

/*============================ MACROS ========================================*/
#define IS_KEY2_DOWN()   (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
#define IS_KEY2_UP()     (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
#define IS_KEY1_DOWN()   (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
#define IS_KEY1_UP()     (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))

#define LED1_ON()        do{GPIOF->BRR = GPIO_Pin_6;}while(0)
#define LED1_OFF()       do{GPIOF->BSRR = GPIO_Pin_6;}while(0)

#define LED2_ON()        do{GPIOF->BRR = GPIO_Pin_7;}while(0)
#define LED2_OFF()       do{GPIOF->BSRR = GPIO_Pin_7;}while(0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void Port_Init(void);
extern void LEDBreath(void);

#endif
