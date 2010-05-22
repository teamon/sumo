#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "os.h"
#include "uart.h"
#include "debug.h"

#define PACKAGE_SIZE 13

Uart uart;

char _buffer[50];

ISR(USART_RXC_vect){
	int c;
	c = UDR;
	uart.push(c);
}

char hex2num(char c){
	if(c >= '0' && c <= '9') return c-48;
	else if(c >= 'A' && c <= 'F') return c-55;
	else if(c >= 'a' && c <= 'f') return c-87;
	return -1;
}

//int hex_arg(char * pack, char start, char len){
//	char sign = 1;
//	int res = 0, i =0;
//	start += 3;
//	
//	if(pack[start] == '-') {
//		sign = -1;
//		i++;
//	}
//	
//	for(; i<len; i++){
//		res *= 0x10;
//		res += char2hex(pack[start+i]);
//	}
//	
//	return res*sign;
//}

int arg(char * pack, char start, char len){
	int res = 0, i = 0;
	start += 3;
	
	for(; i<len; i++){
		res <<= 4;
		res |= hex2num(pack[start+i]);
	}
	return res;
}

void modbus_error(char * msg){
	uart << "[ERROR] " << msg << EOP;
}

void modbus_info(char * msg, ...){
	char buf[50];
	va_list args;
	va_start(args, msg);
	vsprintf(buf, msg, args);
	va_end(args);
	uart << "[INFO] " << buf << EOP;
}

void dbg(char * msg, ...){
	char buf[50];
	va_list args;
	va_start(args, msg);
	vsprintf(buf, msg, args);
	va_end(args);
	uart << "[DBG] " << buf << EOP;
}


void debug_send_state(){
	char grd = os.ground();
	for(int i=0; i<4; i++)
		uart << (grd & _BV(i) ? '1' : '0') << ':';
	
	for(int i=0; i<6; i++)
		uart << os.dist[i] << ':';

	uart << '\n';
}

void debug_console(){
	if(uart.buf.size() >= PACKAGE_SIZE){
		debug_parse_package();
	}
	//debug_send_state();
}


void debug_parse_package(){
	char * pack = uart.package(PACKAGE_SIZE);
	
	// pack[0] - should be $. If not, packet is invalid
	// pack[1..2] - function
	// pack[3..10] - arguments
	// pack[11] - should be \r
	// pack[12] - should be \n
	
	// Example: $ E0  0 - engine 0, 70% power
	
	// Function	| Description			| Parameters		
	// -------------------------------------------------------------
	// E0		| Set engine 0 power	| ## - power [char]  
	// -------------------------------------------------------------
	// E1		| Set engine 1 power	| ## - power [char]
	// -------------------------------------------------------------
	// A0       | Push move to queue    | ## - Engine 0 power [char]
	//          |                       | ## - Engine 1 power [char]
	//          |                       | ## - Time [int]
	
	if(pack[0] == '$' && pack[11] == '\r' && pack[12] == '\n'){
		int code = hex2num(pack[1])*0x10 + hex2num(pack[2]);
				
		switch(code){
			case 0xE0:
				os.engine[0] = (char)arg(pack, 0, 2);
				modbus_info("Engine 0 set power=%d", os.engine[0]);
				break;
				
			case 0xE1:
				os.engine[1] = (char)arg(pack, 0, 2);
				modbus_info("Engine 1 set power=%d", os.engine[1]);
				break;
				
			case 0xA0:
			{
				char e0 = (char)arg(pack, 0, 2);
				char e1 = (char)arg(pack, 2, 2);
				int time = (int)arg(pack, 4, 4);
				os.queue.push(e0, e1, time);
				modbus_info("Queue push: e0=%d e1=%d time=%d", e0, e1, time);
			}
				break;
				
			default:
				modbus_error("Function not found");
				break;
				
		}
		
	} else {
		modbus_error("Invalid package");
		uart.buf.clear();
	}
	
	
	free(pack);	
}

