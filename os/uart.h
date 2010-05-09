#ifndef _USART_H_
#define _USART_H_

#include "buffer.h"

class Uart {
public:
	Uart();
	char * package();
	bool awaiting();
	void sendByte(unsigned char byte);
	void push(char byte);
	Uart & operator<<(char * string);
private:
	Buffer buf;
};

#endif



