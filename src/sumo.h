#ifndef SUMO_H_
#define SUMO_H_

#ifdef AVR
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <avr/pgmspace.h>
	#include <stdlib.h>
#else
	#include <iostream>
	
	#define _delay_ms(x) 
	#define D(x) std::cout << x << std::endl
	#define _BV(x) (1 << x)
	
	void simulate();
#endif

#include "engine.h"
#include "queue.h"

#define ITERATION_TIME 100
#define MOVE_TIME_MULTIPLIER 100

#define ENGINE_NUM 2
#define ENGINE_LEFT 0
#define ENGINE_RIGHT 1

#define GROUND_NUM 4
#define GROUND_FRONT_LEFT 0
#define GROUND_FRONT_RIGHT 1
#define GROUND_BACK_LEFT 2
#define GROUND_BACK_RIGHT 3

#define DIST_NUM 6

// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)

#define char2int(c) (c - 48)
#define int2char(c) (c + 48)

extern char ground; // [ 0 | 0 | 0 | 0 | G3 | G2 | G1 | G0 ]
// check ground with: ground == _BV(GROUNT_FRONT_LEFT)

extern Engine engine[ENGINE_NUM];

extern char dist[DIST_NUM];

// usart.cpp
void usart_init();
void usart_write_byte(unsigned char byte);
void usart_write_string(char *string);
void usart_write_number(long number);
unsigned char usart_read_byte();

#ifdef DEBUG
void debug_send_state();
// void debug_read_input();
void debug_parse_input();
void debug_wait_for_input(char c);

extern char debug_dist_enabled;
extern char debug_ground_enabled;
extern char debug_manual_engine_mode;
extern char debug_invert_enabled;
extern volatile char debug_wait;


// #define OFFBLAST_CHAR '\n'

#endif

#endif
