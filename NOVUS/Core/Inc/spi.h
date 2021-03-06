 #pragma once
/*
 * spi.h
 *
 *  Created on: 2021. 3. 31.
 *      Author: sb030
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "header.h"

#define MAX_BUFF 50





void SpiSet(GPIO_TypeDef *GPIO_x,uint16_t GPIO_Pin_Num,SPI_HandleTypeDef *hspi_x);
uint8_t ReadSpiCall(uint8_t address);
void WriteSpiCall(uint8_t address, uint8_t data);

#endif /* INC_SPI_H_ */
