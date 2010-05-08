// Zewnetrzna obsługa czujnikiów odleglosci - ATmega8

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define I_SEE 200

volatile int i = 0;
volatile int value;

ISR(ADC_vect){
	value = (ADCL | (ADCH << 8));
	if(value < I_SEE) PORTD &= ~(1 << i); // clear bit
	else PORTD |= (1 << i); // set bit
	if (++i > 3) i = 0;
	ADMUX = (0xC0 | i); // select ADC channel
	ADCSRA |= _BV(ADSC); // start conversion
}

int main(void){
	DDRD = 0x0F; // PD0-4 output
	
	// ADC init
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //INIT ADC
	ADMUX = _BV(REFS0);
	
	sei();
	
    for(;;){}
	
    return 0;
}
