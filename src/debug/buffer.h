#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
public:
	Buffer();
	void push(char c);
	void pop();
	void clear();
	bool empty();
	char * front();
	int size();
	char read();
	
private:
	int _counter;
};

#endif
