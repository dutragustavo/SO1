#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

void* work()
{
	printf("Nova thread %lu\n", pthread_self());
}

int main(int argc, char const *argv[])
{
	pthread_t threads[MAX_THREADS];
	for (int i = 0; i < MAX_THREADS; ++i){
		pthread_create(&threads[i], NULL, work, NULL); 
	} 

	for (int i = 0; i < MAX_THREADS; ++i){
		pthread_join(threads[i], NULL);
	}

}