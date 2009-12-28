#include "sumo.h"
#include "queue.h"

// global variables
Engine engine[ENGINE_NUM];
char ground;
Queue q;

void setup(){
	// initialize engines
	engine[ENGINE_LEFT] = Engine();
	engine[ENGINE_RIGHT] = Engine();
	
	// initialize ground sensors
	ground = 0;
}

void loop(){
	#ifndef AVR
	simulate();
	#endif
	
	
	if(!q.empty()){
		engine[ENGINE_LEFT].setPower(q.front()->left);
		engine[ENGINE_RIGHT].setPower(q.front()->right);
		q.decrement(1);
	} else {
		q.push(40, 60, 30);
		q.push(-60, -40, 30);
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
