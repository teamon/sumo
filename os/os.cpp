#include "os.h"

void OS::init(){
	initEngines();
	initDist();
	initGround();
}

void OS::run(){
	if(!queue.empty()){
		engine[0] = queue.front()->left;
		engine[1] = queue.front()->right;
		queue.decrement(1);
	} else {
		// default values
		// engine[0] = 0;
		// engine[1] = 0;
	}


	runEngines();
}

void OS::escape(){
	char grd = ground();
	
	if(grd == 0) return;
	
	queue.clear();
	
	switch(grd){
		case 0x01: // front left
		case 0x02: // front right
		case 0x01 | 0x02: // front
			invert();
			break;
			
		case 0x04 | 0x08: // back
			queue.push(100, 100, 5);
			break;
			
		case 0x04: // back left
			queue.push(100, 80, 5);
			break;
		
		case 0x08: // back right
			queue.push(80, 100, 5);
			break;
			
		case 0x01 | 0x04: // left
			// TODO: Escape when LEFt
			break;
		
		case 0x02 | 0x08: // right
			// TODO: Escape when RIGHT
			break;
	}
}

void OS::invert(){
	
}
