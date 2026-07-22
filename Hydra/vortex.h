/*
 * vortex.h
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_VORTEX_H_
#define HYDRA_VORTEX_H_

#define	VORTEX_PUMP_PORT		AC_CMD0_GPIO_Port
#define	VORTEX_PUMP_PIN			AC_CMD0_Pin
#define	VORTEX_EV3V_VACUUM_PORT	AUX1_OUT_NOPWM_GPIO_Port	/* J46 STD I/O */
#define	VORTEX_EV3V_VACUUM_PIN	AUX1_OUT_NOPWM_Pin
#define	VORTEX_EV3V_HYDRA_PORT	PIN_TIM3_CH1_GPIO_Port		/* J22 STD_I/O */
#define	VORTEX_EV3V_HYDRA_PIN	PIN_TIM3_CH1_Pin
#define	VORTEX_MOTORPWM_PORT	PIN_TIM3_CH2_GPIO_Port		/* J23 PWM */
#define	VORTEX_MOTORPWM_PIN		PIN_TIM3_CH2_Pin
#define	VORTEX_PROP_PORT		AUX3_TIM15_CH1_GPIO_Port	/* J34 PWM prop vacuum */
#define	VORTEX_PROP_PIN			AUX3_TIM15_CH1_Pin

#define	VORTEX_SPEED_MIN		960							/* 1/4 Hz = 4 sec / rotation */
#define	VORTEX_SPEED_MED		VORTEX_SPEED_MIN/2			/* 1/2 Hz = 2 sec / rotation */
#define	VORTEX_SPEED_MAX		VORTEX_SPEED_MIN/4			/* 1 Hz = 1 sec / rotation */
#define	VORTEX_SPEED_RECOVERY	VORTEX_SPEED_MIN/8			/* 2 Hz = .5 sec / rotation */

uint32_t	vortex_init(void);
uint32_t	vortex_start(uint32_t level);
uint32_t	vortex_set_dose(uint16_t	data1_val);
uint32_t	vortex_set_vacuum(uint16_t	data1_val);
uint32_t	vortex_set_speed(uint16_t	data1_val);
#endif /* HYDRA_VORTEX_H_ */
