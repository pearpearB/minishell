/*
	man 2 unlink
	파일 또는 링크를 삭제함(== rm)

	SYNOPSIS
	#include <unistd.h>

	int unlink(const char *path);

	RETURN
	성공시 0
	실패시 -1
*/

#include <unistd.h>

int main(void)
{
	unlink("./test.c"); // 디렉토리는 삭제가 안되는 듯!

	return (0);
}
