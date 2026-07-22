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
 * jetpeel.c
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "jetpeel.h"

uint32_t jetpeel_init(void)
{
	return 0;
}

static uint32_t jetpeel_timeout_callback(uint32_t	val0,uint32_t	val1)
{
	HAL_GPIO_WritePin(JETPEEL_PUMP_PORT, JETPEEL_PUMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(JETPEEL_EV3WARIA_PORT, JETPEEL_EV3WARIA_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_RESET);
	HYDRA_Struct.jetpeel_enable = 0;
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,AIRPEN_VP,0);
	task_delay(50);
	global_timer_stop();
	return 0;
}

static uint32_t jetpeel_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	jetpeel_timeout_callback(0,0);
	return 0;
}

uint32_t jetpeel_set_out(uint32_t level)
{
	if ( level == 0 )
	{
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		global_timer_stop();
		HAL_GPIO_WritePin(JETPEEL_PUMP_PORT, JETPEEL_PUMP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(JETPEEL_EV3WARIA_PORT, JETPEEL_EV3WARIA_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_RESET);
		HYDRA_Struct.global_timer_elapsed_callback = NULL;
		HYDRA_Struct.jetpeel_enable = 0;
	}
	else
	{
		HYDRA_Struct.jetpeel_enable = 1;
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		HYDRA_Struct.global_timer_elapsed_callback = jetpeel_timeout_callback;
		HYDRA_Struct.cleanup_function = jetpeel_cleanup_function;

		HAL_GPIO_WritePin(JETPEEL_PUMP_PORT, JETPEEL_PUMP_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(JETPEEL_EV3WARIA_PORT, JETPEEL_EV3WARIA_PIN, GPIO_PIN_SET);
	}
	return 0;
}

uint32_t jetpeel_timer_call(void)
{
	if ( HYDRA_Struct.jetpeel_enable == 0 )
		return 0;
	if ( HYDRA_Struct.jetpeel_program <= 1 )
	{
		HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_SET);
		HYDRA_Struct.global_timer_elapsed_callback = jetpeel_timeout_callback;
	}

	if ( HYDRA_Struct.jetpeel_program == 2 )
	{
		HYDRA_Struct.global_timer_elapsed_callback = jetpeel_timeout_callback;
		HYDRA_Struct.jetpeel_time ++;
		if ( HYDRA_Struct.jetpeel_time < 5 )
		{
			HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_RESET);
			HYDRA_Struct.jetpeel_time = 0;
		}
	}
	if ( HYDRA_Struct.jetpeel_program == 3 )
	{
		HYDRA_Struct.global_timer_elapsed_callback = jetpeel_timeout_callback;
		HYDRA_Struct.jetpeel_time ++;
		if ( HYDRA_Struct.jetpeel_time < 10 )
		{
			HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(JETPEEL_EV_PORT, JETPEEL_EV_PIN, GPIO_PIN_RESET);
			HYDRA_Struct.jetpeel_time = 0;
		}
	}
	return 0;
}

uint32_t jetpeel_set_program(uint32_t level)
{
	HYDRA_Struct.jetpeel_program = level;
	HYDRA_Struct.jetpeel_time = 0;
	if ( HYDRA_Struct.jetpeel_program < 2 )
		HYDRA_Struct.jetpeel_program = 1;
	return 0;
}


#endif //#ifndef	SAMPLE_PROCESSES_ENABLED
