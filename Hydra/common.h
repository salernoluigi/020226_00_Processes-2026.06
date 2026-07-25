/*
 * common.h
 *
 *  Created on: Jul 25, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_COMMON_H_
#define HYDRA_COMMON_H_

#define	PROPORTIONAL_PROP_PORT	AUX3_TIM15_CH1_GPIO_Port	/* J34 PWM prop vacuum */
#define	PROPORTIONAL_PROP_PIN	AUX3_TIM15_CH1_Pin

#define	STEPPER_SPEED_MIN		960							/* 1/4 Hz = 4 sec / rotation */
#define	STEPPER_SPEED_MED		VORTEX_SPEED_MIN/2			/* 1/2 Hz = 2 sec / rotation */
#define	STEPPER_SPEED_MAX		VORTEX_SPEED_MIN/4			/* 1 Hz = 1 sec / rotation */
#define	STEPPER_SPEED_RECOVERY	VORTEX_SPEED_MIN/8			/* 2 Hz = .5 sec / rotation */

extern	uint32_t	stepper_set_speed(uint16_t	data1_val);
extern	uint32_t	proportional_set_vacuum(uint16_t	data1_val);

#endif /* HYDRA_COMMON_H_ */
