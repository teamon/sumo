#ifndef _OS_H_
#define _OS_H_

// macros
#define setb(byte, bit) byte |= (1 << bit)
#define clrb(byte, bit) byte &= ~(1 << bit)
#define negb(byte, bit) byte ^= (1 << bit)
#define bset(byte, bit) byte & (1 << bit)

#define _abs(x) ( ((x) < 0) ? (-(x)) : (x) )
#define _min(a,b) ( ((a) > (b)) ? (b) : (a) )
class OS {
public:
	// initializers
	void init();
	
	// engines.cpp
	void initEngines();
	void run();
	
	
	volatile int engine[0];
	volatile int _prev_engine[2];
};

extern OS os;

#endif
