#include "sumo.h"


volatile int i=0;


SIGNAL (SIG_ADC)
{
	
	dist[i] = (ADCL | (ADCH << 8));	
    ADMUX = (ADMUX & 0xE0) | i;
	if (i++ == 6) i=0;
	ADCSRA |= _BV(ADSC);
}


void dist_init ()
{
	DDRC=0b11111110;
		
		
	ADCSRA=_BV(ADEN)|_BV(ADSC)|_BV(ADIE)|_BV(ADPS2)|_BV(ADPS0); //INIT ADC sprawdz dla mega32
	ADMUX=_BV(REFS0); //INIT ADC 
	sei(); 
		
}
