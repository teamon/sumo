#include <avr/io.h>
#include "os.h"

#if DEBUG
#include "debug.h"
#endif

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
	unsigned char grd = (unsigned char)((~(GROUND_PIN >> 4)) & 0x0F); // 0000ABCD
	if(inverted) {
		return (((grd & 0x08) >> 3) | ((grd & 0x04) >> 1) | ((grd & 0x02) << 1) | ((grd & 0x01) << 3)) & 0x0F;
	} else {
		return grd;
	}
		
	//return ((grd << 2) | (grd >> 2)) & 0x0F;
}
