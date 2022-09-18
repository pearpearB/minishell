/*
	서로 독립된 프로세스가 데이터를 주고받을 수 있게 함

	SYNOPSIS
	#include <unistd.h>

	int pipe(int fildes[2]);

- fildes[0] : 함수 호출 후 데이터를 입력받을 수 있는 fd가 담김(파이프 출구)
- fildes[1] : 함수 호출 후 데이터를 출력할 수 있는 fd가 담김(파이프 입구)

	RETURN
	성공시 0
	실패시 -1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipes[2];

void parent_proccess() {
  char * buf = 0x0;
  ssize_t s;
  size_t len = 0;

  /* 읽기용 파이프를 닫는다 */
  close(pipes[0]);

  while ((s = getline(&buf, &len, stdin)) != -1) 
	{
    buf[s - 1] = 0x0;

    ssize_t sent = 0;
    char *data = buf;

    while (sent < s)
      sent += write(pipes[1], buf + sent, s - sent);
    free(buf);
    buf = 0x0;
    len = 0;
  }
  close(pipes[1]);
}

void child_proccess() 
{
  char buf[32];
  ssize_t s;

  /* 쓰기용 파이프를 닫는다 */
  close(pipes[1]);

  while ((s = read(pipes[0], buf, 31)) > 0) 
	{
    buf[s + 1] = 0x0;
    printf(">%s\n", buf);
  }
  exit(0);
}

int main() 
{
  pid_t child_pid;

  pipe(pipes);
  printf("pipe connected %d %d\n", pipes[0], pipes[1]);

  child_pid = fork();
  if (child_pid == 0)
    child_proccess();
  else
    parent_proccess();
  return (0);
}

// 사실 잘 이해가 되지 않는다.
