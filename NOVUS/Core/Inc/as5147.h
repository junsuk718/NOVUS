/**
 *
 * @file : as5147.h
 * @brief : header for as5147.cpp
 *
 * */

#ifndef __AS5147_H
#define __AS5147_H

#ifdef __cplusplus
extern "C" {
#endif


// include header file
#include "stm32g4xx_hal.h"
#include <math.h>


class AS5147{
	uint8_t errorFlag = 0;
	uint16_t _cs;
	uint16_t cs;
	GPIO_TypeDef* _ps;
	SPI_HandleTypeDef* _spi;
	uint8_t dout;
	uint8_t din;
	uint8_t clk;
	uint16_t position;
	uint16_t transaction(uint16_t data);

public:

	/**
	 * SPI
	 * CONNECTION
	 * SpiSet();
	 * will be written by jypark
	 */

	/*
	 * read()
	 * write()
	 * will be written by jypark
	 */


	/*
	 * Returns the raw angle directly from the sensor
	 */
	uint16_t RawPos();


	/**
	 * Get the rotation of the sensor relative to the zero position.
	 */
	int pos();



	/**
	 * Return Automatic Gain Control
	 */
	uint8_t agcGain();

	/*
	 * return state register value
	 */
	uint16_t getState();


	// check error
	uint8_t checkerror();


	//set the zero position
	void setZeroPosition(uint16_t zero_position);


	// get the zero position
	uint16_t getZeroPosition();

	//mapping the angle with pos
	uint16_t err_angle();

	//mapping the angle with pos
	uint16_t angleMap();



};

const int AS5147_ERRFL              		   = 0x0001;	//error register
const int AS5147_PROG        				   = 0x0003;	//Programming register
const int AS5147_ZPOSM					       = 0x0016;	//Zero position MSB
const int AS5147_ZPOSL					       = 0x0017;	//Zero position LSB/MAG diagnostic
const int AS5147_DIAAGC                        = 0x3FFC;	//Diagnostic and AGC
const int AS5147_MAG                           = 0x3FFD;	//CORDIC magnitude
const int AS5147_ANGLEUNC					   = 0x3FFE;	// Measured angle without dynamic angle error compensation
const int AS5147_ANGLECOM                      = 0x3FFF;	// Measured angle with dynamic angle error compensation


#ifdef __cplusplus


}
#endif



#endif /* __MAIN_H */

