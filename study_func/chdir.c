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

int main(void)
{
	char cd_path[PATH_MAX] = { "/Users/baejaeyeong/42_ing/" };

	int result = chdir(cd_path);

	if(result == 0)
		printf("Success\n"); // ? 잘 모르겠다. success라고 뜨긴 하는데 뭐가 성공인거지?
	else
		perror("Fail...\n");
	return (0);
}