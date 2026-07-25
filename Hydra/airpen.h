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
 * airpen.h
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */


#ifndef HYDRA_AIRPEN_H_
#define HYDRA_AIRPEN_H_

#define	AIRPEN_PUMP_PORT		AC_CMD0_GPIO_Port
#define	AIRPEN_PUMP_PIN			AC_CMD0_Pin
#define	AIRPEN_EV3WARIA_PORT	AUX2_OUT_NOPWM_GPIO_Port	/* J45 */
#define	AIRPEN_EV3WARIA_PIN		AUX2_OUT_NOPWM_Pin
#define	AIRPEN_EV_PORT			PIN_TIM1_CH3_GPIO_Port		/* J20 */
#define	AIRPEN_EV_PIN			PIN_TIM1_CH3_Pin

extern	uint32_t airpen_init(void);
extern	uint32_t airpen_set_out(uint32_t level);

#endif /* HYDRA_AIRPEN_H_ */
