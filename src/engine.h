#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine(){}
	Engine(int pin);
	void stop();
	void setPower(char p); // power: -100..100
	char getPower();
	void invert();
	int run();
	
private:	
	int __;
	volatile char power;
	char dir;
	int dirpin;
};

#endif
