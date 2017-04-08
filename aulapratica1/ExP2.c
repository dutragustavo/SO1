#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void PrintProcess(pid_t pid)
{
	if(pid > 0){
		printf("Processo pai %d criou %d\n", getpid(), pid);
	}
	else{
		printf("Processo filho %d\n", getpid());
	}
}

int main(int argc, char const *argv[])
{
	pid_t cpid = fork();
	for (int i = 0; i < 3; ++i)
	{
		if(cpid > 0){
			PrintProcess(cpid);
			cpid = fork();
		}
		else{
			break;
		}

	}
	PrintProcess(cpid);
	return 0;
}