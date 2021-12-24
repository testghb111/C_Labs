#ifndef CQUEUE_H
#define CQUEUE_H

#include <malloc.h>

typedef struct NodeCQueue NCQ;
typedef struct CQueue CQ;

struct NodeCQueue {
	NCQ* next;
	time_t val1;
	long long val2;
};

struct CQueue
{
	NCQ* first;
	NCQ* last;
};

NCQ* addToCQ(CQ* q, time_t val1, long long val2) {
	if (q->last != 0) {
		NCQ* newNode = malloc(sizeof(NCQ));
		newNode->val1 = val1;
		newNode->val2 = val2;
		newNode->next = 0;
		q->last->next = newNode;
		q->last = q->last->next;
		return newNode;
	}
	else {
		q->last = malloc(sizeof(NCQ));
		q->last->next = 0;
		q->last->val1 = val1;
		q->last->val2 = val2;
		q->first = q->last;
		return q->last;
	}
}

void removeFromCQ(CQ* q) {
	if (q->first != 0) {
		if (q->last != q->first) {
			NCQ* oldFirst = q->first;
			q->first = q->first->next;
			free(oldFirst);
		}
		else {
			free(q->first);
			q->first = 0;
			q->last = 0;
		}
	}
}

void initCQ(CQ* q) {
	q->first = 0;
	q->last = 0;
}

void freeCQ(CQ* q) {
	while (q->first != 0) {
		removeFromCQ(q);
	}
}

#endif