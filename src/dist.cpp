#include "sumo.h"

volatile int i = 0;

SIGNAL (SIG_ADC)
{
	dist[i] = (ADCL | (ADCH << 8));	
    ADMUX = (ADMUX & 0xE0) | i;
	if (i++ == 6) i = 0;
	ADCSRA |= _BV(ADSC);
}


void dist_init (){
	DIST_DDR = 0xE0; // PA0-PA5 -> input

	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS0); 
	ADMUX = _BV(REFS0); 
}
