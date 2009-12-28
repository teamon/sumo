#include "engine.h"
#include "sumo.h"

// TODO: Add secondary constructor with all required parameters for engine controller

Engine::Engine(){
	_reverse = false;
}

void Engine::stop(){
	// TODO: Stop motor immediately
}

void Engine::setPower(char p){
	if(p == getPower()) return;
	power = p;
	p = abs(p);
	
	if(p > 100) p = 100; // max power is 100%
	if(power > 0) {
		// forward
		// TODO: Go forward
	} else if(power < 0) {
		// backward
		// TODO: Go backward
	} else { // (power == 0)
		stop();
	}
}

char Engine::getPower(){
	return power;
}

void Engine::reverse(){
	_reverse = !_reverse;
}
