/*
	작업 디렉토리 위치 변경(== cd)

	SYNOPSIS
	#include <unistd.h>

	int chdir(const char *dirname);

	RETURN
	성공시 0
	실패시 -1
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int main(void)
{
	char cd_path[PATH_MAX] = { "../../minishell" }; // 상대경로도 가능

	int result = chdir(cd_path);

	if(result == 0)
		printf("Success\n");
	else
		printf("Fail\n");
	if (system("pwd") == -1) // 현재 위치 확인
        printf("Fail\n");
	return (0);
}
