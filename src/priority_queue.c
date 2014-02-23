// @DISABLE_SWAPS
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "scheduler.h"
#include "kernel.h"


Node* getNodeP(tid_t tid) 
{
	Node* nd = &tasks[tid];
	assert(nd->tid == NO_TASK);	
	nd->tid = tid;
	nd->next = NULL;
	return nd;
}

void clearNodeP(NodeP* node)
{
	node->tid = NO_TASK;
	node->virtual_runtime = 0;//TODO review this
	node->next = NULL;
	return;
}

PriorityQueue* makeQueueP() 
{
    PriorityQueue* queue = (PriorityQueue*) malloc(sizeof(PriorityQueue)); 
    queue->curNode = NULL;
	queue->lastNode = NULL;
	//queue->priority = priority;
	return queue;
}


int removeNodeP(PriorityQueue* list, tid_t tid)
{
	NodeP* currentNode = list->curNode;
	if (currentNode == NULL)
		return NO_TASK;
	if (currentNode->tid == tid)
	{
		list->curNode = currentNode->next;
		clearNodeP(currentNode);
		return TRUE;
	}
	else
	{
		while (currentNode->next != NULL)
		{
			if (currentNode->next->tid == tid)
			{
				NodeP* nextNode = currentNode->next->next;
				if (list->lastNode == nextNode)
					list->lastNode = currentNode;	
				clearNodeP(currentNode->next);
				currentNode->next = nextNode;
				return TRUE;
			}
			currentNode = currentNode->next;
		}
		return NO_TASK;
	}
	//never gets here
	return FALSE;
}

void enqueueP(PriorityQueue* list, tid_t tid, /*For testing priority queue:long vrt*/)
{
	NodeP* to_add = (NodeP*)malloc(sizeof(NodeP));
	to_add->tid = tid;
	to_add->virtual_runtime = vrt;
	//TODO calculate to_add's virtual_runtime, add it to this struct

	if (list->curNode == NULL) //if list is empty, so lastNode is also null
	{
		list->lastNode = to_add;
	   	list->curNode = list->lastNode;	
	}
	else	
	{
		NodeP* current = list->curNode;
		//if we should be at front of list
		if (to_add->virtual_runtime <= current->virtual_runtime) {
			list->curNode = to_add;
			to_add->next = current;	
		}
		else if (current->next == NULL) { //only 1 thing in the list
			//thing we are adding should be at front
			if (to_add->virtual_runtime <= current->virtual_runtime) {
				list->curNode = to_add;
				to_add->next = current;
				list->lastNode = current;
				//current = to_add;
			}
			//thing we are adding should be at end
			else {
				current->next = to_add;
				to_add->next = NULL;
				list->lastNode = to_add;
			}
		}
		else {
			while (current->next != NULL) {
				if (to_add->virtual_runtime <= current->next->virtual_runtime) {
					to_add->next = current->next;
					current->next = to_add;	
					return;
				}
				current = current->next;
			}
			//if we get out here, current->next is NULL and we haven't added, so 
			//add to end
			current->next = to_add;
			to_add->next = NULL;
		}
	}
	return;
}

int dequeueP(PriorityQueue* list)
{
	if (list->curNode == NULL)
	{
		return NO_TASK;
	}
	NodeP* cur = list->curNode;	
    int tid = list->curNode->tid;
	list->curNode = list->curNode->next;
	if (list->curNode == NULL)
		list->lastNode = NULL;
	//clearNodeP(cur);	
    return tid;
}

//For testing purposes
void printQueueP(PriorityQueue* list)
{
	NodeP* cur = list->curNode;
	while (cur != NULL)
	{
		printf("(%i %ld) ", cur->tid, cur->virtual_runtime);
		cur = cur->next;
	}
	printf("\n");
}

void clearListP(PriorityQueue *list)
{
	return;
	//list->curNode == NULL;
}

void clearListNodeP(PriorityQueue *list)
{
	//Node* currentNode = list->curNode;
	//while (currentNode != NULL)
	//{
	//	Node* next = currentNode->next;
	//	free(currentNode);
	//	currentNode = next;
	//}
	return;
}

// @ENABLE_SWAPS
