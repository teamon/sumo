#include "sumo.h"

void ground_init(){
	//set data direction port
	clrb(GROUND_DDR, GROUND_0_PIN);
	clrb(GROUND_DDR, GROUND_1_PIN);
	clrb(GROUND_DDR, GROUND_2_PIN);
	clrb(GROUND_DDR, GROUND_3_PIN);
}

void ground_get(){
	ground = (GROUND_PORT & 0xF);
}
