/**
 *
 * @file : as5147.c
 * @brief : header for as5147.cpp
 *
 *references
 *https://github.com/ZoetropeLabs/AS5048A-Arduino
 *AS5147_DS000307_2-00 datasheet
 *
 * */


#include <as5147.h>
#include <spi.h>

//constructor
//spiConnection , GPIO pin set

// AS5147::AS5147(SPI_HandleTypeDef* hspi, GPIO_TypeDef* arg_ps, uint16_t arg_cs){
// 	_cs = arg_cs;
// 	_ps = arg_ps;
// 	_spi = hspi;
// 	errorFlag = 0;
// 	position = 0;
// }

/*
 *
 * GPIO write pin
 * write yet
 */



/*
 * Read register from sensor
 * register address 8bit로 주소 받기
 * return register value
 * uint8_t AS5147::ReadSpiCall(uint8_t address, int len);
 *will be written by @jypark
 */


/*
 * write to register
 *will be written by @jypark
 */



/*
 * return the raw angle directly
 */
uint16_t AS5147::RawPos(){
	
	return ReadSpiCall(AS5147_ANGLEUNC);
}

// 제로포지션과의 각도 얻기
int AS5147::pos(){

	uint16_t rawpos;
	int rotation;

	rawpos = AS5147::RawPos();
	rotation = int(data) - (int)position;
	if(rotation > 8191) rotation =- ((0x3FFF)-rotation);
	return rotation;
}

uint16_t AS5147::getState(){
	
	  return ReadSpiCall(AS5147_DIAAGC);
}

uint8_t AS5147::agcGain(){
	uint16_t data = AS5147::getState();
	return (uint8_t) data & 0xFF;
}


uint8_t error(){
	return errorFlag;
}

/*
 * check error register
 */
uint8_t AS5147::checkerror(){
	 return ReadSpiCall(AS5147_ERRFL);
}

void AS5147::setZeroPosition(uint16_t zero_position){
	position = zero_position % 0x3FFF;
}

uint16_t getZeroPosition(){
	return position;
}

float normalize_angle(float angle){

	#ifdef ANGLE_MODE_1
			angle += 100;
	#endif
	angle = fmod(angle, 360);
	if(angle < 0){
		angle += 360;
	}
	#ifdef ANGLE_MODE_1
			angle -=180;
	#endif
	return angle;
}


float AS5147::angleMap(uint16_t angle){
	/*
	 * 14 bits = 2^(14) -1 = 16.383
	 * https://www.arduino.cc/en/Reference/Map
	 */
	return (float)angle * ((float)360 / 16383);
}


double AS5147::calctime(clock_t begin, clock_t end){
	double result;
	result = (double)(end - begin)/1000;	//second
	return result;
}

float AS5147::calcRPM(double resTime){
	float rpm;
	rpm = (1/(float)resTime) * (float)60;
	return rpm;
}

