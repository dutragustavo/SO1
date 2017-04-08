#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t cpid = 1;
	int status;
	for(int i = 0; i < 2; ++i)
	{
		if(cpid == 0)
			break;

		cpid = fork();
		if(cpid == 0)
			printf("Processo %d filho de %d\n", getpid(), getppid());
	}

	if(cpid > 0){
		wait(&status);
		return 0;
	}
			
	cpid = 1;
	for(int j = 0; j < 2; ++j)
	{
		if(cpid == 0)
			break;

		cpid = fork();
		if(cpid == 0){
			printf("Processo %d filho de %d\n", getpid(), getppid());
		}
		else{
			wait(&status);
		}
	}

	return 0;
}