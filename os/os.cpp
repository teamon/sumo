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
