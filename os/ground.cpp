#include <avr/io.h>
#include "os.h"

#define GROUND_DDR DDRB
#define GROUND_PORT PORTB
#define GROUND_0_PIN 0
#define GROUND_1_PIN 1
#define GROUND_2_PIN 2
#define GROUND_3_PIN 3

#define GROUND_FRONT_LEFT  0
#define GROUND_FRONT_RIGHT 1
#define GROUND_BACK_LEFT   2
#define GROUND_BACK_RIGHT  3

void OS::initGround(){
	clrb(GROUND_DDR, GROUND_0_PIN);
	clrb(GROUND_DDR, GROUND_1_PIN);
	clrb(GROUND_DDR, GROUND_2_PIN);
	clrb(GROUND_DDR, GROUND_3_PIN);
}

char OS::ground(){
	return (GROUND_PORT & 0x0F);
}
