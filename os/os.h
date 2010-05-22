#ifndef _OS_H_
#define _OS_H_

#define DEBUG 1

#include "queue.h"

// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)

#define _abs(x) ( ((x) < 0) ? (-(x)) : (x) )
#define _min(a,b) ( ((a) > (b)) ? (b) : (a) )

class OS {
public:
	void init();
	void run();
	void escape();
	void invert();
	
	// engines.cpp
	void initEngines();
	void runEngines();
	
	// dist.cpp
	void initDist();
	
	// ground.cpp
	void initGround();
	unsigned char ground();

	
	Queue queue;
	
	volatile int engine[0];
	volatile int _prev_engine[2];
	volatile int dist[6];
	bool inverted;
};

extern OS os;

#endif
