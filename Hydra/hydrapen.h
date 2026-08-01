/*
 * hydrapen.h
 *
 *  Created on: Jul 25, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_HYDRAPEN_H_
#define HYDRA_HYDRAPEN_H_

#define	HYDRAPEN_PUMP_PORT				AC_CMD0_GPIO_Port
#define	HYDRAPEN_PUMP_PIN				AC_CMD0_Pin
#define	HYDRAPEN_PUMP24V_PORT			PIN_TIM1_CH2_GPIO_Port		/* J19 pompa supplementare 24V*/
#define	HYDRAPEN_PUMP24V_PIN			PIN_TIM1_CH2_Pin
#define	HYDRAPEN_PROP_VACUUM_PORT		AUX3_TIM15_CH1_GPIO_Port	/* J34 PWM prop vacuum */
#define	HYDRAPEN_PROP_VACUUM_PIN		AUX3_TIM15_CH1_Pin
#define	HYDRAPEN_PROP_PRODUCT_PORT		AUX4_TIM15_CH2_GPIO_Port	/* J44 PWM prop */
#define	HYDRAPEN_PROP_PRODUCT_PIN		AUX4_TIM15_CH2_Pin
#define	HYDRAPEN_EV3_VACUUM_PORT		AUX1_OUT_NOPWM_GPIO_Port	/* J46 vacuum  */
#define	HYDRAPEN_EV3_VACUUM_PIN			AUX1_OUT_NOPWM_Pin

#define	HYDRAPEN_BOTTLE_A_PORT			PIN_TIM5_CH4_GPIO_Port		/* J33 prodotto EV A */
#define	HYDRAPEN_BOTTLE_A_PIN			PIN_TIM5_CH4_Pin
#define	HYDRAPEN_BOTTLE_B_PORT			PIN_TIM5_CH3_GPIO_Port		/* J32 prodotto EV B */
#define	HYDRAPEN_BOTTLE_B_PIN			PIN_TIM5_CH3_Pin
#define	HYDRAPEN_BOTTLE_C_PORT			PIN_TIM5_CH2_GPIO_Port		/* J31 prodotto EV C */
#define	HYDRAPEN_BOTTLE_C_PIN			PIN_TIM5_CH2_Pin
#define	HYDRAPEN_BOTTLE_H2O_PORT		PIN_TIM5_CH1_GPIO_Port		/* J30 prodotto EV D / H2O */
#define	HYDRAPEN_BOTTLE_H2O_PIN			PIN_TIM5_CH1_Pin


extern	uint32_t 	hydrapen_start(uint32_t level);
extern	uint32_t	hydrapen_treatment_sel(uint16_t	data1_val);

#endif /* HYDRA_HYDRAPEN_H_ */
