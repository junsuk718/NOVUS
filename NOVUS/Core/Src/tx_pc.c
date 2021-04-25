/*
 * tx_pc.c
 *
 *  Created on: 2021. 4. 21.
 *      Author: sb030
 */

#include "tx_pc.h"

void get_packet_moter(){
	payload.A = moter.ang;
	payload.B = moter.rpm;
	payload.c = moter.acceleration;
	payload.D = moter.pwm;
	payload.E = moter.time;
    payload.F = 0x00;
    Payload.G = 0x00;
    trans_pc(5,1);
}

void get_packet_rc(){
	payload.A = rc.throttle;
	payload.B = rc.roll;
	payload.C = rc.pitch;
	payload.D = rc.yaw;
	payload.E = rc.aux1;
	payload.F = rc.aux2;
	payload.G = rc.aux3;

    trans_pc(7,0);
}

/** @J.Yeon
  * @brief  패킷 정의 후 UART 송신
  * @param  uint8_t 보내는 패킷구조체 중 실제 구조체 크기
  * @param  uint8_t 메시지ID
  * @retval None
  */
void trans_pc(uint8_t len, uint8_t msgid){
	tp.header = STX;
	tp.len = len;
	tp.msgid = msgid;
	tp.PAYLOAD = payload;
	tp.end = ETX;

	HAL_UART_Transmit(&huart2, &tp, sizeof(tp), 1000); //읽어드린 값 터미널로 출력
}
