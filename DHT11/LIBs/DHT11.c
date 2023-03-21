/*
 * DHT11.c
 *
 *  Created on: Mar 17, 2023
 *      Author: Tuan
 */

#include "DHT11.h"
#include "delay.h"

#define START_TIME 18000 //us
#define TIME_OUT 2000    //ms

static void DHT11_Delay_Init
