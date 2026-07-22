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
 * linfocup.h
 *
 *  Created on: Jul 22, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_LINFOCUP_H_
#define HYDRA_LINFOCUP_H_

#define	LINFOCUP_PUMP_PORT		AC_CMD0_GPIO_Port
#define	LINFOCUP_PUMP_PIN		AC_CMD0_Pin
#define	LINFOCUP_EV3WARIA_PORT	AUX1_OUT_NOPWM_GPIO_Port	/* J46 driven by ton/toff */
#define	LINFOCUP_EV3WARIA_PIN	AUX1_OUT_NOPWM_Pin
#define	LINFOCUP_EV2CAP_PORT	PIN_TIM3_CH3_GPIO_Port		/* J24 I/O */
#define	LINFOCUP_EV2CAP_PIN		PIN_TIM3_CH3_Pin
#define	LINFOCUP_PROP_PORT		AUX3_TIM15_CH1_GPIO_Port	/* J34 PWM prop vacuum */
#define	LINFOCUP_PROP_PIN		AUX3_TIM15_CH1_Pin

extern	uint32_t 	linfocup_init(void);
extern	uint32_t	linfocup_set_out(uint16_t	data1_val);
extern	uint32_t	linfocup_set_intensity(uint16_t	data1_val);
extern	uint32_t	linfocup_set_release(uint16_t	data1_val);
extern	uint32_t	linfocup_set_su(uint16_t	data1_val);

#endif /* HYDRA_LINFOCUP_H_ */
