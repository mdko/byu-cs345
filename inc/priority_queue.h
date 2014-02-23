#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "type_defs.h"

typedef struct nodep {
	tid_t tid;
//	int virtual_runtime;
	struct nodep* next;
} NodeP;

typedef struct priorityQueue {
	NodeP *curNode; 
	NodeP *lastNode;
	//struct queueList *nextList;
	//unsigned short priority;
} PriorityQueue;

//Node* getNode(tid_t tid);

void clearNodeP(NodeP*);

PriorityQueue* makeQueueP();

/**
 * Used for descheduling a node from the list
 */
int removeNodeP(PriorityQueue*, tid_t);

/**
 * Place node in appropriate spot in list based
 * on virtual run-time
 */
void enqueueP(PriorityQueue*, tid_t);

/**
 * Remove front node from list
 */
int dequeueP(PriorityQueue*);

void printQueueP(PriorityQueue*);

void clearListP(PriorityQueue *list);

void clearListNodeP(PriorityQueue *list);

#endif
