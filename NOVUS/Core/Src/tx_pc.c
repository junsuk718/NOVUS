/*
 * tx_pc.c
 *
 *  Created on: 2021. 4. 21.
 *      Author: sb030
 */

#include "tx_pc.h"

void get_packet_moter(){
	 tm.ang = moter.ang;
	 tm.rpm = moter.rpm;
	 tm.acceleration = moter.acceleration;
	 tm.pwm = moter.pwm;
	 tm.time = moter.time;
}
void get_packet_rc(){
	tr.throttle = rc.throttle;
	tr.roll = rc.roll;
	tr.pitch = rc.pitch;
	tr.yaw = rc.yaw;
	tr.aux1 = rc.aux1;
	tr.aux2 = rc.aux2;
	tc.aux3 = rc.aux3;
}
void trans_pc(packet, header){
	tp.header = header;
	tp.len = sizeof(packet);
	tp.PAYLOAD = packet;

	 HAL_UART_Transmit(&huart2, &packet, 1, 1000); //읽어드린 값 터미널로 출력
}
