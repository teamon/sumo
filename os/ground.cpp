#include <avr/io.h>
#include "os.h"
#include "debug.h"

#define GROUND_DDR DDRB
#define GROUND_PIN PINB
#define GROUND_0_PIN 4
#define GROUND_1_PIN 5
#define GROUND_2_PIN 6
#define GROUND_3_PIN 7


void OS::initGround(){
	clrb(GROUND_DDR, GROUND_0_PIN);
	clrb(GROUND_DDR, GROUND_1_PIN);
	clrb(GROUND_DDR, GROUND_2_PIN);
	clrb(GROUND_DDR, GROUND_3_PIN);
}

unsigned char OS::ground(){
	unsigned char grd = (unsigned char)((~(GROUND_PIN >> 4)) & 0x0F);
	if(inverted) return (grd << 2) | ((grd >> 2) & 0x03);
	else return grd;
}

