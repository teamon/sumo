#ifndef QUEUE_H_
#define QUEUE_H_

struct QMove {
	char left, right, pri;
	int time;
};

class Queue {
public:
	Queue();
	~Queue();
	void push(QMove move);
	void push(char left, char right, int time);
	void push(char left, char right, int time, char priority);
	void pop();
	void clear();
	bool empty();
	QMove* front();
	void decrement(int time);
};

#endif
