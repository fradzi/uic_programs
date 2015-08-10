#include<pthread.h>
#include<sched.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void randomize() {
	int i=random();
	if(i%2==0) sched_yield();
	else usleep(i%10000);
}
