/*
	현재 작업중인 디렉토리 path를 가져옴 (==`pwd`)

	SYNOPSIS
	#include <unistd.h>

	char *getcwd(
							char *buf,  // 현재 작업 디렉토리를 저장할 버퍼
							size_t size // 버퍼에 할당할 메모리 크기
							);

	RETURN
	성공시 포인터 반환
	실패시 null
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
  char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("Directory: %s\n", cwd);
	return (0);
}
