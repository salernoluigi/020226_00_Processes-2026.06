/*
 * lcd_parser.h
 *
 *  Created on: Jun 23, 2026
 *      Author: MARFIX
 */

#ifndef LCD_PARSER_H_
#define LCD_PARSER_H_

typedef struct
{
	uint8_t			flags[2];
	uint8_t			byte_count;
	uint8_t			instruction;
	uint8_t			vph;
	uint8_t			vpl;
	uint8_t			data0l;
	uint8_t			data0h;
	uint8_t			data1l;
	uint8_t			data1h;
}LCDdata_Struct_t;

#define	MAX_VPCOUNT	32
typedef struct
{
	uint16_t		vp;
	uint32_t		(*vp_callback)(uint16_t	data0_val,uint16_t	data1_val);
}VPLCD_Struct_t;

extern	LCDdata_Struct_t	LCDdata_Struct;
extern	VPLCD_Struct_t		VPLCD_Struct[];

extern	uint32_t lcd_parser(UART_DriverStruct_t *uart_drv);

#endif /* LCD_PARSER_H_ */
