#include "os.h"
#include "debug.h"

void OS::init(){
	inverted = false;
	initEngines();
	initDist();
	initGround();
}

void OS::run(){
	int pri = 0;
	
	if(!queue.empty()){
		pri = queue.front()->pri;
	}
	
	
	if(pri < 3){
		escape();
	}
	
	
	if(!queue.empty()){
		engine[0] = queue.front()->left;
		engine[1] = queue.front()->right;
		queue.decrement(1);
	} else {
		// default values - searching
		engine[0] = 0;
		engine[1] = 0;
	}


	runEngines();
}

void OS::escape(){
	unsigned char grd = ground();
	
	if(grd == 0) return;
	
	queue.clear();
	
	switch(grd){
		case 0x01: // front left
		case 0x02: // front right
		case 0x01 | 0x02: // front
			invert();
			break;
			
		case 0x04 | 0x08: // back
			queue.push(100, 100, 5, 3);
			break;
			
		case 0x04: // back left
			queue.push(100, 60, 5, 3);
			break;
		
		case 0x08: // back right
			queue.push(60, 100, 5, 3);
			break;
			
		case 0x01 | 0x04: // left
			queue.push(100, -100, 4, 3);
			break;
		
		case 0x02 | 0x08: // right
			queue.push(-100, 100, 4, 3);
			break;
	}
}

void OS::invert(){
	inverted = !inverted;
}
