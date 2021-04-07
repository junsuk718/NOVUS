/*
 * spi.c
 *
 *  Created on: 2021. 3. 31.
 *      Author: sb030
 *
 *      참고사이트
 *      https://noel-embedded.tistory.com/673
 *      https://ddtxrx.tistory.com/entry/STM32-CubeMX-LL-%EB%93%9C%EB%9D%BC%EC%9D%B4%EB%B2%84-SPI-4
 *      https://m.blog.naver.com/PostView.nhn?blogId=eziya76&logNo=220941952468&proxyReferer=https:%2F%2Fwww.google.com%2F
 */

#include "spi.h"



GPIO_TypeDef *GPIO;
uint16_t GPIO_Pin;
SPI_HandleTypeDef *hspi;


/** @J.Yeon
  * @brief  Spi통신을 하기위한 초기설정
  * @param  GPIO_X GPIO포트(A..G)
  * @param  GPIO_Pin_Num GPIO통신을 하기위한 핀넘버(0..15)
  * @param  hspi_x SPI_HandleTypeDef 구조에 대한 hspi 포인터
  * @retval void
  */
void SpiSet(GPIO_TypeDef *GPIO_x,uint16_t GPIO_Pin_Num,SPI_HandleTypeDef *hspi_x){

	GPIO = GPIO_x;
	GPIO_Pin = GPIO_Pin_Num;
	hspi = hspi_x;
}

/** @J.Yeon
  * @brief  Spi통신을 통한 데이터 수신
  * @param  address GPIO포트(A..G)
  * @param  len GPIO통신을 하기위한 핀넘버(0..15)
  * @retval pdata Spi통신을 통해 받은 데이터
  */
uint8_t ReadSpiCall(uint8_t address, int len){

	uint8_t pdata[MAX_BUFF];

	//!NOTE :: 필요길이가 MAX_BUFF보다 클때 -> 에러(0출력) @J.Yeon
	if (len>MAX_BUFF)
		return 0;

	HAL_SPI_Writepin(*GPIO, GPIO_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, &address, 1, 30);
	HAL_SPI_Receive(hspi, pdata, len, 30);
	HAL_SPI_Writepin(*GPIO, GPIO_Pin, GPIO_PIN_SET);

	return pdata;
}


void WriteSpiCall(uint8_t address, uint8_t data){


	HAL_SPI_Writepin(*GPIO, GPIO_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, &address, 1, 30);
	HAL_SPI_Receive(hspi, data, len, 30);
	HAL_SPI_Writepin(*GPIO, GPIO_Pin, GPIO_PIN_SET);

}
