/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : A_os
*/
/*
 * process_1.c
 *
 *  Created on: Mar 13, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

#ifndef	SAMPLE_PROCESSES_ENABLED
uint32_t prescaler = 960;
void stepper_callback(uint32_t value)
{
	stepper_set_prescaler(&Stepper_Control,prescaler);
}

void process_1_init(uint32_t process_id)
{
	hydra_register_devices();
}

uint8_t timbuf[32];

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	count=0;
	create_timer(TIMER_ID_0,TIM_TICK,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	adc_start(&ADC_Drv);
	uart_start_receive(&Uart3_LCD_Drv);
	global_timer_init();
	global_timer_stop();
	HAL_GPIO_WritePin(SLEEP_3G_GPIO_Port, SLEEP_3G_Pin, GPIO_PIN_RESET);

	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_ADC1_IRQ | EVENT_UART3_IRQ | EVENT_SW_MODULES);
		get_wakeup_flags(&wakeup,&flags);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			process_led();
			count++;
			if ( count >= 10 )
			{
				global_timer_run();
				count=0;
			}
			jetpeel_timer_call();
		}
		if (( wakeup & WAKEUP_FROM_ADC1_IRQ) == WAKEUP_FROM_ADC1_IRQ)
		{
			get_adc_values();
		}
		if (( wakeup & WAKEUP_FROM_LCD_UART_IRQ) == WAKEUP_FROM_LCD_UART_IRQ)
		{
			if ( uart_get_rxlen(&Uart3_LCD_Drv) > 2)
				lcd_parser(&Uart3_LCD_Drv);
		}
		if (( wakeup & WAKEUP_FROM_SW_MODULES_IRQ) == WAKEUP_FROM_SW_MODULES_IRQ)
		{
			if ( Stepper_Control.stepper_direction == STEPPER_DIRECTION_FORWARD )
				Stepper_Control.number_of_steps = 0x0fffffff;
		}
	}
}
#endif //#ifdef SAMPLE_PROCESSES_ENABLED



