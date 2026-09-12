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
 * airpen.c
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */
#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "airpen.h"

uint32_t airpen_init(void)
{
	return 0;
}

static uint32_t airpen_timeout_callback(uint32_t	val0,uint32_t	val1)
{
	HAL_GPIO_WritePin(AIRPEN_PUMP_PORT, AIRPEN_PUMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIRPEN_EV3WARIA_PORT, AIRPEN_EV3WARIA_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIRPEN_EV_PORT, AIRPEN_EV_PIN, GPIO_PIN_RESET);
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,AIRPEN_VP,0);
	task_delay(50);
	global_timer_stop();
	HYDRA_Struct.airpen_enable = 0;
	HYDRA_Struct.pump_status = 0;
	return 0;
}


static uint32_t airpen_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	airpen_timeout_callback(0,0);
	return 0;
}


uint32_t airpen_set_out(uint32_t level)
{
	if ( level )
	{
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		global_timer_run();
		HAL_GPIO_WritePin(AIRPEN_PUMP_PORT, AIRPEN_PUMP_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIRPEN_EV3WARIA_PORT, AIRPEN_EV3WARIA_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIRPEN_EV_PORT, AIRPEN_EV_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIRPEN_PUMP24V_PORT, AIRPEN_PUMP24V_PIN, GPIO_PIN_SET);
		set_gpio_mode(AIRPEN_PUMP24V_PORT,AIRPEN_PUMP24V_PIN,MODE_OUTPUT);
		HYDRA_Struct.global_timer_elapsed_callback = airpen_timeout_callback;
		HYDRA_Struct.cleanup_function = airpen_cleanup_function;
		HYDRA_Struct.airpen_enable = 1;
		HYDRA_Struct.pump_status = 1;
	}
	else
	{
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		global_timer_stop();
		HAL_GPIO_WritePin(AIRPEN_PUMP_PORT, AIRPEN_PUMP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIRPEN_EV3WARIA_PORT, AIRPEN_EV3WARIA_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIRPEN_EV_PORT, AIRPEN_EV_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIRPEN_PUMP24V_PORT, AIRPEN_PUMP24V_PIN, GPIO_PIN_RESET);
		set_gpio_mode(AIRPEN_PUMP24V_PORT,AIRPEN_PUMP24V_PIN,MODE_AF);
		HYDRA_Struct.global_timer_elapsed_callback = NULL;
		HYDRA_Struct.cleanup_function = NULL;
		HYDRA_Struct.airpen_enable = 0;
		HYDRA_Struct.pump_status = 0;
	}
	return 0;
}

#endif //#ifndef	SAMPLE_PROCESSES_ENABLED


