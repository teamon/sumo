#ifndef SUMO_H_
#define SUMO_H_

#ifdef AVR
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdlib.h>
#else
	#include <iostream>
	
	#define _delay_ms(x) usleep(x)
	#define D(x) std::cout << x << std::endl
	#define _BV(x) (1 << x)
	void simulate();
#endif

#include "engine.h"

#define ITERATION_TIME 100
#define MOVE_TIME_MULTIPLIER 100

#define ENGINE_NUM 2
#define ENGINE_LEFT 0
#define ENGINE_RIGHT 1

#define GROUND_FRONT_LEFT 0
#define GROUND_FRONT_RIGHT 1
#define GROUND_BACK_LEFT 2
#define GROUND_BACK_RIGHT 3

// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)

extern char ground; // | 0 | 0 | 0 | 0 | G3 | G2 | G1 | G0 |
// check ground with bset(Ground, GROUND_FRONT_LEFT)

extern Engine engine[ENGINE_NUM];

#endif
