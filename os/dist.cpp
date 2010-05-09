#include <avr/io.h>
#include <avr/interrupt.h>
#include "os.h"

#define DIST_DDR DDRA

volatile int dist_i = 0;

ISR(ADC_vect){
	os.dist[dist_i] = (ADCL | (ADCH << 8));
	if (++dist_i > 5) dist_i = 0;
	ADMUX = (0xC0 | dist_i);
	ADCSRA |= _BV(ADSC);
}


void OS::initDist (){
	DIST_DDR = 0xE0; // PA0-PA5 -> input
	
	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS0); 
}
