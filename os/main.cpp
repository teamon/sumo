#include <avr/io.h>
#include <avr/interrupt.h>
#include "os.h"
#include "debug.h"

OS os;

int main(void){
	os.init();
	sei();
	
	for(int i = 1; i < 10; i++){
		os.queue.push(i*10, i*10, 10);
		os.queue.push(-i*10, -i*10, 10);
	}
	
		
    for(;;){
		debug_console();
		
		os.run();
    }
    return 0;
}
