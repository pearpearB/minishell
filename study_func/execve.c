/*
	execve함수를 호출한 프로세스를 새 프로세스로 바꿔줌

	SYNOPSIS
	#include <unistd.h>

	int execve(
						const char *path,   // 실행시킬 파일 경로 또는 파일명
						char *const argv[], // 새롭게 실행될 프로그램에 전달할 인수 목록(마지막  NULL)
						char *const envp[]  // 새롭게 실행될 프로그램에 전달할 환경 설정 목록(key = value 형태, 마지막  NULL)
						);

	RETURN
	성공시 없음, 이미 지정된 프로그램의 로직 실행
	실패시 -1
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	char *str[2];
	
	// str[0] = "/bin/ls";
	str[0] = "/bin/cat";
	str[1] = NULL;

	if (execve(str[0], str, NULL) == -1)
		printf("프로그램 실행 error: %s\n", strerror(errno));

	printf("명령어가 실행된 이후임으로 여기는 출력되지 않음");

	return (0);
}

/*
실행방법
a.out
결과는 str[0]에 넣은 명령어를 실행함
*/
