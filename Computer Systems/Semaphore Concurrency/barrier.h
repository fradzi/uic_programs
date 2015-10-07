#include<semaphore.h>
typedef struct {
	sem_t *mutex, *enter, *exit;
	int size;
	int count;
} barrier;
void barrier_init(barrier* m, int size);
void barrier_wait(barrier* m);
