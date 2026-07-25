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
 * common.c
 *
 *  Created on: Jul 25, 2026
 *      Author: MARFIX
 */


#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "common.h"

uint16_t	clast_stepper_speed=0;
uint16_t	clast_stepper_status=0;
uint16_t	proportional_status=0;

uint32_t	stepper_set_speed(uint16_t	data1_val)
{
	switch ( data1_val )
	{
	case 0:
		stepper_stop(&Stepper_Control,TIM_CHANNEL_1);
		break;
	case 1:
		stepper_set_prescaler(&Stepper_Control,STEPPER_SPEED_MIN);
		break;
	case 2:
		stepper_set_prescaler(&Stepper_Control,STEPPER_SPEED_MED);
		break;
	case 3:
		stepper_set_prescaler(&Stepper_Control,STEPPER_SPEED_MAX);
		break;
	}
	if (( clast_stepper_speed == 0 ) && (clast_stepper_status == 1 ))
		stepper_start(&Stepper_Control,TIM_CHANNEL_1,0,STEPPER_DIRECTION_FORWARD);

	clast_stepper_speed = data1_val;
	return clast_stepper_speed;
}

uint32_t	proportional_set_vacuum(uint16_t	data1_val)
{
	if ( proportional_status == 0 )
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
	set_gpio_mode(PROPORTIONAL_PROP_PORT,PROPORTIONAL_PROP_PIN,MODE_AF);
	pwm_start(&Pwm_TIM15_Control,TIM_CHANNEL_1);
	return 0;
}

#endif //#ifndef	SAMPLE_PROCESSES_ENABLED
