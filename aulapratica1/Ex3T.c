#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 128

int contador_global = 0;

void* work()
{
	for (int i = 0; i < 100; ++i)
	{
		contador_global++;
	}
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

	printf("Valor final do contador%d\n", contador_global);
}