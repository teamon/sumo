#include "sumo.h"
#include "queue.h"

// global variables
Engine engine[ENGINE_NUM];
char ground;
Queue Q;

void setup(){
	// initialize engines
	engine[ENGINE_LEFT] = Engine();
	engine[ENGINE_RIGHT] = Engine();
	
	// initialize ground sensors
	ground = 0; // ....0000
}

void reverse(){
	engine[ENGINE_LEFT].reverse();
}

void escape(){
	if(ground == 0) return;
	
	Q.clear();
	
	switch(ground){
		case _BV(GROUND_FRONT_LEFT):
			Q.push(-100, -100, 30);
		break;
			
		case _BV(GROUND_FRONT_RIGHT):
			Q.push(-100, -100, 30);
		break;

		case _BV(GROUND_BACK_LEFT):
		break;
		
		case _BV(GROUND_BACK_RIGHT):
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_FRONT_RIGHT):
		break;
		
		case _BV(GROUND_BACK_LEFT) | _BV(GROUND_BACK_RIGHT):
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_BACK_LEFT):
		break;
		
		case _BV(GROUND_FRONT_RIGHT) | _BV(GROUND_BACK_RIGHT):
		break;
		
	}
}

void loop(){
	#ifndef AVR
	simulate();
	#endif
	
	escape();
	
	
	if(!Q.empty()){
		engine[ENGINE_LEFT].setPower(Q.front()->left);
		engine[ENGINE_RIGHT].setPower(Q.front()->right);
		Q.decrement(1);
	} else {
		Q.push(40, 60, 50);
	}
}


int main(void){
	setup();
	
	for(;;){
		loop();
		_delay_ms(ITERATION_TIME);
	}
	return 0;
}
