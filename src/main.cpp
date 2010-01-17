#include "sumo.h"
#include "queue.h"

// global variables
Engine engine[ENGINE_NUM];
char ground;
bool inverted = false;
Queue Q;

// volatile int adcValue;

// SIGNAL(SIG_ADC){
// 	adcValue = (ADCL | (ADCH << 8));
// 	// adcValue = ADCH;
// 	
// 	// usart_write_number(adcValue);
// 	
// 	// usart_write_byte('\n');
// 	setb(ADCSRA, ADSC);
// }

void setup(){
	// initialize engines
	engine[ENGINE_LEFT] = Engine();
	engine[ENGINE_RIGHT] = Engine();
	
	// initialize ground sensors
	ground = 0; // ....0000
	
	
	#ifdef AVR

	usart_init();

	#endif
}

void invert(){
	engine[ENGINE_LEFT].invert();
	engine[ENGINE_RIGHT].invert();
	
	inverted = !inverted;
}

void escape(){
	if(ground == 0) return;
	
	Q.clear();
	
	switch(ground){
		case _BV(GROUND_FRONT_LEFT):
			invert();
			// Q.push(-100, -100, 5);
			// Q.push(-100, 100, 20);
		break;
			
		case _BV(GROUND_FRONT_RIGHT):
			invert();
			// Q.push(-100, -100, 5);
			// Q.push(-100, 100, 20);
		break;
		
		// TODO: Escape

		case _BV(GROUND_BACK_LEFT):
			Q.push(100, 80, 5);
		break;
		
		case _BV(GROUND_BACK_RIGHT):
			Q.push(80, 100, 5);
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_FRONT_RIGHT): // FRONT
			invert();
			// Q.push(-100, -100, 10);
			// Q.push(-100, 100, 20);
			// Q.push(100, 100, 10);
		break;
		
		case _BV(GROUND_BACK_LEFT) | _BV(GROUND_BACK_RIGHT): // BACK
		break;
		
		
		case _BV(GROUND_FRONT_LEFT) | _BV(GROUND_BACK_LEFT): // LEFT
		break;
		
		case _BV(GROUND_FRONT_RIGHT) | _BV(GROUND_BACK_RIGHT): // RIGHT
		break;
		
	}
}

void loop(){
	#ifndef AVR
	simulate();
	#endif
	
	if(inverted) ground = (ground >> 2) | (ground << 2) & (0x0F); // 0000abcd => 0000cdab
	
	escape();
	
	if(!Q.empty()){
		engine[ENGINE_LEFT].setPower(Q.front()->left);
		engine[ENGINE_RIGHT].setPower(Q.front()->right);
		Q.decrement(1);
	} else {
		Q.push(70, 50, 50);
	}
}

int main(void){
	setup();

	int i = 0;
	
	
	for(;;){
		usart_write_number((i++) % 8 < 4 ? 1 : 0);
		usart_write_byte(':');
 	 	usart_write_number(0);
	  	usart_write_byte(':');
	  	usart_write_number(0);
	  	usart_write_byte(':');
	  	usart_write_number(1);
	  	usart_write_byte(':');
  	
	  	usart_write_number(90);
	  	usart_write_byte(':');
	  	usart_write_number(100);
	  	usart_write_byte(':');
	  	usart_write_number(1000);
	  	usart_write_byte(':');
	  	usart_write_number(300);
	  	usart_write_byte(':');
	  	usart_write_number(800);
	  	usart_write_byte(':');
	  	usart_write_number(5);
	  	usart_write_byte(':');
	
	  	usart_write_number(80);
	  	usart_write_byte(':');
	  	usart_write_number(-40);
	  	usart_write_byte(':');
	  	usart_write_string("dupa");
	  	usart_write_byte('\n');
				
		//loop();
		_delay_ms(ITERATION_TIME);
	}
	return 0;
}
