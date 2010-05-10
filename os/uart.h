#ifndef _USART_H_
#define _USART_H_

#include "buffer.h"

#define EOP "\r\n"

class Uart {
public:
	Uart();
	char * package(char size);
	void sendByte(unsigned char byte);
	void push(char byte);
	Uart & operator<<(char * string);
	Uart & operator<<(const int number);
	Uart & Uart::operator<<(const char byte);
//private:
	Buffer buf;
};

#endif



