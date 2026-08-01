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
 * hydrapen.c
 *
 *  Created on: Jul 25, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "hydrapen.h"

uint16_t	hydrapen_status=0;

uint32_t hydrapen_init(void)
{
	return 0;
}

static void hydrapen_reset_ports(void)
{
	HAL_GPIO_WritePin(HYDRAPEN_PUMP_PORT, HYDRAPEN_PUMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_PUMP24V_PORT, HYDRAPEN_PUMP24V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_EV3_VACUUM_PORT, HYDRAPEN_EV3_VACUUM_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_RESET);
}


static uint32_t hydrapen_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	hydrapen_status = 0;
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	global_timer_stop();
	hydrapen_reset_ports();
	set_gpio_mode(HYDRAPEN_PROP_VACUUM_PORT,HYDRAPEN_PROP_VACUUM_PIN,MODE_OUTPUT);
	set_gpio_mode(HYDRAPEN_PROP_PRODUCT_PORT,HYDRAPEN_PROP_PRODUCT_PIN,MODE_OUTPUT);
	set_gpio_mode(HYDRAPEN_EV3_VACUUM_PORT,HYDRAPEN_EV3_VACUUM_PIN,MODE_OUTPUT);
	set_gpio_mode(HYDRAPEN_PUMP24V_PORT,HYDRAPEN_PUMP24V_PIN,MODE_OUTPUT);

	HYDRA_Struct.global_timer_elapsed_callback = NULL;
	HYDRA_Struct.cleanup_function = NULL;
	HYDRA_Struct.pump_status = 0;
	HYDRA_Struct.hydrapen_running = 0;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,HYDRAPEN_VP,0);
	return 	0;
}

static uint32_t hydrapen_timeout_callback(uint32_t	val0,uint32_t	val1)
{
	hydrapen_status = 0;
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	global_timer_stop();
	hydrapen_reset_ports();
	HYDRA_Struct.pump_status = 0;
	HYDRA_Struct.hydrapen_running = 0;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,HYDRAPEN_VP,0);
	return 	0;
}

uint32_t	hydrapen_set_vacuum(uint16_t	data1_val)
{
	if ( hydrapen_status == 0 )
		return 0;
	switch(data1_val)
	{
	case 0 :
		pwm_stop(&Pwm_TIM15_Control,TIM_CHANNEL_1);
		return 0;
		break;
	case 1 :
		pwm_set_width(&Pwm_TIM15_Control,Pwm_TIM15_Control.period/3,TIM_CHANNEL_1);
		break;
	case 2 :
		pwm_set_width(&Pwm_TIM15_Control,Pwm_TIM15_Control.period/2,TIM_CHANNEL_1);
		break;
	case 3 :
		pwm_set_width(&Pwm_TIM15_Control,(Pwm_TIM15_Control.period/1)+10,TIM_CHANNEL_1);
		break;
	}
	pwm_start(&Pwm_TIM15_Control,TIM_CHANNEL_1);
	return 0;
}

uint32_t	hydrapen_set_prod(uint16_t	data1_val)
{
	if ( hydrapen_status == 0 )
		return 0;
	switch(data1_val)
	{
	case 0 :
		pwm_stop(&Pwm_TIM15_Control,TIM_CHANNEL_2);
		return 0;
		break;
	case 1 :
		pwm_set_width(&Pwm_TIM15_Control,Pwm_TIM15_Control.period/3,TIM_CHANNEL_2);
		break;
	case 2 :
		pwm_set_width(&Pwm_TIM15_Control,Pwm_TIM15_Control.period/2,TIM_CHANNEL_2);
		break;
	case 3 :
		pwm_set_width(&Pwm_TIM15_Control,(Pwm_TIM15_Control.period/1)+10,TIM_CHANNEL_2);
		break;
	}
	set_gpio_mode(HYDRAPEN_PROP_PRODUCT_PORT,HYDRAPEN_PROP_PRODUCT_PIN,MODE_AF);
	pwm_start(&Pwm_TIM15_Control,TIM_CHANNEL_2);return 0;
}

uint32_t	hydrapen_treatment_sel(uint16_t	data1_val)
{
	switch(data1_val)
	{
	case 1:
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_SET);
		break;
	default:
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_A_PORT, HYDRAPEN_BOTTLE_A_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_B_PORT, HYDRAPEN_BOTTLE_B_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_C_PORT, HYDRAPEN_BOTTLE_C_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDRAPEN_BOTTLE_H2O_PORT, HYDRAPEN_BOTTLE_H2O_PIN, GPIO_PIN_RESET);
		break;
	}
	return 0;
}

uint32_t hydrapen_start(uint32_t level)
{
	if ( level == 1 )
	{
		hydrapen_status = 1;
		task_delay(50);
		send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,HYDRAPEN_ALARM_VP,1);
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		global_timer_run();
		HYDRA_Struct.global_timer_elapsed_callback = hydrapen_timeout_callback;
		HYDRA_Struct.cleanup_function = hydrapen_cleanup_function;
		set_gpio_mode(VORTEX_PROP_PORT,VORTEX_PROP_PIN,MODE_OUTPUT);
		HAL_GPIO_WritePin(HYDRAPEN_PUMP_PORT, HYDRAPEN_PUMP_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDRAPEN_PUMP24V_PORT, HYDRAPEN_PUMP24V_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDRAPEN_EV3_VACUUM_PORT, HYDRAPEN_EV3_VACUUM_PIN, GPIO_PIN_SET);
		set_gpio_mode(HYDRAPEN_PROP_VACUUM_PORT,HYDRAPEN_PROP_VACUUM_PIN,MODE_AF);
		set_gpio_mode(HYDRAPEN_PROP_PRODUCT_PORT,HYDRAPEN_PROP_PRODUCT_PIN,MODE_AF);
		set_gpio_mode(HYDRAPEN_EV3_VACUUM_PORT,HYDRAPEN_EV3_VACUUM_PIN,MODE_OUTPUT);
		set_gpio_mode(HYDRAPEN_PUMP24V_PORT,HYDRAPEN_PUMP24V_PIN,MODE_OUTPUT);

		HYDRA_Struct.pump_status = 1;
		HYDRA_Struct.hydrapen_running = 1;
	}
	else
	{
		hydrapen_status = 0;
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		global_timer_stop();
		HYDRA_Struct.global_timer_elapsed_callback = NULL;
		HYDRA_Struct.cleanup_function = NULL;
		hydrapen_cleanup_function(0,0);
		HYDRA_Struct.pump_status = 0;
		HYDRA_Struct.hydrapen_running = 0;
	}
	return 0;
}
#endif //#ifndef	SAMPLE_PROCESSES_ENABLED
