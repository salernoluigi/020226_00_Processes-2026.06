/*
 * mousse.h
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */

#ifndef HYDRA_MOUSSE_H_
#define HYDRA_MOUSSE_H_

#define	MOUSSE_PORT	PIN_TIM1_CH1_GPIO_Port	/* J18 */
#define	MOUSSE_PIN	PIN_TIM1_CH1_Pin

extern	uint32_t mousse_init(void);
extern	uint32_t mousse_set_out(uint32_t level);

#endif /* HYDRA_MOUSSE_H_ */
