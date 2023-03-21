/*
 * BUTTON.h
 *
 *  Created on: Mar 21, 2023
 *      Author: Tuan
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

typedef struct
{
    GPIO_TypeDef *GPIO_Button;
    uint16_t GPIO_Pin_Button;
    uint8_t current_state;
    uint8_t last_state;
    uint8_t deboucing_state;
    uint8_t is_deboucing;
    uint32_t deboucing_timer;
} BUTTON_HandleTypeDef;

void BUTTON_Init(BUTTON_HandleTypeDef *ButtonX, GPIO_TypeDef *GPIO_Button, uint16_t GPIO_Pin_Button);

void BUTTON_Handle(BUTTON_HandleTypeDef *ButtonX);


#endif /* BUTTON_H_ */
