/*
 * DHT11.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Tuan
 */

#ifndef DHT11_H_
#define DHT11_H_

#include "main.h"

typedef struct
{
	TIM_HandleTypeDef *htim;
	GPIO_TypeDef *GPIO_DHT11;
	uint16_t GPIO_Pin_DHT11;
	uint16_t start;
	float Hum;
	float Temp;
}DHT11_HandleTypeDef;



#endif /* DHT11_H_ */
