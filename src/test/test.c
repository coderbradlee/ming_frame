#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	pid_t pid=fork();
	if(pid>0)
	{
		printf("in parent process,sleep for one minute\n");
		int status=-10;
		pid_t pr=wait(&status);
		printf("in parent process,%d\n",pr);
		if(WIFEXITED(status))
		{
			printf("exit normally,%d,exit code %d\n",pr,WEXITSTATUS(status));
		}
		else
		{
			printf("exit abnormally\n");
		}
		printf("in parent process,after sleep\n");
	}
	else if(pid==0)
	{
		printf("in parent process,pid:%u,ppid:%u\n",getpid(),getppid());
		exit(0);
	}
}
