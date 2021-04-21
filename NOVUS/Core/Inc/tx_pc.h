/*
 * tx_pc.h
 *
 *  Created on: 2021. 4. 21.
 *      Author: sb030
 */

#include"spectrum.h"
#include"as5147.h"
#include"stm32g4xx_hal_uart.h"

#ifndef INC_TX_PC_H_
#define INC_TX_PC_H_



struct TransMoter{
	uint16_t ang;
	uint16_t rpm;
	uint16_t acceleration;
	uint16_t pwm;
	uint16_t time;
};

struct TransRc{
	uint16_t throttle;
	uint16_t roll;
	uint16_t pitch;
	uint16_t yaw;
	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
};

struct TrnasPacket{
	uchar header;
	uint8_t len;
	struct PAYLOAD;
	uchar end;
};
void get_packet_moter();
void get_packet_rc();
void trans_pc(struct packet,uchar header);

struct TransMoter tm;
struct TransRc tr;
struct TransPacket tp;
#endif /* INC_TX_PC_H_ */
