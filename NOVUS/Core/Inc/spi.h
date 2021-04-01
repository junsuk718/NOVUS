/*
 * spi.h
 *
 *  Created on: 2021. 3. 31.
 *      Author: sb030
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32g4xx_hal_spi.h"
#include "stm32g4xx_hal_gpio.h"







void SpiSet(GPIO_TypeDef *GPIO_x,uint16_t GPIO_Pin_Num,SPI_HandleTypeDef *hspi);
uint8_t ReadSpiCall(uint8_t *address);


#endif /* INC_SPI_H_ */
