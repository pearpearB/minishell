/*
	시그널을 받은 프로세스는 시그널에 따라 미리 지정된 기본 동작을 수행하거나, 
	미리 정해놓은 함수에 의해 원하는 동작을 할 수 있다.
	시그널(sig)과 시그널을 처리할 핸들러(func)를 인수로 넣어주면 핸들러를 반환한다.

	SYNOPSIS
	#include <signal.h>

	void (*signal(
							int sig,          // 시그널 번호
							void (*func)(int) // 시그널에 처리할 핸들러 함수
				);)(int);

	RETURN
	성공시 시그널 핸들러
	실패시 SIG_ERR
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signo)
{
	printf("^C를 누른 것을 기억하고 있어요. 다시 누르면 종료\n");
	signal(SIGINT, SIG_DFL); // SIG_DFL : 신호 기본 처리, ^C의 기본 동작을 처리함
}

int main()
{
	signal(SIGINT, sigint_handler); // SIGINT : ^C
	while(1)
	{
    printf("jabae is HAPPY!\n");
    sleep(3);
	}
	return (0);
}
