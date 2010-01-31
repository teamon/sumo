#include "sumo.h"
#include "engine.h"

ISR (TIMER1_OVF_vect)           
{
	ENGINE_0_OCR = engine[0].run();
	ENGINE_1_OCR = engine[1].run();
}

void engine_init(){
	engine[0] = Engine(ENGINE_0_DIR_PIN);
	engine[1] = Engine(ENGINE_1_DIR_PIN);
	
	TCCR1A = _BV(COM1A1) |  _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
	TCCR1B |= _BV(CS11); // preskaler clk/8
	
	ENGINE_0_OCR = 0;
	ENGINE_1_OCR = 0;
	
	setb(ENGINE_DDR, ENGINE_0_PIN);
	setb(ENGINE_DDR, ENGINE_1_PIN);
	setb(ENGINE_DDR, ENGINE_0_DIR_PIN);
	setb(ENGINE_DDR, ENGINE_1_DIR_PIN);
	setb(ENGINE_DDR, ENGINE_0_FW_PIN);
	setb(ENGINE_DDR, ENGINE_1_FW_PIN);
	setb(ENGINE_PORT, ENGINE_0_FW_PIN);
	setb(ENGINE_PORT, ENGINE_1_FW_PIN);
	
	TIMSK = _BV(TOIE1);
}

Engine::Engine(unsigned char _dir_pin){
	dir = 1;
	dir_pin = _dir_pin;
	power = 0;
}

void Engine::stop(){
	// setb(ENGINE_PORT, )
	// TODO: AVR, Stop motor immediately
}

void Engine::setPower(char p){
	power = p;
}

char Engine::getPower(){
	return power;
}

int Engine::run(){
	char p;
	
	if(power * dir > 0){
		clrb(ENGINE_PORT, dir_pin);
		p = power;
	} else {
		setb(ENGINE_PORT, dir_pin);
		p = -power;
	}
	
	return p*10;
}

void Engine::invert(){
	dir *= -1;
}
