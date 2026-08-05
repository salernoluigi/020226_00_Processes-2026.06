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
 * data_struct.c
 *
 *  Created on: Jun 9, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

#ifndef	SAMPLE_PROCESSES_ENABLED
#define	__STDRAM_DATA_AREA	__attribute__ ((aligned (32)))
#define	__ERAM_DATA_AREA	__attribute__((section(".d2ram"))) __attribute__ ((aligned (32)))

/* ADC Data */
__STDRAM_DATA_AREA	ADC_DriverStruct_t	ADC_Drv =
{
	.adc = &hadc1,
	.adc_buffer = &HYDRA_Struct.adc_data[0],
	.num_channels = ADCVAL_SAMPLES,
	.adc_timer = &htim6,
	.wakeup_id = WAKEUP_FROM_ADC1_IRQ,
	.flags = ADC_FLAGS_FULL_WAKEUP | ADC_FLAGS_CALIBRATE,
};

/* UART Data */
__ERAM_DATA_AREA	uint8_t	uart2_Exp_rx_buffer[UART2_RX_BUF_SIZE];
__ERAM_DATA_AREA	uint8_t	uart2_Exp_tx_buffer[UART2_TX_BUF_SIZE];

__STDRAM_DATA_AREA	UART_DriverStruct_t Uart2_Exp_Drv =
{
	.data = uart2_Exp_rx_buffer,
	.rx_max_len = UART2_RX_BUF_SIZE,
	.uart = &huart2,
	.wakeup_id = WAKEUP_FROM_UART2_IRQ,
	.timeout = 100,
	//.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	.flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

uint8_t	uart3_LCD_rx_buffer[UART3_RX_BUF_SIZE];
uint8_t	uart3_LCD_tx_buffer[UART3_TX_BUF_SIZE];

UART_DriverStruct_t Uart3_LCD_Drv =
{
	.data = uart3_LCD_rx_buffer,
	.rx_max_len = UART3_RX_BUF_SIZE,
	.uart = &huart3,
	.wakeup_id = WAKEUP_FROM_UART3_IRQ,
	.timeout = 10,
	//.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	/* this was ok */
	/* .flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT, */
	.flags = UART_USES_DMA_TX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

__ERAM_DATA_AREA	uint8_t	uart4_RS485_rx_buffer[UART4_RX_BUF_SIZE];
__ERAM_DATA_AREA	uint8_t	uart4_RS485_tx_buffer[UART4_TX_BUF_SIZE];

__STDRAM_DATA_AREA	UART_DriverStruct_t Uart4_RS485_Drv =
{
	.data = uart4_RS485_rx_buffer,
	.rx_max_len = UART4_RX_BUF_SIZE,
	.uart = &huart4,
	.wakeup_id = WAKEUP_FROM_UART4_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	//.flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

__ERAM_DATA_AREA	uint8_t	uart5_3G_rx_buffer[UART5_RX_BUF_SIZE];
__ERAM_DATA_AREA	uint8_t	uart5_3G_tx_buffer[UART5_TX_BUF_SIZE];

__STDRAM_DATA_AREA	UART_DriverStruct_t Uart5_3G_Drv =
{
	.data = uart5_3G_rx_buffer,
	.rx_max_len = UART5_RX_BUF_SIZE,
	.uart = &huart5,
	.wakeup_id = WAKEUP_FROM_UART5_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	//.flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

__ERAM_DATA_AREA	uint8_t	uart7_Easy_rx_buffer[UART7_RX_BUF_SIZE];
__ERAM_DATA_AREA	uint8_t	uart7_Easy_tx_buffer[UART7_TX_BUF_SIZE];

__STDRAM_DATA_AREA	UART_DriverStruct_t Uart7_Easy_Drv =
{
	.data = uart7_Easy_rx_buffer,
	.rx_max_len = UART7_RX_BUF_SIZE,
	.uart = &huart7,
	.wakeup_id = WAKEUP_FROM_UART7_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	//.flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

__ERAM_DATA_AREA	uint8_t	uart8_BT_rx_buffer[UART8_RX_BUF_SIZE];
__ERAM_DATA_AREA	uint8_t	uart8_BT_tx_buffer[UART8_TX_BUF_SIZE];

__STDRAM_DATA_AREA	UART_DriverStruct_t Uart8_BT_Drv =
{
	.data = uart8_BT_rx_buffer,
	.rx_max_len = UART8_RX_BUF_SIZE,
	.uart = &huart8,
	.wakeup_id = WAKEUP_FROM_UART8_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
	//.flags = UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

/* NEOLED */
#define	NUM_LEDS		8
#define WS2812_BUF_SIZE 		(WS2812_RESET_HEAD + (NUM_LEDS * WS2812_LEDBPP) + WS2812_RESET_TAIL)

uint16_t ws2812_work_buf[WS2812_BUF_SIZE];


NeoPixel_Struct_t	glow_buffer[NUM_LEDS];
NeoPixel_Struct_t	worm_buffer[NUM_LEDS];
NeoPixel_Struct_t	flasher_buffer[NUM_LEDS];

Worm_Struct_t		WormBuf =
{
		.led_buf = worm_buffer,
		.r = 0,
		.g = 0,
		.b = 255,
		.direction = WORM_WS2812_COUNTER_CLOCKWISE,
		.worm_len = NUM_LEDS,
};

Glow_Struct_t		GlowBuf =
{
		.led_buf = glow_buffer,
		.r = 0,
		.g = 0,
		.b = 255,
		.glow_mode = WS2812_GLOW_ONLY_DOWN,
		.initial_brightness = 0x10,
		.final_brightness = 0xf0,
		.glow_step = 1,
		.glow_len = NUM_LEDS,
};

Flasher_Struct_t		FlasherBuf =
{
		.led_buf = flasher_buffer,
		.r_on = 0,
		.g_on = 0,
		.b_on = 255,
		.r_off = 255,
		.g_off = 0,
		.b_off = 0,
		.brightness = 128,
		.flasher_len = NUM_LEDS,
};

WS2812_DriverStruct_t	WS2812_Drv =
{
		.ws2812_timer = &htim17,
		.ws2812_timer_channel = TIM_CHANNEL_1,
		.ws2812_numleds = NUM_LEDS,
		.ws2812_work_buf = &ws2812_work_buf[0],
		.ws2812_work_buf_buflen = WS2812_BUF_SIZE,
		.ws2812_arr_val = 211,
		.wakeup_id = WAKEUP_FROM_TIM_IRQ,
};

/* sd card */
__STDRAM_DATA_AREA	SDCARD_DriverStruct_t SDCARD =
{
	.hsd = &hsd1,
	.sd_detect_port = SDMMC1_CD_GPIO_Port,
	.sd_detect_bit = SDMMC1_CD_Pin,
};

/* PWM */
__STDRAM_DATA_AREA	Pwm_Control_DriverStruct_t	Pwm_TIM1_Control =
{
		.timer = &htim1,
		.period = 10000,
		.pulse_width = {PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,},
};

__STDRAM_DATA_AREA	Pwm_Control_DriverStruct_t	Pwm_TIM3_Control =
{
		.timer = &htim3,
		.period = 10000,
		.pulse_width = {PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,},
};

__STDRAM_DATA_AREA	Pwm_Control_DriverStruct_t	Pwm_TIM4_Control =
{
		.timer = &htim4,
		.period = 10000,
		.pulse_width = {PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,},
};

__STDRAM_DATA_AREA	Pwm_Control_DriverStruct_t	Pwm_TIM5_Control =
{
		.timer = &htim5,
		.period = 10000,
		.pulse_width = {PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,},
};


__STDRAM_DATA_AREA	Pwm_Control_DriverStruct_t	Pwm_TIM15_Control =
{
		.timer = &htim15,
		.period = 1250,
		.pulse_width = {PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,PWM_DEFAULT_PW,},
};

/* Stepper */
void stepper_callback(uint32_t value);

Stepper_Control_DriverStruct_t	Stepper_Control =
{
		.timer = &htim16,
		.timer_channel = TIM_CHANNEL_1,
		.tim_port = PERI_STEP_TIM16CH1_GPIO_Port,
		.tim_bit = PERI_STEP_TIM16CH1_Pin,
		.dir_port = PERI_DIR_GPIO_Port,
		.dir_bit = PERI_DIR_Pin,
		.enable_port = SLEEP_3G_GPIO_Port,
		.enable_bit = SLEEP_3G_Pin,
		.pulse_width = STEPPER_DEFAULT_PW,
		.prescaler = 480,
		.steps_per_rotation = 200,
		.stepper_callback = stepper_callback,
		.wakeup_id = WAKEUP_FROM_SW_MODULES_IRQ,
};

__attribute__ ((aligned (32)))	HYDRA_Struct_t			HYDRA_Struct;
__attribute__ ((aligned (32)))	BOARD_Config_Struct_t	BOARD_Config =
{
		.header = HYDRA_CONFIG_HEADER,
		.board_name = "Hydra",
		.board_version = "0.0",
		.os_version = A_OS_VERSION,
		.gpio_tim_output = ALL_GPIO,
		.footer = HYDRA_CONFIG_FOOTER,
};

void hydra_register_devices(void)
{
	adc_register(&ADC_Drv);
	uart_register(&Uart2_Exp_Drv);
	uart_register(&Uart3_LCD_Drv);
	uart_register(&Uart4_RS485_Drv);
	uart_register(&Uart5_3G_Drv);
	uart_register(&Uart7_Easy_Drv);
	uart_register(&Uart8_BT_Drv);
	sdcard_register(&SDCARD);
	stepper_register(&Stepper_Control);
	pwm_register(&Pwm_TIM1_Control);
	pwm_register(&Pwm_TIM3_Control);
	pwm_register(&Pwm_TIM4_Control);
	pwm_register(&Pwm_TIM5_Control);
	pwm_init(&Pwm_TIM1_Control);
	pwm_init(&Pwm_TIM3_Control);
	pwm_init(&Pwm_TIM4_Control);
	pwm_init(&Pwm_TIM5_Control);
	pwm_init(&Pwm_TIM15_Control);
	i2c_24xx_register(&i2c_24xx_Drv);
	bzero(uart3_LCD_rx_buffer,UART3_RX_BUF_SIZE);
	set_default_BOARD_Config();
	/*
	if ( HAL_I2C_IsDeviceReady(i2c_24xx_Drv.bus,i2c_24xx_Drv.device_address,5,1000) == 0 )
	{
		if ( read_BOARD_Config() == 0 )
			config_pins_from_BOARD_Config();
	}
	*/
	if ( BOARD_Config.neoled_num <= NUM_LEDS )
		WS2812_Drv.ws2812_numleds = BOARD_Config.neoled_num;
	ws2812_register(&WS2812_Drv);
}

#endif //#ifdef SAMPLE_PROCESSES_ENABLED


