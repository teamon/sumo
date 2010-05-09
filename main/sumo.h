#ifndef SUMO_H_
#define SUMO_H_

#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../../../avr/lib/usart/usart.h"

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

#define ENGINE_DDR DDRD
#define ENGINE_PORT PORTD
#define ENGINE_0_PIN 5
#define ENGINE_1_PIN 4
#define ENGINE_0_OCR OCR1A // PD4
#define ENGINE_1_OCR OCR1B // PD5
#define ENGINE_DIR_DDR DDRB
#define ENGINE_DIR_PORT PORTB
#define ENGINE_0_DIR_PIN_0 0
#define ENGINE_0_DIR_PIN_1 1
#define ENGINE_1_DIR_PIN_0 2
#define ENGINE_1_DIR_PIN_1 3

#define GROUND_DDR DDRB
#define GROUND_PORT PORTB
#define GROUND_0_PIN 0
#define GROUND_1_PIN 1
#define GROUND_2_PIN 2
#define GROUND_3_PIN 3

#define DIST_DDR DDRA

// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)

#define _abs(x) ( ((x) < 0) ? (-(x)) : (x) )

class SUMO {
public:
	static char engine[5];
	static bool inverted;
	static char ground;
	static volatile int dist[DIST_NUM];
};


// engine.cpp
void engine_init();
void engine_set_power(char p0, char p1);

//dist
void dist_init ();

//ground
void ground_init();
void ground_get();

#ifdef DEBUG

#define char2int(c) (c - 48)
#define int2char(c) (c + 48)

// debug.cpp
void debug_init();
void debug_send_state();
void debug_parse_input();

void debug(char * c);
void debug(char c);
void debug(int c);

extern char debug_dist_enabled;
extern char debug_ground_enabled;
extern char debug_manual_engine_mode;
extern char debug_invert_enabled;
extern volatile char debug_got_input;
extern volatile char debug_wait;
extern Usart32 usb;

extern Queue Q;

#endif

#endif
