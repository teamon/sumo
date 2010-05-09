#include <avr/io.h>
#include <avr/interrupt.h>
#include "os.h"
#include "debug.h"

OS os;

int main(void){
	os.init();
	sei();
	
    for(;;){
		debug_console();
		
		os.run();
    }
    return 0;
}
