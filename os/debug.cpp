#include <avr/interrupt.h>
#include <stdlib.h>
#include "os.h"
#include "uart.h"
#include "debug.h"

Uart uart;

ISR(USART_RXC_vect){
	int c;
	c = UDR;
	uart.push(c);
}

int char2hex(char c){
	if(c >= '0' && c <= '9') return c-48;
	else if(c >= 'A' && c <= 'F') return c-55;
	else if(c >= 'a' && c <= 'f') return c-87;
	return -1;
}

int hex_arg(char * pack, char start, char len){
	char sign = 1;
	int res = 0, i =0;
	start += 3;
	
	if(pack[start] == '-') {
		sign = -1;
		i++;
	}
	
	for(; i<len; i++){
		res *= 0x10;
		res += char2hex(pack[start+i]);
	}
	
	return res*sign;
}

void modbus_error(char * msg){
	uart << "[ERROR] " << msg << EOP;
}

void debug_console(){
	if(uart.awaiting()){
		debug_parse_package();
	}
	
}

void dbg(char * label, int num){
	uart << label << ": " << num << EOP;
}

void debug_parse_package(){
	char * pack = uart.package();
	
	// pack[0] - should be $. If not, packet is invalid
	// pack[1..2] - function
	// pack[3..5] - arguments
	// pack[6] - should be \r
	// pack[7] - should be \n
	
	// Example: $E0070 - engine 0, 70% power
	
	// Function	| Description			| Parameters
	// ----------------------------------------------------
	// 0xE0		| Set engine 0 power	| ### - power [int]
	// 0xE1		| Set engine 1 power	| ### - power [int]
	
	if(pack[0] == '$' && pack[6] == '\r' && pack[7] == '\n'){
		int code = char2hex(pack[1])*0x10 + char2hex(pack[2]);
		
		dbg("code", code);
		
		switch(code){
			case 0xE0:
				os.engine[0] = hex_arg(pack, 0, 3);
				break;
				
			case 0xE1:
				os.engine[1] = hex_arg(pack, 0, 3);
				break;
				
			default:
				modbus_error("Function not found");
				break;
				
		}
		
	} else {
		modbus_error("Invalid package");
	}
	
	
	free(pack);	
}

