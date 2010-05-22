#include <avr/io.h>
#include <avr/interrupt.h>
#include "os.h"

#if DEBUG
#include "debug.h"
#endif

OS os;

int main(void){
#if DEBUG
	debug_init();
#endif
	
	os.init();
	sei();
	
    for(;;){
#if DEBUG
		debug_console();
#endif
		
		os.run();
    }
    return 0;
}
