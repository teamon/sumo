#ifndef SUMO_H_
#define SUMO_H_

#define _abs(x) ( ((x) < 0) ? (-(x)) : (x) )

#ifdef AVR
	#include <avr/io.h>
	#include <avr/iom32.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdlib.h>
#else
	#include <iostream>
	
	#define _delay_ms(x) 
	#define D(x) std::cout << x << std::endl
	#define _BV(x) (1 << x)
	
	void simulate();
#endif

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

#ifdef AVR
	#define ENGINE_DDR DDRD
	#define ENGINE_PORT PORTD
	#define ENGINE_0_PIN 4
	#define ENGINE_1_PIN 5
	#define ENGINE_0_OCR OCR1B // PD4
	#define ENGINE_1_OCR OCR1A // PD5
	#define ENGINE_DIR_DDR DDRD
	#define ENGINE_DIR_PORT PORTD
	#define ENGINE_0_DIR_PIN 2
	#define ENGINE_1_DIR_PIN 3

	#define GROUND_DDR DDRB
	#define GROUND_PORT PORTB
	#define GROUND_0_PIN 0
	#define GROUND_1_PIN 1
	#define GROUND_2_PIN 2
	#define GROUND_3_PIN 3
	
	#define DIST_DDR DDRA
#endif


// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)


class SUMO {
public:
	static char engine[5];
	static bool inverted;
	static char ground;
	static volatile int dist[DIST_NUM];
};


// engine.cpp
void engine_init();

//dist
void dist_init ();

//ground
void ground_init();
void ground_get();

#ifdef DEBUG

#define char2int(c) (c - 48)
#define int2char(c) (c + 48)

// usart.cpp
void usart_init();
void usart_write_byte(unsigned char byte);
void usart_write_string(char *string);
void usart_write_number(long number);
unsigned char usart_read_byte();

// debug.cpp
void debug_send_state();
void debug_parse_input();
void debug_wait_for_input(char c);

void debug(char c);
void debug(int c);

extern char debug_dist_enabled;
extern char debug_ground_enabled;
extern char debug_manual_engine_mode;
extern char debug_invert_enabled;
extern volatile char debug_wait;

#endif

#endif
