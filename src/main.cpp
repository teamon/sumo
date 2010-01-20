#include "sumo.h" //dupa

// global variables
Engine engine[ENGINE_NUM];
char ground;
char dist[DIST_NUM];
bool inverted = false;
Queue Q;

#ifdef DEBUG
char debug_dist_enabled = (0xFF >> (8-DIST_NUM));
char debug_ground_enabled = (0xFF >> (8-GROUND_NUM));
char debug_manual_engine_mode = 0;
char debug_invert_enabled = 1;
#endif

void setup(){
	// initialize engines
	engine[ENGINE_LEFT] = Engine();
	engine[ENGINE_RIGHT] = Engine();
	
	// initialize ground sensors
	ground = 0; // ....0000
	
	
#ifdef DEBUG
	usart_init();
#endif


	sei(); // always at the end
}

void invert(){
	#ifdef DEBUG
	if(!debug_invert_enabled) return;
	#endif
	
	engine[ENGINE_LEFT].invert();
	engine[ENGINE_RIGHT].invert();
	
	inverted = !inverted;
}

void escape(){
	#ifdef DEBUG
	ground &= debug_ground_enabled;
	#endif
	
	if(ground == 0) return;
	
	Q.clear();
	
	switch(ground){
		case _BV(GROUND_FRONT_LEFT):
			invert();
		break;
			
		case _BV(GROUND_FRONT_RIGHT):
			invert();
		break;
		
		// TODO: Escape

		case _BV(GROUND_BACK_LEFT):
			Q.push(100, 80, 5);
		break;
		
		case _BV(GROUND_BACK_RIGHT):
			Q.push(80, 100, 5);
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_FRONT_RIGHT): // FRONT
			invert();
			// Q.push(-100, -100, 10);
			// Q.push(-100, 100, 20);
			// Q.push(100, 100, 10);
		break;
		
		case _BV(GROUND_BACK_LEFT) | _BV(GROUND_BACK_RIGHT): // BACK
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_BACK_LEFT): // LEFT
		break;
		
		case _BV(GROUND_FRONT_RIGHT) | _BV(GROUND_BACK_RIGHT): // RIGHT
		break;
		
	}
}

void loop(){
	#ifndef AVR
	simulate();
	#endif
	
	#ifdef DEBUG
	debug_send_state();
	debug_read_input();
	#endif
	
	if(inverted) ground = (ground >> 2) | (ground << 2) & (0x0F); // 0000abcd => 0000cdab
	
	escape();
	
	if(!Q.empty()){
		engine[ENGINE_LEFT].setPower(Q.front()->left);
		engine[ENGINE_RIGHT].setPower(Q.front()->right);
		Q.decrement(1);
	} else {
		Q.push(70, 50, 50);
	}
}

int main(void){
	setup();
	
	#ifdef DEBUG
	debug_wait_for_input(OFFBLAST_CHAR);
	#endif

	for(;;){
		loop();
		_delay_ms(ITERATION_TIME);
	}
	return 0;
}
