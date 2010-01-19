#include "sumo.h"

void read_until_newline(){
	while(usart_read_byte() != '\n'){}
}

void enable_disable(char *reg){
	char c = usart_read_byte();
	if(c){
		char v = usart_read_byte();
		if(v == '0') clrb(*reg, char2int(c));
		else if(v == '1') setb(*reg, char2int(c));
	}
	read_until_newline();
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

	usart_write_string("");
	usart_write_byte('\n');
}

void debug_read_input(){
	char input = usart_read_byte();
	switch(input){
		case 'G': // enable/disable ground sensors
			enable_disable(&debug_ground_enabled);
			break;
			
		case 'D': // enable/disable distance sensors
			enable_disable(&debug_dist_enabled);
			break;
			
		case 'M': // enable/disable manual engine mode
			char v = usart_read_byte();
			if(v == '0') debug_manual_engine_mode = 0;
			else if(v == '1') debug_manual_engine_mode = 1;
			read_until_newline();
			break;
			
		case 'E': // set motor power (only at manual mode)
			if(!debug_manual_engine_mode) break;
			
			char c = usart_read_byte();
			if(c){
				char sign = 1;
				int value = 0;
				char v;
				
				while(1){
					v = usart_read_byte();
					if(v == '\n') break;
					else if(v == '-') sign = -1;
					else {
						value *= 10;
						value += char2int(v);
					}
				}
				
			}
			break;
	}
}

