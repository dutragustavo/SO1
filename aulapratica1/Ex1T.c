#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void* work()
{
	printf("Nova thread %lu", pthread_self());
}

int main(int argc, char const *argv[])
{
	pthread_t t; 
	pthread_create(&t, NULL, work, NULL);
	pthread_join(t, NULL);
}