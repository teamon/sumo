#ifndef MOTOR_H_
#define MOTOR_H_

class Engine {
public:
	Engine();
	void stop();
	void setPower(char power); // power: -100..100
	char getPower();
	void reverse();
	
private:
	char power;
	bool _reverse;
};

#endif
