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
 * user_config.h
 *
 *  Created on: Sep 1, 2025
 *      Author: fil
 */

#ifndef PROJECT_LIB_MODULES_H_
#define PROJECT_LIB_MODULES_H_

#define		USER_PROCESSES	1

#define 	USB_DEVICE_ENABLED		1
#define		USB_CDC				1
#undef		USBD_MANUFACTURER_STRING
#define		USBD_MANUFACTURER_STRING	"KS"
#undef		USBD_PRODUCT_STRING_FS
#define 	USBD_PRODUCT_STRING_FS		"Hydra Virtual ComPort"
#define		XMODEM_ENABLE		1


#define		BOARD_NAME					"020226-00"
#define		MACHINE_NAME				"Hydra"
#define		MACHINE_VERSION				"A"

#endif /* PROJECT_LIB_MODULES_H_ */
