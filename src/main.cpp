#include "sumo.h" //dupa

// global variables
char SUMO::engine[] = {0, 0};
volatile int SUMO::dist[] = {0,0,0,0,0,0};
char SUMO::ground = 0;
bool SUMO::inverted = false;
Queue Q;

#ifdef DEBUG
char debug_dist_enabled = (0xFF >> (8-DIST_NUM));
char debug_ground_enabled = (0xFF >> (8-GROUND_NUM));
char debug_manual_engine_mode = 0;
char debug_invert_enabled = 1;
volatile char debug_wait = 1;
#endif

void setup(){
#ifdef DEBUG
	usart_init();
#endif

	ground_init();
	dist_init();
	engine_init();

	sei(); // always at the end
}

void invert(){
	#ifdef DEBUG
	if(!debug_invert_enabled) return;
	#endif

	SUMO::inverted = !SUMO::inverted;
}

void escape(){
	#ifdef DEBUG
	SUMO::ground &= debug_ground_enabled;
	#endif
	
	if(SUMO::ground == 0) return;
	
	Q.clear();
	
	switch(SUMO::ground){
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
		break;
		
		case _BV(GROUND_BACK_LEFT) | _BV(GROUND_BACK_RIGHT): // BACK
			Q.push(100, 100, 5);
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_BACK_LEFT): // LEFT
		break;
		
		case _BV(GROUND_FRONT_RIGHT) | _BV(GROUND_BACK_RIGHT): // RIGHT
		break;
		
	}
}

void loop(){
	#ifdef DEBUG
	debug_send_state();
	debug_parse_input();
	#endif

	
	if(SUMO::inverted) SUMO::ground = (SUMO::ground >> 2) | (SUMO::ground << 2) & (0x0F); // 0000abcd => 0000cdab
	
	escape();
	
	#ifdef DEBUG
	if(!debug_manual_engine_mode){
	#endif
	
		if(!Q.empty()){
			SUMO::engine[ENGINE_LEFT] = Q.front()->left;
			SUMO::engine[ENGINE_RIGHT] = Q.front()->right;
			Q.decrement(1);
		} else {
			//Q.push(70, 50, 50);
		}
		
	#ifdef DEBUG
	}
	#endif
	

}

int main(void){
	setup();
	
	#ifdef DEBUG
	while(debug_wait);
	#endif

	for(;;){
		loop();
		_delay_ms(ITERATION_TIME);
	}
	return 0;
}
