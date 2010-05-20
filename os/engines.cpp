#include <avr/io.h>
#include <util/delay.h>
#include "os.h"
#include "debug.h"

#define ENGINE_DDR DDRD
#define ENGINE_PORT PORTD
#define ENGINE_0_PIN 5
#define ENGINE_1_PIN 4
#define ENGINE_0_OCR OCR1A // PD4
#define ENGINE_1_OCR OCR1B // PD5
#define ENGINE_DIR_DDR  DDRB
#define ENGINE_DIR_PORT PORTB
#define ENGINE_0_DIR_PIN_0 0
#define ENGINE_0_DIR_PIN_1 1
#define ENGINE_1_DIR_PIN_0 2
#define ENGINE_1_DIR_PIN_1 3

#define ENGINE_MAX_POWER 1023

void OS::initEngines(){
	engine[0] = 0;
	engine[1] = 0;
	_prev_engine[0] = 0;
	_prev_engine[1] = 0;
	
	TCCR1A = _BV(COM1A1) |  _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
	TCCR1B |= _BV(CS11); // preskaler clk/8
	
	ENGINE_0_OCR = 0;
	ENGINE_1_OCR = 0;
	
	setb(ENGINE_DDR, ENGINE_0_PIN);
	setb(ENGINE_DDR, ENGINE_1_PIN);
	setb(ENGINE_DIR_DDR, ENGINE_0_DIR_PIN_0);
	setb(ENGINE_DIR_DDR, ENGINE_0_DIR_PIN_1);
	setb(ENGINE_DIR_DDR, ENGINE_1_DIR_PIN_0);
	setb(ENGINE_DIR_DDR, ENGINE_1_DIR_PIN_1);
}

void OS::runEngines(){
	//dbg("engine[0]", engine[0]);
	//dbg("engine[1]", engine[1]);
	
	//if(engine[0] == _prev_engine[0] && engine[1] == _prev_engine[1]) return; // TODO: check it
	if(engine[0] * _prev_engine[0] < 0) ENGINE_0_OCR = 0;
	if(engine[1] * _prev_engine[1] < 0) ENGINE_1_OCR = 0;
	_delay_ms(50);
			
	int e0 = engine[0]*10;
	int e1 = engine[1]*10;
		
	if(e0 > 0){
		setb(ENGINE_DIR_PORT, ENGINE_0_DIR_PIN_0);
		clrb(ENGINE_DIR_PORT, ENGINE_0_DIR_PIN_1);
		ENGINE_0_OCR = _min(e0, ENGINE_MAX_POWER);
	} else {
		clrb(ENGINE_DIR_PORT, ENGINE_0_DIR_PIN_0);
		setb(ENGINE_DIR_PORT, ENGINE_0_DIR_PIN_1);
		ENGINE_0_OCR = _min(-e0, ENGINE_MAX_POWER);
	}
	
	if(e1 > 0){
		clrb(ENGINE_DIR_PORT, ENGINE_1_DIR_PIN_0);
		setb(ENGINE_DIR_PORT, ENGINE_1_DIR_PIN_1);
		ENGINE_1_OCR = _min(e1, ENGINE_MAX_POWER);
	} else {
		setb(ENGINE_DIR_PORT, ENGINE_1_DIR_PIN_0);
		clrb(ENGINE_DIR_PORT, ENGINE_1_DIR_PIN_1);
		ENGINE_1_OCR = _min(-e1, ENGINE_MAX_POWER);
	}
	
	_prev_engine[0] = engine[0];
	_prev_engine[1] = engine[1];
}
