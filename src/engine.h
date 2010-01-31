#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine(){}
	Engine(unsigned char _dir_pin);
	void stop();
	void setPower(char p); // power: -100..100
	char getPower();
	void invert();
	int run();
	
private:
	unsigned char dir_pin;
	volatile char power;
	char dir;
};

#endif
