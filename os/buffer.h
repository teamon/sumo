#ifndef _BUFFER_H_
#define _BUFFER_H_

struct BufferItem {
	char character;
	BufferItem* next;
};


class Buffer {
public:
	Buffer();
	void push(char c);
	void pop();
	void clear();
	char * front();
	int size();
	
private:
	int _size;
	BufferItem *_head, *_tail;
};

#endif
