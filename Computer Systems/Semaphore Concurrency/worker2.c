/*
 * Filip Radzikowski
 * U. of Illinois, Chicago
 * CS361
 * Homework 6
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>


int back, front;

sem_t *mutex2, *frontQueue, *backQueue;

typedef struct {
	sem_t *mutex, *enter, *exit;
	int size;
	int count;
} barrier;

barrier wall;


void barrier_init(barrier* b, int s) {
	
	b->mutex = (sem_t*)malloc(sizeof(sem_t));
	b->enter = (sem_t*)malloc(sizeof(sem_t));
	b->exit = (sem_t*)malloc(sizeof(sem_t));
	
	sem_init(b->mutex, 0, 1);
	sem_init(b->enter, 0, 0);
	sem_init(b->exit, 0, 1);
	b->size = s;
	b->count = 0;
}

void barrier_wait(barrier* b) {

	sem_wait(b->mutex);
		b->count++;

	if ( b->count == b->size){
		sem_wait(b->exit);
		sem_post(b->enter);	// 3rd person, enterr++

	}
	sem_post(b->mutex);

	sem_wait(b->enter);//2 people, enter = 1 // spot where people wait
	sem_post(b->enter);

	/*****************************************************************/
	sem_wait(b->mutex);
		b->count--;
	
	if(b->count == 0){
		sem_wait(b->enter);
		sem_post(b->exit);
	}
	sem_post(b->mutex);

	sem_wait(b->exit);
	sem_post(b->exit);
}

void group();



void init() {

	front = 0;
	back = 0;
	mutex2 = (sem_t*)malloc(sizeof(sem_t));
	frontQueue = (sem_t*)malloc(sizeof(sem_t));
	backQueue = (sem_t*)malloc(sizeof(sem_t));


	sem_init(mutex2, 0, 1);
	sem_init(frontQueue, 0, 0);
	sem_init(backQueue, 0, 0);

	barrier_init(&wall,3);

}

void back_ready() {
	
	sem_wait(mutex2);
	back++;
	
	if( back >= 2 && front >=1){
		sem_post(backQueue);
		sem_post(backQueue);
		back -=2;
		sem_post(frontQueue);
		front -=1;
	}else{
		sem_post(mutex2);
	}
	
	sem_wait(backQueue);
	
	printf("back ready\n");
	group();
	barrier_wait(&wall);
}

void front_ready() {
	
	sem_wait(mutex2);
	front++;
	
	if( back >= 2 ){
		sem_post(backQueue);
		sem_post(backQueue);
		back -=2;
		sem_post(frontQueue);
		front -=1;
	}else{
		sem_post(mutex2);
	}

	sem_wait(frontQueue);

	printf("front ready\n");
	group();
		
	barrier_wait(&wall);
	sem_post(mutex2);
}
