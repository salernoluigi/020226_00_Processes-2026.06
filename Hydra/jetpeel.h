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
 * jetpeel.h
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_JETPEEL_H_
#define HYDRA_JETPEEL_H_

#define	JETPEEL_PUMP_PORT		AC_CMD0_GPIO_Port
#define	JETPEEL_PUMP_PIN		AC_CMD0_Pin
#define	JETPEEL_PUMP24V_PORT	PIN_TIM1_CH2_GPIO_Port		/* J19 pompa supplementare 24V*/
#define	JETPEEL_PUMP24V_PIN		PIN_TIM1_CH2_Pin

#define	JETPEEL_EV_PORT			AUX2_OUT_NOPWM_GPIO_Port	/* J45 */
#define	JETPEEL_EV_PIN			AUX2_OUT_NOPWM_Pin
#define	JETPEEL_EV3WARIA_PORT	PIN_TIM1_CH4_GPIO_Port		/* J21 */
#define	JETPEEL_EV3WARIA_PIN	PIN_TIM1_CH4_Pin

extern	uint32_t jetpeel_init(void);
extern	uint32_t jetpeel_set_out(uint32_t level);
extern	uint32_t jetpeel_timer_call(void);
extern	uint32_t jetpeel_set_program(uint32_t level);

#endif /* HYDRA_JETPEEL_H_ */
