/**
 *
 * @file : as5147.h
 * @brief : header for as5147.cpp
 *
 * */

#ifndef __AS5147_H
#define __AS5147_H

#define AS5147_ERRFL 0x0001;	//error register
#define AS5147_PROG 0x0003;	//Programming register
#define AS5147_ZPOSM 0x0016;	//Zero position MSB
#define AS5147_ZPOSL 0x0017;	//Zero position LSB/MAG diagnostic
#define AS5147_DIAAGC 0x3FFC;	//Diagnostic and AGC
#define AS5147_MAG 0x3FFD;	//CORDIC magnitude
#define AS5147_ANGLEUNC 0x3FFE;	// Measured angle without dynamic angle error compensation
#define  AS5147_ANGLECOM 0x3FFF;	// Measured angle with dynamic angle error compensation

#ifdef __cplusplus
extern "C" {
#endif


// include header file
#include "stm32g4xx_hal.h"
#include <math.h>
#include <time.h>

typedef struct {
	float ang				/*< 모터 각도		*/
	float RPM					/*< 모터 속도		*/
	float acceleration		/*< 모터 가속도		*/
	float pwm				/*< Output			*/
	float time				/*< cycle_time		*/
}MOTOR;

class AS5147{
	uint8_t errorFlag = 0;
	uint16_t position;
	uint16_t transaction(uint16_t data);

//	uint8_t dout;
//	uint8_t din;
//	uint8_t clk;
	//	uint16_t _cs;
	//	uint16_t cs;
	//	GPIO_TypeDef* _ps;
	//	SPI_HandleTypeDef* _spi;

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

	uint8_t error();

	// check error
	uint8_t checkerror();


	//set the zero position
	void setZeroPosition(uint16_t zero_position);


	// return 현재 zero position
	uint16_t getZeroPosition();

	//return normalized angle
	uint16_t normalize_angle(float angle);

	//mapping the angle with pos
	uint16_t angleMap(uint16_t angle);


	double calctime(clock_t begin, clock_t end);

	float calcRPM(double resTime);

	
	MOTOR motor();
};

#ifdef __cplusplus
}
#endif



#endif /* __MAIN_H */


