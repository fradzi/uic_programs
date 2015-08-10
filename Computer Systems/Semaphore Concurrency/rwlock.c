/*
 * Filip Radzikowski
 * U. of Illinois, Chicago
 * CS361
 * Homework 6
 *
 */



#include"rwlock.h"
#include<stdlib.h>
#include<stdio.h>

int cc_readers;


void rwlock_init(rwlock* m, int concurrent_readers){ 

	m->mutex = (sem_t*)malloc(sizeof(sem_t));
	m->readers = (sem_t*)malloc(sizeof(sem_t));

	sem_init(m->mutex, 0, 1);
	sem_init(m->readers, 0, 1);

	// Initially there are no writes to read
	cc_readers = 0;

}

void rlock(rwlock * m){
	sem_wait(m->mutex);
		
		cc_readers++; // incrempent number of readers
		if (cc_readers == 1){ // if there is anything to read
			sem_wait(m->readers);
		}
	
	sem_post(m->mutex);

}

void runlock(rwlock * m){
	sem_wait(m->mutex);
	
		cc_readers--; // if read then decrement number of readers
		if (cc_readers == 0){ // if there is nothing to read
			sem_post(m->readers);
		}
	
	sem_post(m->mutex);

}

void wlock(rwlock * m){
	
	sem_wait(m->readers);
	
}

void wunlock(rwlock * m){
	
	sem_post(m->readers);
}

