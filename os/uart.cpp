#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

#define UART_BAUD 9600L

Uart::Uart(){
	int ubrr = (int)(F_CPU/UART_BAUD/16) - 1;
	
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);
}

void Uart::push(char c){
	buf.push(c);
}

void Uart::sendByte(unsigned char byte){
	while (!(UCSRA & (1<<UDRE)));
	UDR = byte;
}

bool Uart::awaiting(){
	return buf.size() >= 8;	
}

char * Uart::package(){
	char * pack = (char *) malloc(sizeof(char)*8); // 8 bits package
	for(int i = 0; i<8; i++){
		pack[i] = *(buf.front());
		buf.pop();
	}
	return pack;
}

Uart & Uart::operator<<(char * string){
	while (*string != '\0') sendByte(*string++);
	return *this;
}

