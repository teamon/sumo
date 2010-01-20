#include "../sumo.h"
#include "buffer.h"

Buffer buffer;

ISR(USART_RXC_vect){
	char in;
	in = UDR;
	buffer.push(in);
}

void debug(char c){
	usart_write_byte('^');
	usart_write_byte(c);
	usart_write_byte('\n');
}

void read_until_newline(){
	while(usart_read_byte() != '\n'){}
}

void enable_disable(char *reg){
	char c = usart_read_byte();
	char v = usart_read_byte();
	debug(c);
	debug(v);
	if(v == '0') clrb(*reg, char2int(c));
	else if(v == '1') setb(*reg, char2int(c));
	//read_until_newline();
}

void debug_send_state(){
	for(int i=0; i<GROUND_NUM; i++){
		if(ground & _BV(i)) usart_write_byte('1');
		else usart_write_byte('0');
		usart_write_byte(':');
	}
	
	for(int i=0; i<DIST_NUM; i++){
		usart_write_number(_BV(dist[i]));
		usart_write_byte(':');
	}

	for(int i=0; i<ENGINE_NUM; i++){
		usart_write_number(engine[i].getPower());
		usart_write_byte(':');
	}

	usart_write_number(debug_ground_enabled);
	usart_write_byte('-');
	usart_write_number(debug_dist_enabled);
	usart_write_byte('-');
	usart_write_number(debug_manual_engine_mode);
	usart_write_byte('\n');
}

void debug_read_input(){
	char input = usart_read_byte();
	
	char a = usart_read_byte();
	char b = usart_read_byte();
	char c = usart_read_byte();
	
	debug(input);
	debug(a);
	debug(b);
	debug(c);
	
	switch(input){
		case '*': // reset
			asm("cli"); 
			asm("jmp 0"); 
			break;
		case 'G': // enable/disable ground sensors
			enable_disable(&debug_ground_enabled);
			break;
			
		// case 'D': // enable/disable distance sensors
		// 	enable_disable(&debug_dist_enabled);
		// 	break;
			
		// case 'M': // enable/disable manual engine mode
		// 	char v = usart_read_byte();
		// 	if(v == '0') debug_manual_engine_mode = 0;
		// 	else if(v == '1') debug_manual_engine_mode = 1;
		// 	read_until_newline();
		// 	break;
			
		// case 'E': // set motor power (only at manual mode)
		// 	if(!debug_manual_engine_mode) break;
		// 	
		// 	char c = usart_read_byte();
		// 	
		// 		char sign = 1;
		// 		int value = 0;
		// 		char v;
		// 		
		// 		while(1){
		// 			v = usart_read_byte();
		// 			if(v == '\n') break;
		// 			else if(v == '-') sign = -1;
		// 			else {
		// 				value *= 10;
		// 				value += char2int(v);
		// 			}
		// 		}
		// 		
		// 		engine[char2int(c)].setPower(v);
		// 	
		// 	break;
	}
}

void debug_wait_for_input(char c){
	while(usart_read_byte() != c){}
}

