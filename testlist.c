#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct event
{
	int init_value;
	int time;
	int semId;
	int periodic;
	struct event* next;
} clockEvent;

clockEvent* deltaClock = 0;

unsigned long myClkTime;
unsigned long myOldClkTime;

int insertDeltaClock(int time, int semId, int periodic)
{
	/*if (time < 0 || _getSempahore(semId) == NULL)
		return -1;

	if (time == 0) {
		semSignal(semId);
		return 0;
	}*/
	
	clockEvent* event = deltaClock;
	int total_time = 0;
	
	clockEvent* new_event = malloc(sizeof(clockEvent));
	new_event->init_value = time;
	new_event->semId = semId;
	new_event->periodic = periodic;
	
	if (event == NULL || time <= event->time) { //new_event should go at front of list

		new_event->time = time;
		new_event->next = event;
		deltaClock = new_event;

		if (event != NULL)
			event->time -= time;
	}
	else { //the first isn't null, or is less than the time of event we're inserting
		total_time += event->time;
		
		while (event->next != NULL && time > (total_time + event->next->time)) {
			total_time += event->next->time;
			event = event->next;
		} //if event->next is null, we're at the end of the list, so just tack it on
		  //we're also here if our time is less than the total time accumulated plus next
		new_event->time = time - total_time;
		new_event->next = event->next;
		if (new_event->next != NULL)
			new_event->next->time -= new_event->time;
		event->next = new_event;
	}

	return -1;
}

int deleteClockEvent(int semId)
{
	clockEvent* event = deltaClock;
	if (event == NULL)
		 return -1;
		 
	// checking if first is what we want, if so, removing it from front and checking again
	while (event != NULL && event->semId == semId) {
		if (event->next != NULL)
			event->next->time += event->time;
		deltaClock = event->next;
		free(event);
		event = deltaClock;
	}
	
	while (event != NULL && event->next != NULL) {	// not possible that event has the semId now
			
		if (event->next->semId == semId) {
			
			if (event->next->next != NULL) {
				event->next->next->time += event->next->time;
				
				//printf("semId %d time %d\n", event->next->next->semId,
				//	event->next->next->time);
			}
			
			clockEvent* to_delete = event->next;
			
			event->next = event->next->next;
			free(to_delete);
		}
		event = event->next;		
	}
	return 0;
}

int tickDeltaClock() {
 	return 0;
 }


/**
 *
 */
int listDeltaClock()
{
    puts("*********************");
    puts("Delta Clock Contents");
    // delta clock queue is empty
    if (!deltaClock) {
        puts("Empty");
    }
    // Print all of the delta clock queue's contents
    else {
        clockEvent * n = deltaClock;
        while (n) {
            printf("Semaphore %d with time=%d\n", n->semId, n->time);
            n = n->next;
        }
    }
    puts("*********************");
	return 0;
}

int main() {

	listDeltaClock();
	
	insertDeltaClock(5,1,0);
	listDeltaClock();
	
	insertDeltaClock(1,2,0);
	listDeltaClock();
	
	insertDeltaClock(1,3,0);
	listDeltaClock();
	
	insertDeltaClock(3,4,0);
	listDeltaClock();
	
	insertDeltaClock(5,5,0);
	listDeltaClock();
	
	insertDeltaClock(6,6,0);
	listDeltaClock();
	
	deleteClockEvent(3);
	listDeltaClock();
	
	deleteClockEvent(4);
	listDeltaClock();
	
	deleteClockEvent(6);
	listDeltaClock();
	
	deleteClockEvent(2);
	listDeltaClock();
	
	deleteClockEvent(5);
	listDeltaClock();
	
	deleteClockEvent(1);
	listDeltaClock();

}
