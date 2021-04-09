/*
 * spectrum.h
 *
 *  Created on: 2021. 4. 7.
 *      Author: sb030
 */


#ifndef INC_SPECTRUM_H_
#define INC_SPECTRUM_H_

#include "uart.h"

#define THROTTLE    0
#define AILERON     1
#define ELEVATOR    2
#define RUDDER      3
#define AUX1        4
#define AUX2        5
#define AUX3        6
#define AUX4        7
#define AUX5        8
#define AUX6        9
#define AUX7        10
#define AUX8        11

uint16_t rc[7];
struct RC{

	uint16_t throttle;
	uint16_t roll;
	uint16_t pitch;
	uint16_t yaw;
	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
};

struct CHANNEL_DATA {
    uint8_t phase;
    uint8_t id;
    uint16_t pos;
};

uint8_t byte_data[16];
uint16_t bit_data;
uint8_t fade, sys;
struct CHANNEL_DATA channel[12];

struct RC spectrum_read(uart_buffer);

#endif /* INC_SPECTRUM_H_ */
