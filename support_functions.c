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
 * support_functions.c
 *
 *  Created on: Jun 10, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#ifndef	SAMPLE_PROCESSES_ENABLED

#include "hydra_020226_00.h"

uint8_t 	led_cntr = 0;

void process_led(void)
{
	switch(led_cntr)
	{
	case 6:
	case 8:
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
		break;
	case 10:
		led_cntr = 0;
		break;
	default :
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
		break;
	}
	led_cntr++;
}

void ac_cmd0_on(void)
{
	HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin,GPIO_PIN_SET);
}

void ac_cmd0_off(void)
{
	HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin,GPIO_PIN_RESET);
}

void ac_cmd1_on(void)
{
	HAL_GPIO_WritePin(AC_CMD1_GPIO_Port, AC_CMD1_Pin,GPIO_PIN_SET);
}

void ac_cmd1_off(void)
{
	HAL_GPIO_WritePin(AC_CMD1_GPIO_Port, AC_CMD1_Pin,GPIO_PIN_RESET);
}

void ac_cmd2_on(void)
{
	HAL_GPIO_WritePin(AC_CMD2_GPIO_Port, AC_CMD2_Pin,GPIO_PIN_SET);
}

void ac_cmd2_off(void)
{
	HAL_GPIO_WritePin(AC_CMD2_GPIO_Port, AC_CMD2_Pin,GPIO_PIN_RESET);
}

void buzzer_on(void)
{
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,GPIO_PIN_SET);
}

void buzzer_off(void)
{
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,GPIO_PIN_RESET);
}

void hydrogen_on(void)
{
	HAL_GPIO_WritePin(HYDROGEN_9V_GPIO_Port, HYDROGEN_9V_Pin,GPIO_PIN_SET);
}

void hydrogen_off(void)
{
	HAL_GPIO_WritePin(HYDROGEN_9V_GPIO_Port, HYDROGEN_9V_Pin,GPIO_PIN_RESET);
}

void aux1_on(void)
{
	HAL_GPIO_WritePin(AUX1_OUT_NOPWM_GPIO_Port, AUX1_OUT_NOPWM_Pin,GPIO_PIN_SET);
}

void aux1_off(void)
{
	HAL_GPIO_WritePin(AUX1_OUT_NOPWM_GPIO_Port, AUX1_OUT_NOPWM_Pin,GPIO_PIN_RESET);
}

void aux2_on(void)
{
	HAL_GPIO_WritePin(AUX2_OUT_NOPWM_GPIO_Port, AUX2_OUT_NOPWM_Pin,GPIO_PIN_SET);
}

void aux2_off(void)
{
	HAL_GPIO_WritePin(AUX2_OUT_NOPWM_GPIO_Port, AUX2_OUT_NOPWM_Pin,GPIO_PIN_RESET);
}

void peri_fwd(void)
{
	HAL_GPIO_WritePin(PERI_DIR_GPIO_Port, PERI_DIR_Pin,GPIO_PIN_SET);
}

void peri_rev(void)
{
	HAL_GPIO_WritePin(PERI_DIR_GPIO_Port, PERI_DIR_Pin,GPIO_PIN_RESET);
}

void get_adc_values(void)
{
	HYDRA_Struct.press0 = HYDRA_Struct.adc_data[ANALOG_PRESS0];
	HYDRA_Struct.press1 = HYDRA_Struct.adc_data[ANALOG_PRESS1];
	HYDRA_Struct.v24    = HYDRA_Struct.adc_data[ANALOG_V24];
	HYDRA_Struct.v12    = HYDRA_Struct.adc_data[ANALOG_V12];
	HYDRA_Struct.vout   = HYDRA_Struct.adc_data[ANALOG_VOUT];
	HYDRA_Struct.v5     = HYDRA_Struct.adc_data[ANALOG_V5];
}

uint32_t read_BOARD_Config(void)
{
	if ( i2c_24xx_read(&i2c_24xx_Drv,0,(uint8_t *)&BOARD_Config,HYDRA_CONFIG_SIZE) )
		return 1;
	if (( BOARD_Config.header == HYDRA_CONFIG_HEADER) && ( BOARD_Config.footer == HYDRA_CONFIG_FOOTER))
		return 0;
	return 1;
}

uint32_t set_default_BOARD_Config(void)
{
uint32_t i;

	BOARD_Config.gpio_tim_output = 0;	// all gpio
	for(i=0;i<HYDRA_TIM_NUM;i++)
	{
		switch(i)
		{
		case 0:
			BOARD_Config.gpio_bit[i] = PIN_TIM1_CH1_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM1_CH1_GPIO_Port;
			break;
		case 1:
			BOARD_Config.gpio_bit[i] = PIN_TIM1_CH2_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM1_CH2_GPIO_Port;
			break;
		case 2:
			BOARD_Config.gpio_bit[i] = PIN_TIM1_CH3_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM1_CH3_GPIO_Port;
			break;
		case 3:
			BOARD_Config.gpio_bit[i] = PIN_TIM1_CH4_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM1_CH4_GPIO_Port;
			break;
		case 4:
			BOARD_Config.gpio_bit[i] = PIN_TIM3_CH1_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM3_CH1_GPIO_Port;
			break;
		case 5:
			BOARD_Config.gpio_bit[i] = PIN_TIM3_CH2_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM3_CH2_GPIO_Port;
			break;
		case 6:
			BOARD_Config.gpio_bit[i] = PIN_TIM3_CH3_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM3_CH3_GPIO_Port;
			break;
		case 7:
			BOARD_Config.gpio_bit[i] = PIN_TIM3_CH4_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM3_CH4_GPIO_Port;
			break;
		case 8:
			BOARD_Config.gpio_bit[i] = PIN_TIM4_CH1_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM4_CH1_GPIO_Port;
			break;
		case 9:
			BOARD_Config.gpio_bit[i] = PIN_TIM4_CH2_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM4_CH2_GPIO_Port;
			break;
		case 10:
			BOARD_Config.gpio_bit[i] = PIN_TIM4_CH3_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM4_CH3_GPIO_Port;
			break;
		case 11:
			BOARD_Config.gpio_bit[i] = PIN_TIM4_CH4_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM4_CH4_GPIO_Port;
			break;
		case 12:
			BOARD_Config.gpio_bit[i] = PIN_TIM5_CH1_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM5_CH1_GPIO_Port;
			break;
		case 13:
			BOARD_Config.gpio_bit[i] = PIN_TIM5_CH2_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM5_CH2_GPIO_Port;
			break;
		case 14:
			BOARD_Config.gpio_bit[i] = PIN_TIM5_CH3_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM5_CH3_GPIO_Port;
			break;
		case 15:
			BOARD_Config.gpio_bit[i] = PIN_TIM5_CH4_Pin;
			BOARD_Config.gpio_port[i] = PIN_TIM5_CH4_GPIO_Port;
			break;
		case 16:
			BOARD_Config.gpio_bit[i] = AUX3_TIM15_CH1_Pin;
			BOARD_Config.gpio_port[i] = AUX3_TIM15_CH1_GPIO_Port;
			break;
		case 17:
			BOARD_Config.gpio_bit[i] = AUX4_TIM15_CH2_Pin;
			BOARD_Config.gpio_port[i] = AUX4_TIM15_CH2_GPIO_Port;
			break;
		}
		HAL_GPIO_WritePin(BOARD_Config.gpio_port[i],BOARD_Config.gpio_bit[i],(BOARD_Config.gpio_bit_level_if_gpio & (1<<i)) ); // gpio defaults to 0 if used
		set_gpio_mode(BOARD_Config.gpio_port[i],BOARD_Config.gpio_bit[i],MODE_OUTPUT);
	}

	return 0;
}

uint32_t config_pins_from_BOARD_Config(void)
{
uint32_t i,k,pinmode;
	for(i=0,k=0x01;i<HYDRA_TIM_NUM;i++,k<<=1)
	{
		if ( BOARD_Config.gpio_tim_output & k )
			pinmode = MODE_AF;
		else
			pinmode = MODE_OUTPUT;
		HAL_GPIO_WritePin(BOARD_Config.gpio_port[i],BOARD_Config.gpio_bit[i],(BOARD_Config.gpio_bit_level_if_gpio & k)>>i ); // gpio defaults to 0 if used
		set_gpio_mode(BOARD_Config.gpio_port[i],BOARD_Config.gpio_bit[i],pinmode);
	}
	return 0;
}

void tim_pin_on(uint16_t BOARD_Config_tim_number)
{
	if ( BOARD_Config_tim_number < HYDRA_TIM_NUM)
		HAL_GPIO_WritePin(BOARD_Config.gpio_port[BOARD_Config_tim_number],BOARD_Config.gpio_bit[BOARD_Config_tim_number],GPIO_PIN_SET); // gpio defaults to 0 if used
}

void tim_pin_off(uint16_t BOARD_Config_tim_number)
{
	if ( BOARD_Config_tim_number < HYDRA_TIM_NUM)
		HAL_GPIO_WritePin(BOARD_Config.gpio_port[BOARD_Config_tim_number],BOARD_Config.gpio_bit[BOARD_Config_tim_number],GPIO_PIN_RESET); // gpio defaults to 0 if used
}

uint32_t test_blink_ports(uint8_t index , uint8_t level)
{
GPIO_TypeDef		*gpio_port;
uint16_t			gpio_bit;

	gpio_port = BOARD_Config.gpio_port[index];
	gpio_bit  = BOARD_Config.gpio_bit[index];
	HAL_GPIO_WritePin(gpio_port,gpio_bit,level);
	return 0;
}

#endif //#ifndef	SAMPLE_PROCESSES_ENABLED

