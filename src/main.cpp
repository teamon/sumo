#include "sumo.h"

// global variables
Engine engine[ENGINE_NUM];
char ground;

void setup(){
	// initialize engines
	engine[ENGINE_LEFT] = Engine();
	engine[ENGINE_RIGHT] = Engine();
	
	// initialize ground sensors
	ground = 0;
}


int main(void){
	setup();
	
	return 0;
}
