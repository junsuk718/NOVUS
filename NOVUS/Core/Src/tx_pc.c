/*
 * tx_pc.c
 *
 *  Created on: 2021. 4. 21.
 *      Author: sb030
 */

#include "tx_pc.h"

UART_HandleTypeDef huart2;

/*
void get_packet_moter(){
	payload.A = motor.ang;
	payload.B = motor.rpm;
	payload.C = motor.acceleration;
	payload.D = motor.pwm;
	payload.E = motor.time;
    payload.F = 0x00;
    payload.G = 0x00;
    trans_pc(5,0);
}
*/
void get_packet_moter(){
	payload.A = 111;
	payload.B = 111;
	payload.C = 111;
	payload.D = 111;
	payload.E = 111;
    payload.F = 0x00;
    payload.G = 0x00;
    trans_pc(5,0);
}
/*
void get_packet_rc(){
	payload.A = rc.throttle;
	payload.B = rc.roll;
	payload.C = rc.pitch;
	payload.D = rc.yaw;
	payload.E = rc.aux1;
	payload.F = rc.aux2;
	payload.G = rc.aux3;

    trans_pc(7,1);
}
*/
void get_packet_rc(){
	payload.A = 222;
	payload.B = 222;
	payload.C = 222;
	payload.D = 222;
	payload.E = 222;
	payload.F = 222;
	payload.G = 222;

    trans_pc(7,1);
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
	tp.payload = payload;
	tp.end = ETX;

	HAL_UART_Transmit(&huart2, (uint8_t*)&tp, sizeof(tp), 1000); //읽어드린 값 터미널로 출력
}
