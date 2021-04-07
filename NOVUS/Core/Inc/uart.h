/*
 * uart.h
 *
 *  Created on: 2021. 4. 7.
 *      Author: sb030
 */

#ifndef INC_UART_H_
#define INC_UART_H_


struct PACKET{
	uchar header;
	uint8_t len;
	struct PAYLOAD payload;
	uchar end;
};


#endif /* INC_UART_H_ */
