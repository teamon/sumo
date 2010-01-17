#include "sumo.h"

void usart_init(){
	// int ubrr = (F_CPU/(4800*16))-1;
	int ubrr = 51;

	// speed settings
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;	
	
	// receiver and transmiter
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);
}

void usart_write_byte(unsigned char byte) {
	while (!(UCSRA & (1<<5)));
	UDR = byte;
}

void usart_write_string(char *string) {
	while (*string != '\0') usart_write_byte(*(string++));
}

void usart_write_number(long number){
	// negative numbers
	if(number < 0) usart_write_byte('-');
	number = abs(number);
	
	long a = 1000000000; //9
	long b = 999999999;
	char k;
	
	for(int i=0; i<10; i++){
		k = (number / a) % 10;
		if(number > b || i == 9){
			usart_write_byte(k+48);
		}
		
		a /= 10;
		b /= 10;
	}
}

// unsigned char usart_read_byte() {
// 	if (UCSRA & (1<<7))
// 		return UDR;
// 	else
// 		return 0;
// }
