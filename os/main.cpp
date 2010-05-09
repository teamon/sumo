#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"

void init(){
	
}

int main(void){
	sei();
	
    for(;;){
		debug_console();
    }
    return 0;
}
