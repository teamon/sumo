#include "buffer.h"
#include <stdlib.h>

Buffer::Buffer(){
	_head = _tail = NULL;
	_size = 0;
}

void Buffer::clear(){
	while(_head != NULL) pop();
}

void Buffer::push(char c){
	BufferItem *curr = (BufferItem*) malloc(sizeof(BufferItem));
	if(_head == NULL) _head = curr;
	else _tail->next = curr;
	curr->character = c;
	curr->next = NULL;
	_tail = curr;
	_size++;
}

void Buffer::pop(){
	if(_head){
		BufferItem *tmp = _head->next;
		free(_head);
		_head = tmp;
		_size--;
	}
}

char * Buffer::front(){
	return (_head ? &(_head->character) : NULL);
}

int Buffer::size(){
	return _size;
}
