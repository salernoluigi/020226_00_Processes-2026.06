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
 * mousse.c
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "mousse.h"

uint32_t mousse_init(void)
{
	return 0;
}

static uint32_t mousse_timeout_callback(uint32_t	val0,uint32_t	val1)
{
	HAL_GPIO_WritePin(MOUSSE_PORT, MOUSSE_PIN, GPIO_PIN_RESET);
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,MOUSSE_VP,0);
	task_delay(50);
	global_timer_stop();
	return 0;
}

static uint32_t mousse_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	mousse_timeout_callback(0,0);
	return 0;
}

uint32_t mousse_set_out(uint32_t level)
{
	if ( level )
	{
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		global_timer_run();
		HAL_GPIO_WritePin(MOUSSE_PORT, MOUSSE_PIN, GPIO_PIN_SET);
		HYDRA_Struct.global_timer_elapsed_callback = mousse_timeout_callback;
		HYDRA_Struct.cleanup_function = mousse_cleanup_function;
	}
	else
	{
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		global_timer_stop();
		HAL_GPIO_WritePin(MOUSSE_PORT, MOUSSE_PIN, GPIO_PIN_RESET);
		HYDRA_Struct.global_timer_elapsed_callback = NULL;
	}
	return 0;
}
#endif //#ifndef	SAMPLE_PROCESSES_ENABLED

