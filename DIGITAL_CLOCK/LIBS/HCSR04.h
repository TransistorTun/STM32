/*
 * HCSR04.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Tuan
 */

#ifndef HCSR04_H_
#define HCSR04_H_

#include "main.h"

typedef struct
{
    TIM_HandleTypeDef *htim;
    GPIO_TypeDef *GPIO_Trig;
    uint16_t GPIO_Pin_Trig;
    GPIO_TypeDef *GPIO_Echo;
    uint16_t GPIO_Pin_Echo;
}SR04_HandleTypeDef;

void HCSR04_Init(SR04_HandleTypeDef *SR_04x, TIM_HandleTypeDef *htim, GPIO_TypeDef *GPIO_Trig, uint16_t GPIO_Pin_Trig, GPIO_TypeDef *GPIO_Echo, uint16_t GPIO_Pin_Echo);

uint8_t HCSR04_Get_Distance(SR04_HandleTypeDef *SR_04x);

#endif /* HCSR04_H_ */
