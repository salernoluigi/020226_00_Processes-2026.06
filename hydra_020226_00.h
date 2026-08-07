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
 * hydra_020226_00.h
 *
 *  Created on: Jun 9, 2026
 *      Author: fil
 */

#ifndef HYDRA_020226_00_H_
#define HYDRA_020226_00_H_

#define	APP_VERSION				"07082026_00"

extern	ADC_HandleTypeDef hadc1;

extern	I2C_HandleTypeDef hi2c1;
extern	I2C_HandleTypeDef hi2c2;

extern	SD_HandleTypeDef hsd1;

extern	SPI_HandleTypeDef hspi1;
extern	SPI_HandleTypeDef hspi2;

extern	TIM_HandleTypeDef htim1;
extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim4;
extern	TIM_HandleTypeDef htim5;
extern	TIM_HandleTypeDef htim6;
extern	TIM_HandleTypeDef htim15;
extern	TIM_HandleTypeDef htim16;
extern	TIM_HandleTypeDef htim17;

extern	UART_HandleTypeDef huart4;
extern	UART_HandleTypeDef huart5;
extern	UART_HandleTypeDef huart7;
extern	UART_HandleTypeDef huart8;
extern	UART_HandleTypeDef huart2;
extern	UART_HandleTypeDef huart3;

extern	ADC_DriverStruct_t				ADC_Drv;
extern	UART_DriverStruct_t 			Uart2_Exp_Drv;
extern	UART_DriverStruct_t 			Uart3_LCD_Drv;
extern	UART_DriverStruct_t 			Uart4_RS485_Drv;
extern	UART_DriverStruct_t 			Uart5_3G_Drv;
extern	UART_DriverStruct_t 			Uart7_Easy_Drv;
extern	UART_DriverStruct_t 			Uart8_BT_Drv;

extern	Pwm_Control_DriverStruct_t		Pwm_TIM1_Control;
extern	Pwm_Control_DriverStruct_t		Pwm_TIM3_Control;
extern	Pwm_Control_DriverStruct_t		Pwm_TIM4_Control;
extern	Pwm_Control_DriverStruct_t		Pwm_TIM5_Control;
extern	Pwm_Control_DriverStruct_t		Pwm_TIM15_Control;
extern	SDCARD_DriverStruct_t 			SDCARD;
extern	WS2812_DriverStruct_t			WS2812_Drv;
extern	Stepper_Control_DriverStruct_t	Stepper_Control;
extern	USB_DriverStruct_t				USB_Drv;
extern	I2C_24xx_DriverStruct_t			i2c_24xx_Drv;

#define	UART2_RX_BUF_SIZE	512
#define	UART2_TX_BUF_SIZE	512
#define	WAKEUP_FROM_EXP_UART_IRQ	WAKEUP_FROM_UART2_IRQ
extern	uint8_t	uart2_Exp_rx_buffer[UART2_RX_BUF_SIZE];
extern	uint8_t	uart2_Exp_tx_buffer[UART2_TX_BUF_SIZE];

#define	UART3_RX_BUF_SIZE	64
#define	UART3_TX_BUF_SIZE	512
#define	WAKEUP_FROM_LCD_UART_IRQ	WAKEUP_FROM_UART3_IRQ
extern	uint8_t	uart3_LCD_rx_buffer[UART3_RX_BUF_SIZE];
extern	uint8_t	uart3_LCD_tx_buffer[UART3_TX_BUF_SIZE];

#define	UART4_RX_BUF_SIZE	512
#define	UART4_TX_BUF_SIZE	512
#define	WAKEUP_FROM_RS485_UART_IRQ	WAKEUP_FROM_UART4_IRQ
extern	uint8_t	uart4_RS485_rx_buffer[UART4_RX_BUF_SIZE];
extern	uint8_t	uart4_RS485_tx_buffer[UART4_TX_BUF_SIZE];

#define	UART5_RX_BUF_SIZE	512
#define	UART5_TX_BUF_SIZE	512
#define	WAKEUP_FROM_3G_UART_IRQ	WAKEUP_FROM_UART5_IRQ
extern	uint8_t	uart5_3G_rx_buffer[UART5_RX_BUF_SIZE];
extern	uint8_t	uart5_3G_tx_buffer[UART5_TX_BUF_SIZE];

#define	UART7_RX_BUF_SIZE	40
#define	UART7_TX_BUF_SIZE	40
#define	WAKEUP_FROM_EASY_UART_IRQ	WAKEUP_FROM_UART7_IRQ
extern	uint8_t	uart7_Easy_rx_buffer[UART7_RX_BUF_SIZE];
extern	uint8_t	uart7_Easy_tx_buffer[UART7_TX_BUF_SIZE];

#define	UART8_RX_BUF_SIZE	512
#define	UART8_TX_BUF_SIZE	512
#define	WAKEUP_FROM_BT_UART_IRQ	WAKEUP_FROM_UART8_IRQ
extern	uint8_t	uart8_BT_rx_buffer[UART8_RX_BUF_SIZE];
extern	uint8_t	uart8_BT_tx_buffer[UART8_TX_BUF_SIZE];

#define	ADCVAL_SAMPLES			6
#define	TIM_TICK				100

#define	ANALOG_V24				0
#define	ANALOG_PRESS0			1
#define	ANALOG_V12				2
#define	ANALOG_PRESS1			3
#define	ANALOG_VOUT				4
#define	ANALOG_V5				5

#define	PWM_DEFAULT_PW			1000
#define	STEPPER_DEFAULT_PW		500
#define	I2CMEM_BUFFERSIZE		I2C_24XX_PAGESIZE*4

#define	GLOBAL_TIMER_DEFAULT	1800
#define	GLOBAL_TIMER_RUNNING	1
#define	GLOBAL_TIMER_STOP		0

typedef struct
{
	uint32_t		global_timer;
	uint32_t		global_timer_status;
	uint32_t		global_timer_value;
	uint8_t 		timbuf[32];
	uint32_t		(*global_timer_callback)(uint32_t	val0,uint32_t	val1);
	uint32_t		(*global_timer_elapsed_callback)(uint32_t	val0,uint32_t	val1);
	uint32_t		(*cleanup_function)(uint32_t	val0,uint32_t	val1);
	uint8_t 		jetpeel_program;
	uint8_t 		jetpeel_time;
	uint8_t 		jetpeel_enable;
	uint8_t 		airpen_enable;
	uint16_t		current_page;
	uint8_t			pump_status;
	uint8_t			hydrapen_running;
	uint8_t			stepper_running;
	uint16_t		stepper_running_timeout;
	uint8_t			flags;
	uint16_t		adc_data[ADCVAL_SAMPLES];
	uint16_t		press0;
	uint16_t		press1;
	uint16_t		v24;
	uint16_t		v12;
	uint16_t		vout;
	uint16_t		v5;
	uint8_t			i2cBufw[I2CMEM_BUFFERSIZE];
	uint8_t			i2cBufr[I2CMEM_BUFFERSIZE];
}HYDRA_Struct_t;
/* flags */
#define	HYDRA_I2CMEM_PRESENT			0x01
#define	HYDRA_I2CMEM_CHECKED			0x02
#define	HYDRA_I2CMEM_REINIT				0x04

#define	EE_HEADER_ADDRESS		0
#define	EE_COUNTERS_ADDRESS		0x100
#define	EE_PROGRAM_ADDRESS		0x200

#define	HYDRA_NAME_LEN			32
#define	HYDRA_VERSION_LEN		32
#define	HYDRA_CONFIG_SIZE		256
#define	HYDRA_CONFIG_HEADER		0x5a
#define	HYDRA_CONFIG_FOOTER		0xa5
#define	HYDRA_TIM_NUM			18

typedef struct
{
	uint8_t				header;
	uint8_t				board_name[32];
	uint8_t				board_version[32];
	uint8_t				os_version[32];
	GPIO_TypeDef		*gpio_port[HYDRA_TIM_NUM];
	uint16_t			gpio_bit[HYDRA_TIM_NUM];
	uint32_t			gpio_bit_level_if_gpio;	// bit field, 0 = output low , 1 = output high
	uint32_t			gpio_tim_output;	// bit field, 0 = gpio , 1 = pwm timer
	uint32_t			neoled_num;
	uint8_t				unused[HYDRA_CONFIG_SIZE - (1+32+32+32+(4*HYDRA_TIM_NUM)+(2*HYDRA_TIM_NUM)+4+4+4+1)];
	uint8_t				footer;
}BOARD_Config_Struct_t;


#define	TIM1_CH1_PWM		0x00000001
#define	TIM1_CH2_PWM		0x00000002
#define	TIM1_CH3_PWM		0x00000004
#define	TIM1_CH4_PWM		0x00000008
#define	TIM3_CH1_PWM		0x00000010
#define	TIM3_CH2_PWM		0x00000020
#define	TIM3_CH3_PWM		0x00000040
#define	TIM3_CH4_PWM		0x00000080
#define	TIM4_CH1_PWM		0x00000100
#define	TIM4_CH2_PWM		0x00000200
#define	TIM4_CH3_PWM		0x00000400
#define	TIM4_CH4_PWM		0x00000800
#define	TIM5_CH1_PWM		0x00001000
#define	TIM5_CH2_PWM		0x00002000
#define	TIM5_CH3_PWM		0x00004000
#define	TIM5_CH4_PWM		0x00008000
#define	TIM15_CH1_PWM		0x00010000
#define	TIM15_CH2_PWM		0x00020000

#define	ALL_PWM (\
		TIM1_CH1_PWM | TIM1_CH2_PWM | TIM1_CH3_PWM |TIM1_CH4_PWM | \
		TIM3_CH1_PWM | TIM3_CH2_PWM | TIM3_CH3_PWM |TIM3_CH4_PWM | \
		TIM4_CH1_PWM | TIM4_CH2_PWM | TIM4_CH3_PWM |TIM4_CH4_PWM | \
		TIM5_CH1_PWM | TIM5_CH2_PWM | TIM5_CH3_PWM |TIM5_CH4_PWM | \
		TIM15_CH1_PWM| TIM15_CH2_PWM )
#define	ALL_GPIO 0


#define	__STDRAM_DATA_AREA	__attribute__ ((aligned (32)))

extern	HYDRA_Struct_t			HYDRA_Struct;
extern	BOARD_Config_Struct_t	BOARD_Config;

extern	uint8_t	i2c_tx_buffer[I2C_24XX_PAGESIZE*2];
extern	uint8_t	i2c_rx_buffer[I2C_24XX_PAGESIZE*2];

extern	void hydra_register_devices(void);
extern	void stepper_callback(uint32_t value);

#include "global_timer.h"
#include "support_functions.h"
#include "weak_ks_functions.h"
#include "diag.h"
#include "lcd_parser.h"
#include "hydra_functions.h"

#include "Hydra/mousse.h"
#include "Hydra/airpen.h"
#include "Hydra/jetpeel.h"
#include "Hydra/vortex.h"
#include "Hydra/linfocup.h"
#include "Hydra/hydrapen.h"
#include "Hydra/counters.h"

#include "Easy_functions/easy_functions.h"

#endif /* HYDRA_020226_00_H_ */
