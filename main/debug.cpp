#include "sumo.h"
#include "../../../avr/lib/usart/usart.h"

void debug_parse_input();

USART32(usb);

void debug_init(){
	usb.setCallback(debug_parse_input);
}

void debug_parse_input(){
	unsigned char cmd;
	usb >> cmd;
	
	if(cmd == '*'){
		asm("cli");
		asm("jmp 0");
	} 
	else if(cmd == '!'){
		debug_wait = 0;
	} 
	else {
		usb.read(); // :
		
		int id, value;
		
		switch(cmd){
			case 'G': // Ground sensors | G:#:(0|1)
				id = usb.readInt();
				usb.read();
				if(usb.readInt() == 1) setb(debug_ground_enabled, id);
				else clrb(debug_ground_enabled, id);
				break;
				
			case 'D': // Distance sensors | D:#:(0|1)
				id = usb.readInt();
				usb.read();
				if(usb.readInt() == 1) setb(debug_dist_enabled, id);
				else clrb(debug_dist_enabled, id);
				break;
				
			case 'M': // enable/disable manual engine mode | M:(0|1)
				debug_manual_engine_mode = usb.readInt();
				break;
				
				
			case 'E': // set engine power | E:#:(power[int])
				if(debug_manual_engine_mode){
					id = usb.readInt();
					usb.read();
					value = usb.readInt();
					
					if(id == 1) engine_set_power(SUMO::engine[0], value);
					else engine_set_power(value, SUMO::engine[1]);
				}
				break;
				
			case 'Q': // add item to queue | Q:(e0[int]):(e1[int]):(time[uint])
				int e0 = usb.readInt();
				usb.read();
				int e1 = usb.readInt();
				usb.read();
				int time = usb.readInt();
				
				Q.push(e0, e1, time);
				usb << "@\n";
				break;
				
		}
	}
	

	
	usb.clear();
}

void debug_send_state(){
	for(int i=0; i<GROUND_NUM; i++)
		usb << (SUMO::ground & _BV(i)) << ':';
		
	for(int i=0; i<DIST_NUM; i++)
		usb << SUMO::dist[i] << ':';
		
	for(int i=0; i<ENGINE_NUM; i++)
		usb << SUMO::engine[i] << ':';
		
	usb << debug_ground_enabled << '-';
	usb << debug_dist_enabled << '-';
	usb << debug_manual_engine_mode << '\n';
}




void debug(char c){
	usb << '^' << c << '\n';
}

void debug(int c){
	usb << '^' << c << '\n';
}


