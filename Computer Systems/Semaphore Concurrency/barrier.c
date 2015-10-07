/*
 * Filip Radzikowski
 * U. of Illinois, Chicago
 * CS361
 * Homework 6
 *
 */

#include"barrier.h"
#include<stdlib.h>
#include<stdio.h>

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
