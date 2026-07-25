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
 * vortex.c
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "vortex.h"
#include "common.h"

uint16_t	last_stepper_speed=0;
uint16_t	last_motor_speed=0;
uint16_t	vortex_status=0;
uint32_t	vortex_set_dose(uint16_t	data1_val)
{
	switch ( data1_val )
	{
	case 0:
		stepper_stop(&Stepper_Control,TIM_CHANNEL_1);
		break;
	case 1:
		stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MIN);
		break;
	case 2:
		stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MED);
		break;
	case 3:
		stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MAX);
		break;
	}
	if (( last_stepper_speed == 0 ) && (vortex_status == 1 ))
		stepper_start(&Stepper_Control,TIM_CHANNEL_1,0,STEPPER_DIRECTION_FORWARD);

	last_stepper_speed = data1_val;
	return 0;
}

uint32_t	vortex_set_vacuum(uint16_t	data1_val)
{
	if ( vortex_status == 0 )
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
	set_gpio_mode(VORTEX_PROP_PORT,VORTEX_PROP_PIN,MODE_AF);
	pwm_start(&Pwm_TIM15_Control,TIM_CHANNEL_1);
	return 0;
}

uint32_t	vortex_set_speed(uint16_t	data1_val)
{
	if ( vortex_status == 0 )
		return 0;
	switch(data1_val)
	{
	case 0 :
		pwm_stop(&Pwm_TIM3_Control,TIM_CHANNEL_2);
		last_motor_speed = 0;
		return 0;
		break;
	case 1 :
		pwm_set_width(&Pwm_TIM3_Control,Pwm_TIM3_Control.period/3,TIM_CHANNEL_2);
		last_motor_speed = Pwm_TIM3_Control.period/3;
		break;
	case 2 :
		pwm_set_width(&Pwm_TIM3_Control,Pwm_TIM3_Control.period/2,TIM_CHANNEL_2);
		last_motor_speed = Pwm_TIM3_Control.period/2;
		break;
	case 3 :
		pwm_set_width(&Pwm_TIM3_Control,(Pwm_TIM3_Control.period/1)+100,TIM_CHANNEL_2);
		last_motor_speed = (Pwm_TIM3_Control.period/1) + 100;
		break;
	}
	set_gpio_mode(VORTEX_MOTORPWM_PORT,VORTEX_MOTORPWM_PIN,MODE_AF);
	pwm_start(&Pwm_TIM3_Control,TIM_CHANNEL_2);

	return 0;
}

uint32_t vortex_init(void)
{
	return 0;
}

static uint32_t vortex_cleanup_function(uint32_t	val0,uint32_t	val1)
{
	vortex_status = 0;

	HAL_GPIO_WritePin(VORTEX_PUMP_PORT, VORTEX_PUMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(VORTEX_EV3V_VACUUM_PORT, VORTEX_EV3V_VACUUM_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(VORTEX_EV3V_HYDRA_PORT, VORTEX_EV3V_HYDRA_PIN, GPIO_PIN_RESET);
	pwm_stop(&Pwm_TIM15_Control,TIM_CHANNEL_1);

	set_gpio_mode(VORTEX_PROP_PORT,VORTEX_PROP_PIN,MODE_OUTPUT);
	set_gpio_mode(VORTEX_MOTORPWM_PORT,VORTEX_MOTORPWM_PIN,MODE_OUTPUT);

	HAL_GPIO_WritePin(VORTEX_PROP_PORT, VORTEX_PROP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(VORTEX_MOTORPWM_PORT, VORTEX_MOTORPWM_PIN, GPIO_PIN_RESET);

	pwm_stop(&Pwm_TIM3_Control,TIM_CHANNEL_2);
	last_motor_speed = 0;

	//if ( last_stepper_speed )
	{
		stepper_stop(&Stepper_Control,TIM_CHANNEL_1);
		stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_RECOVERY);
		stepper_start(&Stepper_Control,TIM_CHANNEL_1,50,STEPPER_DIRECTION_REVERSE);
	}
	last_stepper_speed = 0;
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,VORTEX_VP,0);
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,VORTEX_DOSE_VP,0);
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,VORTEX_VACUUM_VP,0);
	task_delay(50);
	send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,VORTEX_SPEED_VP,0);
	task_delay(50);
	HYDRA_Struct.pump_status = 0;
	return 0;
}

uint32_t vortex_start(uint32_t level)
{
	if ( level == 1 )
	{
		HAL_GPIO_WritePin(VORTEX_PUMP_PORT, VORTEX_PUMP_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(VORTEX_EV3V_VACUUM_PORT, VORTEX_EV3V_VACUUM_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(VORTEX_EV3V_HYDRA_PORT, VORTEX_EV3V_HYDRA_PIN, GPIO_PIN_SET);
		HYDRA_Struct.cleanup_function = vortex_cleanup_function;
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
		vortex_status = 1;
		switch ( last_stepper_speed )
		{
		case 1:
			stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MIN);
			stepper_start(&Stepper_Control,TIM_CHANNEL_1,0,STEPPER_DIRECTION_FORWARD);
			break;
		case 2:
			stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MED);
			stepper_start(&Stepper_Control,TIM_CHANNEL_1,0,STEPPER_DIRECTION_FORWARD);
			break;
		case 3:
			stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_MAX);
			stepper_start(&Stepper_Control,TIM_CHANNEL_1,0,STEPPER_DIRECTION_FORWARD);
			break;
		default:
			vortex_status = 0;
			break;
		}
		set_gpio_mode(VORTEX_PROP_PORT,VORTEX_PROP_PIN,MODE_AF);
		set_gpio_mode(VORTEX_MOTORPWM_PORT,VORTEX_MOTORPWM_PIN,MODE_AF);
		HYDRA_Struct.pump_status = 1;

	}
	else
	{
		HAL_GPIO_WritePin(VORTEX_PUMP_PORT, VORTEX_PUMP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(VORTEX_EV3V_VACUUM_PORT, VORTEX_EV3V_VACUUM_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(VORTEX_EV3V_HYDRA_PORT, VORTEX_EV3V_HYDRA_PIN, GPIO_PIN_RESET);
		HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
		//if ( last_stepper_speed )
		{
			stepper_stop(&Stepper_Control,TIM_CHANNEL_1);
			stepper_set_prescaler(&Stepper_Control,VORTEX_SPEED_RECOVERY);
			stepper_start(&Stepper_Control,TIM_CHANNEL_1,50,STEPPER_DIRECTION_REVERSE);
		}
		set_gpio_mode(VORTEX_PROP_PORT,VORTEX_PROP_PIN,MODE_OUTPUT);
		set_gpio_mode(VORTEX_MOTORPWM_PORT,VORTEX_MOTORPWM_PIN,MODE_OUTPUT);

		HAL_GPIO_WritePin(VORTEX_PROP_PORT, VORTEX_PROP_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(VORTEX_MOTORPWM_PORT, VORTEX_MOTORPWM_PIN, GPIO_PIN_RESET);
		pwm_stop(&Pwm_TIM3_Control,TIM_CHANNEL_2);

		vortex_status = 0;
		HYDRA_Struct.pump_status = 0;

	}
	return 0;
}

#endif //#ifndef	SAMPLE_PROCESSES_ENABLED
