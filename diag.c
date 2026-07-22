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
 * diag.c
 *
 *  Created on: Jun 19, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

#ifndef	SAMPLE_PROCESSES_ENABLED


void diag_init(void)
{
	Pwm_TIM1_Control.status = (PWM_CHANNEL_CH1|PWM_CHANNEL_CH2|PWM_CHANNEL_CH3|PWM_CHANNEL_CH4);
	Pwm_TIM3_Control.status = (PWM_CHANNEL_CH1|PWM_CHANNEL_CH2|PWM_CHANNEL_CH3|PWM_CHANNEL_CH4);
	Pwm_TIM4_Control.status = (PWM_CHANNEL_CH1|PWM_CHANNEL_CH2|PWM_CHANNEL_CH3|PWM_CHANNEL_CH4);
	Pwm_TIM5_Control.status = (PWM_CHANNEL_CH1|PWM_CHANNEL_CH2|PWM_CHANNEL_CH3|PWM_CHANNEL_CH4);
	Pwm_TIM15_Control.status = (PWM_CHANNEL_CH1|PWM_CHANNEL_CH2|PWM_CHANNEL_CH3|PWM_CHANNEL_CH4);

	pwm_set_prescaler(&Pwm_TIM1_Control,4800);
	pwm_set_prescaler(&Pwm_TIM3_Control,4800);
	pwm_set_prescaler(&Pwm_TIM4_Control,4800);
	pwm_set_prescaler(&Pwm_TIM5_Control,4800);
	pwm_set_prescaler(&Pwm_TIM15_Control,4800);

	pwm_start_all_enabled(&Pwm_TIM1_Control);
	pwm_start_all_enabled(&Pwm_TIM3_Control);
	pwm_start_all_enabled(&Pwm_TIM4_Control);
	pwm_start_all_enabled(&Pwm_TIM5_Control);
	pwm_start_all_enabled(&Pwm_TIM15_Control);
}

uint8_t		diag_toggle = 0;
uint32_t	pwm_w = 0x8000 , pwm_wdir=0;
void diag_at_timer(void)
{
	if ( diag_toggle)
	{
		HAL_GPIO_WritePin(AUX1_OUT_NOPWM_GPIO_Port, AUX1_OUT_NOPWM_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AUX2_OUT_NOPWM_GPIO_Port, AUX2_OUT_NOPWM_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AC_CMD1_GPIO_Port, AC_CMD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AC_CMD2_GPIO_Port, AC_CMD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(POWERKEY_3G_GPIO_Port, POWERKEY_3G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SLEEP_3G_GPIO_Port, SLEEP_3G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(M3G_CONNECTED_GPIO_Port, M3G_CONNECTED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HYDROGEN_9V_GPIO_Port, HYDROGEN_9V_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(AUX1_OUT_NOPWM_GPIO_Port, AUX1_OUT_NOPWM_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AUX2_OUT_NOPWM_GPIO_Port, AUX2_OUT_NOPWM_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AC_CMD1_GPIO_Port, AC_CMD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AC_CMD2_GPIO_Port, AC_CMD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(POWERKEY_3G_GPIO_Port, POWERKEY_3G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SLEEP_3G_GPIO_Port, SLEEP_3G_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(M3G_CONNECTED_GPIO_Port, M3G_CONNECTED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HYDROGEN_9V_GPIO_Port, HYDROGEN_9V_Pin, GPIO_PIN_RESET);
	}
	diag_toggle++;
	diag_toggle &= 1;
	pwm_set_width(&Pwm_TIM1_Control,pwm_w,TIM_CHANNEL_1);
	pwm_set_width(&Pwm_TIM1_Control,pwm_w,TIM_CHANNEL_2);
	pwm_set_width(&Pwm_TIM1_Control,pwm_w,TIM_CHANNEL_3);
	pwm_set_width(&Pwm_TIM1_Control,pwm_w,TIM_CHANNEL_4);
	pwm_set_width(&Pwm_TIM3_Control,pwm_w,TIM_CHANNEL_1);
	pwm_set_width(&Pwm_TIM3_Control,pwm_w,TIM_CHANNEL_2);
	pwm_set_width(&Pwm_TIM3_Control,pwm_w,TIM_CHANNEL_3);
	pwm_set_width(&Pwm_TIM3_Control,pwm_w,TIM_CHANNEL_4);
	pwm_set_width(&Pwm_TIM4_Control,pwm_w,TIM_CHANNEL_1);
	pwm_set_width(&Pwm_TIM4_Control,pwm_w,TIM_CHANNEL_2);
	pwm_set_width(&Pwm_TIM4_Control,pwm_w,TIM_CHANNEL_3);
	pwm_set_width(&Pwm_TIM4_Control,pwm_w,TIM_CHANNEL_4);
	pwm_set_width(&Pwm_TIM5_Control,pwm_w,TIM_CHANNEL_1);
	pwm_set_width(&Pwm_TIM5_Control,pwm_w,TIM_CHANNEL_2);
	pwm_set_width(&Pwm_TIM5_Control,pwm_w,TIM_CHANNEL_3);
	pwm_set_width(&Pwm_TIM5_Control,pwm_w,TIM_CHANNEL_4);
	pwm_set_width(&Pwm_TIM15_Control,pwm_w,TIM_CHANNEL_1);
	pwm_set_width(&Pwm_TIM15_Control,pwm_w,TIM_CHANNEL_2);
	if ( pwm_wdir )
	{
		pwm_w +=0x1000;
		if ( pwm_w > 0xfd00 )
			pwm_wdir = 0;
	}
	else
	{
		pwm_w -=0x1000;
		if ( pwm_w < 0x2000 )
			pwm_wdir = 1;
	}


}


#endif // #ifndef	SAMPLE_PROCESSES_ENABLED


