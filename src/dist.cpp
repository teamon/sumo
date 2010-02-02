#include "sumo.h"

volatile char dist_i = 0;

ISR(ADC_vect)
{
	*(dist + dist_i) = (ADCL | (ADCH << 8));
	if (++dist_i > 5) dist_i = 0;
	ADMUX = (0xC0 | dist_i);
	ADCSRA |= _BV(ADSC);
}


void dist_init (){
	DIST_DDR = 0xE0; // PA0-PA5 -> input

	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS0); 
}
