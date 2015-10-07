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

sem_t *service_sem, *request_sem;
void pair();

void init() {

	service_sem = (sem_t*)malloc(sizeof(sem_t));
	request_sem = (sem_t*)malloc(sizeof(sem_t));

	sem_init(service_sem, 0, 0);
	sem_init(request_sem, 0, 1);

}

void wait_for_service() {
	
	sem_wait(service_sem);
	pair();
	sem_post(request_sem);

	// call pair() when ready
}

void wait_for_request() {
	
	sem_wait(request_sem);
	pair();
	sem_post(service_sem);

	// call pair() when ready
}
