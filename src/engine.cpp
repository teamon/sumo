#include "engine.h"
#include "sumo.h"

// TODO: Add secondary constructor with all required parameters for engine controller

Engine::Engine(){
	dir = 1;
	// TODO: AVR, Initialize engine
}

void Engine::stop(){
	// TODO: AVR, Stop motor immediately
}

void Engine::setPower(char p){
	if(p*dir == getPower()) return;
	power = p*dir;
}

void Engine::run(){
	if(power > 0) {
		// forward
		// TODO: AVR, Go forward
	} else if(power < 0) {
		// backward
		// TODO: AVR, Go backward
	} else { // (power == 0)
		stop();
	}
}

char Engine::getPower(){
	return power;
}

void Engine::invert(){
	dir *= -1;
}
