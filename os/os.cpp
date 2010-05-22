#include "os.h"

#if DEBUG
#include "debug.h"
#endif

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
#if DEBUG
		if(DEBUG_OPTS[DEBUG_AUTO_SEARCH]){
			queue.push(DEBUG_OPTS[DEBUG_AUTO_SEARCH_SPEED_0], DEBUG_OPTS[DEBUG_AUTO_SEARCH_SPEED_1], 10, 0);
		} else {
			engine[0] = 0;
			engine[1] = 0;
		}
#else
		engine[0] = 0;
		engine[1] = 0;
#endif
	}

	runEngines();
}

void OS::escape(){
#if DEBUG
	if(!DEBUG_OPTS[DEBUG_AUTO_ESCAPE]) return;
#endif
	
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
			queue.push(100, 20, 5, 3);
			break;
		
		case 0x08: // back right
			queue.push(20, 100, 5, 3);
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
#if DEBUG
	dbg("Inverted: %d", inverted);
#endif
}
