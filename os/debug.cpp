#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"
#include "debug.h"

Uart uart;

ISR(USART_RXC_vect){
	int c = UDR;
	uart.push(c);
}

void debug_console(){
	if(uart.awaiting()){
		debug_parse_package();
	}
}

void debug_parse_package(){
	char * pack = uart.package();
	
	
	uart << "[debug] got package: " << pack;
	
	
	free(pack);	
}
