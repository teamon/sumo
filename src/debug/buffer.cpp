#include "../sumo.h"
#include "buffer.h"

struct BufferItem {
	char character;
	BufferItem* next;
};

BufferItem *_head, *_tail;

Buffer::Buffer(){
	_head = _tail = NULL;
	_counter = 0;
}

void Buffer::clear(){
	while(_head != NULL) pop();
}

bool Buffer::empty(){
	return (_head == NULL);
}

void Buffer::push(char c){
	BufferItem *curr = (BufferItem*) malloc(sizeof(BufferItem));
	if(_head == NULL) _head = curr;
	else _tail->next = curr;
	curr->character = c;
	curr->next = NULL;
	_tail = curr;
	_counter++;
}

void Buffer::pop(){
	if(_head){
		BufferItem *tmp = _head->next;
		free(_head);
		_head = tmp;
		_counter--;
	}
}

char * Buffer::front(){
	return (_head ? &(_head->character) : NULL);
}

int Buffer::size(){
	return _counter;
}

char Buffer::read(){
	char n = *front();
	pop();
	return n;
}
