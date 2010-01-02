#include "sumo.h"
#include "queue.h"

struct QItem {
	QMove move;
	QItem* next;
};

QItem *head, *tail;

Queue::Queue(){
	head = tail = NULL;
}

Queue::~Queue(){
	clear();
}

void Queue::clear(){
	while(head != NULL) pop();
}

bool Queue::empty(){
	return (head == NULL);
}

void Queue::push(QMove move){
	move.time *= MOVE_TIME_MULTIPLIER;
	QItem *curr = (QItem*) malloc(sizeof(QItem));
	if(head == NULL) head = curr;
	else tail->next = curr;
	curr->move = move;
	curr->next = NULL;
	tail = curr;
}

void Queue::push(char left, char right, int time, char priority){
	QMove m = {left, right, priority, time};
	push(m);
}

void Queue::push(char left, char right, int time){
	push(left, right, time, 0);
}

void Queue::pop(){
	if(head){
		QItem *tmp = head->next;
		free(head);
		head = tmp;
	}
}

QMove* Queue::front(){
	return (head ? &(head->move) : NULL);
}

void Queue::decrement(int time){
	if(head){
		head->move.time -= time;
		if(head->move.time <= 0) pop();
	}
}
