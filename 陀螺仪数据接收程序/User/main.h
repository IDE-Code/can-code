#ifndef __MAIN_H__
#define __MAIN_H__

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;


#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

#include "stm32f4xx_conf.h"
#include "bsp_advance_tim.h"
#include "bsp_can.h"
#include "bsp_led.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "usart6.h"

#define abs(x) ((x)>0? (x):(-(x)))

#endif 
