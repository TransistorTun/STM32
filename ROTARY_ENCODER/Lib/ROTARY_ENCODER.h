/*
 * ROTARY_ENCODER.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Tuan
 */

#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include "main.h"
#include "stm32f1xx_hal.h"

typedef struct
{
	TIM_HandleTypeDef *re_timer;
	uint32_t counter;
	int16_t count;
	int16_t current_position;
	int16_t last_position;
	float speed;
}RE_HandleTypeDef;

extern RE_HandleTypeDef rotary_encoder;

void RE_Init(RE_HandleTypeDef * p_re, TIM_HandleTypeDef *p_re_timer);
void RE_Get_Value(RE_HandleTypeDef * p_re);
void RE_Handle(RE_HandleTypeDef * p_re);

#endif /* ROTARY_ENCODER_H_ */