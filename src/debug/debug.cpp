#include "../sumo.h"
#include "buffer.h"

Buffer buffer;

ISR(USART_RXC_vect){
	char in;
	in = UDR;
	
	switch(in){
		case '*': // must be fast
			asm("cli"); 
			asm("jmp 0");
			break;
		case '!':
			debug_wait = 0;
			break;
	}
	
	buffer.push(in);
	debug_parse_input();
}

void debug(char c){
	usart_write_byte('^');
	usart_write_byte(c);
	usart_write_byte('\n');
}

void debug(int c){
	usart_write_byte('^');
	usart_write_number(c);
	usart_write_byte('\n');
}

void debug_send_state(){
	for(int i=0; i<GROUND_NUM; i++){
		if(ground & _BV(i)) usart_write_byte('1');
		else usart_write_byte('0');
		usart_write_byte(':');
	}
	
	for(int i=0; i<DIST_NUM; i++){
		usart_write_number(dist[i]);
		usart_write_byte(':');
	}

	for(int i=0; i<ENGINE_NUM; i++){
		usart_write_number(SUMO::engine[i]);
		usart_write_byte(':');
	}

	usart_write_number(debug_ground_enabled);
	usart_write_byte('-');
	usart_write_number(debug_dist_enabled);
	usart_write_byte('-');
	usart_write_number(debug_manual_engine_mode);
	usart_write_byte('\n');
}

void debug_parse_input(){	
	if(buffer.empty()) return;
	switch(*buffer.front()){
		case 'G':
			if(buffer.size() >= 2){
				buffer.pop();
				char n = buffer.read();
				if(*buffer.front() == '0') clrb(debug_ground_enabled, char2int(n));
				else setb(debug_ground_enabled, char2int(n));
				buffer.pop();
			}
			break;

		case 'D':
			if(buffer.size() > 2){
				buffer.pop();
				char n = buffer.read();
				if(*buffer.front() == '0') clrb(debug_dist_enabled, char2int(n));
				else setb(debug_dist_enabled, char2int(n));
				buffer.pop();
			}
			break;

		case 'M': // enable/disable manual engine mode
			if(buffer.size() > 1){
				buffer.pop();
				if(*buffer.front() == '0') debug_manual_engine_mode = 0;
				else debug_manual_engine_mode = 1;
			}
			break;
			
		case 'E':
			// E:eid:sign:X:X:X
			if(debug_manual_engine_mode && buffer.size() >= 6){
				buffer.pop();
				char eid = buffer.read();
				char sign = buffer.read() == '-' ? -1 : 1;
				int val = 0;
				
				for(int i=0; i<3; i++){
					val *= 10; 
					val += char2int(*buffer.front());
					buffer.pop();
				}
				
				SUMO::engine[char2int(eid)] = val*sign;
			}

			break;


		default:	
			buffer.pop();
			break;
	}
}
