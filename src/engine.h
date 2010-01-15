#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine();
	void stop();
	void setPower(char power); // power: -100..100
	char getPower();
	void invert();
	
private:
	char power;
	char dir;
	void run();
};

#endif
