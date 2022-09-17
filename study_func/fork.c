/*
	새로운 프로세스 생성, 
	호출되는 자식 프로세스는 부모프로세스의 메모리를 그대로 복사함

	SYNOPSIS
	#include <unistd.h>

	pid_t	fork(void);

	RETURN
	성공시 부모프로세스는 자식프로세스의 PID값, 자식 프로세스는 0
	실패시 -1
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int		x;
	
	pid = fork();
	x = 0;

	if(pid > 0)  // 부모 프로세스
	{	
		x = 1;
		printf("<--부모 프로세스-->\n");
		printf("[PID: %d] [fork PID: %d] [x: %d]\n",getpid(), pid, x);
	}
	else // 자식 프로세스
	{
		x = 2;
		printf("<--자식 프로세스-->\n");
		printf("[PID: %d] [fork PID: %d] [x: %d]\n", getpid(), pid, x); 
		// POINT : 자식 프로세스의 fork(); 값은 0 !
	}
	return (0);
}
