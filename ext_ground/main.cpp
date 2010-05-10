// Zewnetrzna obsługa czujnikiów odleglosci - ATtiny26

// Konfiguracja:

// ADC:     [___x_xxx]
//  0 - PA0
//  1 - PA1
//	2 - PA2
//	3 - PA4
// (na PA3 jest AREF)

// OUTPUT:   [xxxx____]
//  0 - PB4
//  1 - PB5
//  2 - PB6
//  3 - PB7


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define I_SEE 200

#define ADC_PORT PORTA
#define OUT_PORT PORTB


volatile int i = 0;
volatile int value;

ISR(ADC_vect){
	value = (ADCL | (ADCH << 8));
	if(value < I_SEE) OUT_PORT &= ~(1 << (i+4)); // clear bit
	else OUT_PORT |= (1 << (i+4)); // set bit
	if (++i > 3) i = 0;
	ADMUX = (0xC0 | i); // select ADC channel
	ADCSR |= _BV(ADSC); // start conversion
}

int main(void){
	OUT_PORT = 0xF0; // PD4..7 output
	
	// ADC init
	ADCSR = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //INIT ADC
	ADMUX = _BV(REFS0);
	
	sei();
	
    for(;;){}
	
    return 0;
}
