// Zewnetrzna obsługa czujnikiów odleglosci - ATtiny26

// Konfiguracja:

// ADC:      [____xxxx]
//  0 - PC0
//  1 - PC1
//	2 - PC2
//	3 - PC4
	
// OUTPUT:   [xxxx____]
//  0 - PD0
//  1 - PD1
//  2 - PD2
//  3 - PD3


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define I_SEE 500

#define ADC_PORT PORTA
#define OUT_PORT PORTB
#define OUT_DDR  DDRB

volatile int i = 0;
volatile int value;

ISR(ADC_vect){
	value = (ADCL | (ADCH << 8));
	if(value > I_SEE) OUT_PORT &= ~(1 << i); // clear bit
	else OUT_PORT |= (1 << i); // set bit
	if (++i > 3) i = 0;
	ADMUX = (0xC0 | i); // select ADC channel
	ADCSR |= _BV(ADSC); // start conversion
}

int main(void){
	OUT_DDR = 0xFF;
	
	// ADC init
	ADCSR = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //INIT ADC
	ADMUX = _BV(REFS0);
	
	sei();	
	
    for(;;){}
	
    return 0;
}
