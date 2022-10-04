#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigint_handler(int signo)
{
	pid_t	pid;
	int		status;
	
	pid = waitpid(-1, &status, WNOHANG); // 부모가 -1 자식이 0
	printf("sig pid: %d\n", pid);        // main에서 fork를 안 하고 실행시 -1을 출력함
	if (signo == SIGINT)
	{
		printf("SIGINT\n");
		exit(SIGINT);
	}
	if (signo == SIGQUIT)
	{
		printf("SIGQUIT\n");
		exit(SIGQUIT);
	}
}


int main()
{
	pid_t pid;
	
	pid = fork();

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	while(1)
	{
    printf("jabae is HAPPY!\n");
    sleep(3);
	}
	return (0);
}