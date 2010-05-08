#include "sumo.h"

inline void engine_change_dir(char power, unsigned char pin0, unsigned char pin1){
	if((SUMO::inverted ? -power : power) >= 0) {
		setb(ENGINE_DIR_PORT, pin0);
		clrb(ENGINE_DIR_PORT, pin1);
	} else {
		clrb(ENGINE_DIR_PORT, pin0);
		setb(ENGINE_DIR_PORT, pin1);
	} 
}

ISR (TIMER1_OVF_vect){}

void engine_init(){
	SUMO::engine[0] = 0;
	SUMO::engine[1] = 0;

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
	
	TIMSK = _BV(TOIE1);
}

void engine_set_power(char p0, char p1){
	if(SUMO::engine[0] * p0 < 0) {
		ENGINE_0_OCR = 0;
		_delay_ms(50);
	}
	if(SUMO::engine[1] * p1 < 0) {
		ENGINE_1_OCR = 0;
		_delay_ms(50);
	}
	
	
	engine_change_dir( p0, ENGINE_0_DIR_PIN_0, ENGINE_0_DIR_PIN_1);
	engine_change_dir(-p1, ENGINE_1_DIR_PIN_0, ENGINE_1_DIR_PIN_1);
	
	SUMO::engine[0] = p0;
	SUMO::engine[1] = p1;
	
	ENGINE_0_OCR = _abs(p0) * 10;
	ENGINE_1_OCR = _abs(p1) * 10;
}

