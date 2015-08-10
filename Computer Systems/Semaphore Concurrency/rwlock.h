#include<semaphore.h>
typedef struct {
	sem_t *mutex, *writers, *readers;
} rwlock;
void rwlock_init(rwlock* m, int concurrent_readers);
void rlock(rwlock * m);
void runlock(rwlock * m);
void wlock(rwlock * m);
void wunlock(rwlock * m);
