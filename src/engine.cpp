#include "sumo.h"

inline void engine_change_dir(char power, unsigned char pin){
	if((SUMO::inverted ? -power : power) >= 0) setb(ENGINE_DIR_PORT, pin);
	else clrb(ENGINE_DIR_PORT, pin);
}

ISR (TIMER1_OVF_vect)
{
	ENGINE_0_OCR = _abs(SUMO::engine[0]) * 10;
	ENGINE_1_OCR = _abs(SUMO::engine[1]) * 10;

	engine_change_dir(SUMO::engine[0], ENGINE_0_DIR_PIN);
	engine_change_dir(-SUMO::engine[1], ENGINE_1_DIR_PIN);
}

void engine_init(){
	SUMO::engine[0] = 0;
	SUMO::engine[1] = 0;

	TCCR1A = _BV(COM1A1) |  _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
	TCCR1B |= _BV(CS11); // preskaler clk/8

	ENGINE_0_OCR = 0;
	ENGINE_1_OCR = 0;

	setb(ENGINE_DDR, ENGINE_0_PIN);
	setb(ENGINE_DDR, ENGINE_1_PIN);
	setb(ENGINE_DIR_DDR, ENGINE_0_DIR_PIN);
	setb(ENGINE_DIR_DDR, ENGINE_1_DIR_PIN);
	
	TIMSK = _BV(TOIE1);
}

