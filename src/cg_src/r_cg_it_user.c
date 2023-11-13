/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_it_user.c
* Version      : Code Generator for RL78/G10 V1.05.05.02 [08 Nov 2021]
* Device(s)    : R5F10Y47
* Tool-Chain   : CCRL
* Description  : This file implements device driver for IT module.
* Creation Date: 2023/11/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_it_interrupt(vect=INTIT)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile bool gMILLISECONDS_TIMER_EVENT_OCCURRED_FLAG = false;
//
volatile static uint8_t gTIMER_EVENT_COUNTER = 0U;
//
static inline void upcount_timer_event_counter(void) {
	// タイマー割り込みを5分周する
	gTIMER_EVENT_COUNTER++;
	if (gTIMER_EVENT_COUNTER >= 5U) {
		gMILLISECONDS_TIMER_EVENT_OCCURRED_FLAG = true;
		gTIMER_EVENT_COUNTER = 0U;
	}
}
//
#define MIN_ROTATION_COUNT  (-100)
#define MAX_ROTATION_COUNT  (100)
volatile int8_t gROTATION_COUNTER = 0;
//
static inline void countup_rotation_counter(void) {
	if (gROTATION_COUNTER < MAX_ROTATION_COUNT) {
		gROTATION_COUNTER++;
	}
}
//
static inline void countdown_rotation_counter(void) {
	if (gROTATION_COUNTER > MIN_ROTATION_COUNT) {
		gROTATION_COUNTER--;
	}
}
#define ENCORDER_B_BIT  (P0_bit.no0)
#define ENCORDER_A_BIT  (P0_bit.no1)
#define ENCORDER_AB_BIT  (P0 & 3)
//
static void sample_encoder(void) {
	static const int8_t dir[] = { 0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1,
			1, 0 };
	static int8_t i;
	int8_t n;

	i = (i << 2) + ENCORDER_AB_BIT;
	n = dir[i & 15];
	if (n < 0) {
		countdown_rotation_counter();
	} else if (n > 0) {
		countup_rotation_counter();
	}
}
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_it_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_it_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
	sample_encoder();
	// タイマー割り込みを5分周する
	upcount_timer_event_counter();
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
