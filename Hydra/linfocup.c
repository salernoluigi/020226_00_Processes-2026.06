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
 * linfocup.c
 *
 *  Created on: Jul 22, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "linfocup.h"

uint16_t	linfocup_run=0;
uint16_t	intensity=0;
uint16_t	t_release=1;
uint16_t	t_su=1;
uint16_t	t_time_full = 2;
uint16_t	t_time_full_work = 2;

uint32_t linfocup_init(void)
{
	return 0;
}

static uint32_t linfocup_timer_callback(uint32_t	val0,uint32_t	val1)
{
	if ( linfocup_run == 0 )
		return 0;

	t_time_full_work++;
	if ( t_time_full_work < t_su)
	{
		HAL_GPIO_WritePin(LINFOCUP_EV3WARIA_PORT, LINFOCUP_EV3WARIA_PIN, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LINFOCUP_EV3WARIA_PORT, LINFOCUP_EV3WARIA_PIN, GPIO_PIN_SET);
	}
	if ( t_time_full_work >= t_time_full)
	{
		HAL_GPIO_WritePin(LINFOCUP_EV3WARIA_PORT, LINFOCUP_EV3WARIA_PIN, GPIO_PIN_RESET);
		t_time_full_work=0;
	}
	return 0;
}

static uint32_t linfocup_timeout_callback(uint32_t	val0,uint32_t	val1)
{
	intensity=t_release=t_su=0;
	HAL_GPIO_WritePin(LINFOCUP_PUMP_PORT, LINFOCUP_PUMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINFOCUP_EV2CAP_PORT, LINFOCUP_EV2CAP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINFOCUP_EV3WARIA_PORT, LINFOCUP_EV3WARIA_PIN, GPIO_PIN_RESET);

	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,CUPPING_VP,0);
	task_delay(50);
	global_timer_stop();
	return 0;
}

static uint32_t linfocup_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	return 	linfocup_timeout_callback(0,0);
}

uint32_t	linfocup_set_intensity(uint16_t	data1_val)
{
	intensity = (Pwm_TIM15_Control.period / 10 ) * (11 - data1_val);
	pwm_set_width(&Pwm_TIM15_Control,intensity,TIM_CHANNEL_1);
	return 0;
}

uint32_t	linfocup_set_release(uint16_t	data1_val)
{
	t_release = data1_val;
	t_time_full = t_su + t_release;
	return 0;
}

uint32_t	linfocup_set_su(uint16_t	data1_val)
{
	t_su = data1_val;
	t_time_full = t_su + t_release;
	return 0;
}

uint32_t	linfocup_set_out(uint16_t	data1_val)
{
	if ( data1_val )
	{
		set_gpio_mode(LINFOCUP_PROP_PORT,LINFOCUP_PROP_PIN,MODE_AF);

		if ( intensity == 0 )
			intensity = Pwm_TIM15_Control.period / 10;

		pwm_set_width(&Pwm_TIM15_Control,intensity,TIM_CHANNEL_1);
		pwm_start(&Pwm_TIM15_Control,TIM_CHANNEL_1);

		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		global_timer_run();
		HYDRA_Struct.global_timer_elapsed_callback = linfocup_timeout_callback;
		HYDRA_Struct.global_timer_callback = linfocup_timer_callback;
		HYDRA_Struct.cleanup_function = linfocup_cleanup_function;
		t_time_full_work=0;
		linfocup_run = 1;
	}
	else
	{
		HAL_GPIO_WritePin(LINFOCUP_PUMP_PORT, LINFOCUP_PUMP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LINFOCUP_EV2CAP_PORT, LINFOCUP_EV2CAP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LINFOCUP_EV3WARIA_PORT, LINFOCUP_EV3WARIA_PIN, GPIO_PIN_RESET);
		pwm_stop(&Pwm_TIM15_Control,TIM_CHANNEL_1);

		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		global_timer_stop();
		intensity=t_release=t_su=0;
		set_gpio_mode(LINFOCUP_PROP_PORT,LINFOCUP_PROP_PIN,MODE_OUTPUT);
		linfocup_run = 0;
		//reset_time_values();
	}
	return 0;
}
#endif //#ifndef	SAMPLE_PROCESSES_ENABLED


