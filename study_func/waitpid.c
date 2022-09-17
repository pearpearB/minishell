/*
	자식 프로세스가 동작중이면 상태를 얻을 때까지(시그널을 받을 때까지) 대기함

	SYNOPSIS
	#include <sys/wait.h>

	pid_t waitpid(pid_t pid,     // 대기할 자식 프로세스
								int *stat_loc, // 자식 프로세스 상태값
								int options.   // 0 혹은 상수 조합
								);

	RETURN
	성공시 상태가 변경된 자식 프로세스의 PID 값 
				options가 WNUHANG인 경우 종료된 자식 프로세스가 없으면 0
	실패시 -1
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int		status;
	
	pid = fork();

	if(pid > 0)  // 부모 프로세스
	{	
		printf("<--부모 프로세스-->\n");
		printf("[PID: %d] [fork PID: %d]\n",getpid(), pid);
		sleep(3);
		// POINT : 부모프로세스에 sleep시간이 짧아도, 자식 프로세스 sleep시간까지 block됨!
		waitpid(pid, &status, 0);
		printf("[status: %d]\n 부모 종료\n", status);
		// POINT : status로 자식 프로세스에서 종료된 상태코드를 받아옴!
	}
	else // 자식 프로세스
	{
		printf("<--자식 프로세스-->\n");
		printf("[PID: %d] [fork PID: %d]\n", getpid(), pid);
		sleep(10);
		printf("자식 종료\n");
		exit(1);
	}
	exit (0);
}

/*
자식 프로세스에서 
exit(0); 하면, 부모 status == 0;
exit(1); 하면, 부모 status == 256;
실행중에
$ kill -9 [자식 프로세스 PID] 하면, 부모 status == 9;
*/
