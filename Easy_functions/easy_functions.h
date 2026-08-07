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
 * easy_functions.h
 *
 *  Created on: Aug 7, 2026
 *      Author: fil
 */

#ifndef EASY_FUNCTIONS_EASY_FUNCTIONS_H_
#define EASY_FUNCTIONS_EASY_FUNCTIONS_H_

#define	EASY_PAYLOAD_LEN		32
typedef struct
{
	uint8_t 		header;
	uint8_t 		address;
	uint8_t 		command;
	uint8_t 		payload[EASY_PAYLOAD_LEN];
	uint32_t		crc;
	uint8_t 		footer;
}EASY_Struct_t;
#define	EASY_HEADER				'<'
#define	EASY_FOOTER				'>'
#define	EASY_ADDR_BROADCAST		0xff
#define	EASY_ADDR_MASTER		0x00
#define	EASY_CMD_DISCOVERY		0x81
#define	EASY_CMD_SET_DATA		0x01

extern	uint32_t easy_loop(void);
extern	uint32_t easy_send(uint8_t *payload, uint8_t address, uint8_t command);

#endif /* EASY_FUNCTIONS_EASY_FUNCTIONS_H_ */
