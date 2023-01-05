# 🌈 minishell

Summary: The objective of this project is for you to create a simple shell. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.

요약: 이번 프로젝트의 목표는 간단한 쉘을 만드는 것입니다. 맞아요, 당신만의 작은 bash나 zsh이요. 프로세스나 파일 디스크립터에 대해 아주 많이 배우게 될 겁니다.

# ✨ 함수 공부하기

## 🔴 readline 관련 함수

### ✅ readline

`char *prompt` 를 터미널에 띄워주고 터미널에서 입력된 문자열을 리턴함

*리턴값은 malloc할당되므로 반드시 free해주어야 함

```c
#include <readline/readline.h>
#include <readline/history.h>

char *readline(const char *prompt); // 터미널에 띄울 문자열
```

**RETURN**

성공시 개행이 제거된 읽어들인 문자열, eof의 경우 NULL

실패시 errno

### ✅ **rl_on_new_line**

readline함수에 프롬프트가 새로운 줄을 만났다고 알려줌

주로 개행을 출력한 후에, 시그널을 처리할 때 사용됨, `rl_replace_line` 이나 `rl_redisplay`와 같이 사용함

```c
#include <readline/readline.h>

int rl_on_new_line(void);
```

**RETURN**

성공시 

실패시 

### ✅ **rl_replace_line**

readline함수의 rl_line_buffer를 `char *text`로 대체함

*mac에서는 사용불가로, brew로 readline을 설치, 나오는 옵션을 넣어서 컴파일 해야함

```c
#include <readline/readline.h>

void rl_replace_line(
		const char *text, // 대체할 텍스트
		int clear_undo.   // 0이 아니라면 현재 행과 관련된 실행 취소 목록이 지워짐
		);
```

### ✅ **rl_redisplay**

`rl_replace_line` 로 바꾼 `rl_line_buffer` 를 `prompt` 에 출력함

```c
#include <readline/readline.h>

void rl_redisplay(void); // 0이 아니면 현재 내용으로 디스플레이를 업데이트함
```

### ✅ **add_history**

`string` 을 히스토리 목록에 넣음

*이렇게 넣어진 문자열은 readline에서 방향키로 가져올 수 있음

```c
#include <readline/readline.h>
#include <readline/history.h>

void add_history(char *string); // 히스토리 목록에 넣을 문자열
```

## 🔴 프로세스 관련 함수

### ✅ fork

자식 프로세스를 생성함

이 때 자식 프로세스는 부모프로세스의 메모리를 그래도 복사하고, fork() 이후로 각자의 메모리를 사용함

```c
#include <unistd.h>

pid_t fork(void);
```

**RETURN**

성공시 부모프로세스에서는 자식 프로세스의 PID 값, 자식 프로세스는 0

실패시 -1

### ✅ execve

execve함수를 호출한 프로세스를 path 명령어로 새 프로세스로 바꿔줌

```c
#include <unistd.h>

int execve(
	const char *path,   // 교체할 실행 파일/ 명령어로, 실행시킬 파일 경로
	char *const argv[], // 새롭게 실행될 프로그램에 전달할 인수 목록(마지막  NULL)
	char *const envp[]  // 새롭게 실행될 프로그램에 전달할 환경 설정 목록(key = value 형태, 마지막  NULL)
	);
```

**RETURN**

성공시 없음, 이미 지정된 프로그램의 로직 실행

실패시 -1

### ✅ pipe

서로 독립된 프로세스가 데이터를 주고받을 수 있게 함

```c
#include <unistd.h>

int pipe(int fildes[2]);
```

- fildes[0] : 함수 호출 후 데이터를 입력받을 수 있는 fd가 담김(파이프 출구)
- fildes[1] : 함수 호출 후 데이터를 출력할 수 있는 fd가 담김(파이프 입구)

**RETURN**

성공시 0

실패시 -1

### ✅ wait

자식프로세스의 종료 상태를 회수함

자식 프로세스가 동작중이면 상태를 얻을 때까지(커널을 통해 시그널을 받을 때까지) 대기함

```c
#include <sys/wait.h>

pid_t wait(int *stat_loc); // 자식 프로세스 상태값
```

**RETURN**

성공시 자식 프로세스 PID 값

실패시 -1

### ✅ waitpid

자식프로세스의 종료 상태를 회수함

자식 프로세스가 동작중이면 상태를 얻을 때까지(커널을 통해 시그널을 받을 때까지) 대기함

wait보다 다양한 옵션 사용이 가능함

```c
#include <sys/wait.h>

pid_t waitpid(
  pid_t pid,     // 대기할 자식 프로세스
	int *stat_loc, // 자식 프로세스 상태값
	int options.   // 0 혹은 상수 조합
	);
```

- pid_t pid
    - < -1 : 그룹 id가 절대값과 같은 자식 프로세스를 기다림
    - == -1 : 임의의 자식 프로세스 id를 기다림
    - == 0 : 자신과 같은 그룹 id를 가진 프로세스를 기다림
    - > 0 : 인자로 주어진 pid 값을 가진 자식 프로세스만 기다림
- options
    - == 0 : 자식이 결과를 리턴할 때까지 기다림(block)
    - …etc

**RETURN**

성공시 상태가 변경된 자식 프로세스의 PID 값 / options가 WNUHANG인 경우 종료된 자식 프로세스가 없으면 0

실패시 -1

### ✅ wait3, wait4

자식프로세스가 종료되는 것을 기다림

종료된 자식 프로세스의 상태와 자원 사용량을 알 수 있음

```c
#include <sys/wait.h>

pid_t wait3(
	int *stat_loc, 
	int options, 
	struct rusage *rusage // 자식 프로세스의 자원 사용량에 대한 정보
	);

pid_t wait4(
	pid_t pid,
	int *stat_loc, 
	int options, 
	struct rusage *rusage
	);
```

**RETURN**

성공시 프로세스의 PID 값 / options가 WNUHANG인 경우 종료된 자식 프로세스가 없으면 0

실패시 -1

### ✅ signal

시그널을 받은 프로세스는 시그널에 따라 미리 지정된 기본 동작을 수행하거나, 미리 정해놓은 함수에 의해 원하는 동작을 할 수 있다.

시그널(sig)과 시그널을 처리할 핸들러(func)를 인수로 넣어주면 핸들러를 반환한다.

### ✅ kill

시그널을 받을 프로세스의 id(pid)를 받아 해당하는 프로세스에 시그널(sig)을 보낸다.

## 🔴 디렉토리 관련 함수

### ✅ getcwd

현재 작업중인 디렉토리 *path*를 가져옴(== `pwd`)

```c
#include <unistd.h>

char *getcwd(
	char *buf,  // 현재 작업 디렉토리를 저장할 버퍼
	size_t size // 버퍼에 할당할 메모리 크기
	);
```

**RETURN**

성공시 포인터 반환

실패시 null

### ✅ chdir

작업 디렉토리 위치 변경(== `cd`)

`dirname` 는 상대경로도 가능하다.

```c
#include <unistd.h>

int chdir(const char *dirname); // 변경할 위치
```

**RETURN**

성공시 0

실패시 -1

### ✅ opendir

디렉토리를 염

```c
#include <dirent.h>

DIR *opendir(const char *filename); // 열 디렉토리 이름
```

**RETURN**

성공시 디렉토리 정보를 담은 구조체 포인터

실패시 NULL

### ✅ readdir

디렉토리 내 모든 파일과 디렉토리 정보 구함

*readdir()를 처음 호출하면 opendir()를 통해 연 디렉토리 내의 **첫번째 파일**에 대한 정보를 가져오고, 다시 호출하면 **두번째**, 다시 호출하면 세번째… 더 이상 파일이나 디렉토리가 없으면 NULL 반환

```c
#include <dirent.h>

struct dirent *readdir(DIR *dirp); // open시 반환되는 구조체 포인터
```

**RETURN**

성공시 디렉토리 내의 파일, 디렉토리에 대한 정보를 담은 구조체 포인터

실패시 NULL

### ✅ closedir

디렉토리를 닫음

```c
#include <dirent.h>

int closedir(DIR *dirp);
```

**RETURN**

성공시 0

실패시 -1

## 🔴 파일 관련 함수

### ✅ stat(2)

파일의 정보(크기, 권한, 생성일시, 최종 변경일 등)를 얻음(== `ls -al`)

```c
#include <sys/stat.h>

int stat(
	const char *restrict path, // 파일명 또는 파일의 상대결로나 절대경로
	struct stat *restrict buf  // 파일의 정보가 저장됨
	);

/*
struct stat {
    dev_t     st_dev;     // ID of device containing file
    ino_t     st_ino;     // inode number
    mode_t    st_mode;    // 파일의 종류 및 접근권한 //***여기가 젤루 종요하다고 한다
    nlink_t   st_nlink;   // 파일의 하드링크 수 
    uid_t     st_uid;     // user ID 
    gid_t     st_gid;     // group ID
    dev_t     st_rdev;    // device ID (if special file)
    off_t     st_size;    // 파일의 크기(bytes)
    blksize_t st_blksize; // blocksize for file system I/O
    blkcnt_t  st_blocks;  // number of 512B blocks allocated
    time_t    st_atime;   // 마지막 접근 시각 
    time_t    st_mtime;   // 마지막 수정 시각
    time_t    st_ctime;   // 마지막 상태 변경 시각
};
*/
```

**RETURN**

성공시 0

실패시 -1

### ✅ lstat, fstat

lstat : symbolic link인 파일 자체의 정보를 얻음

// ? symbolic link : 컴퓨팅에서 심볼릭 링크 또는 기호화된 링크는 절대 경로 또는 상대 경로의 형태로 된 다른 파일이나 디렉터리에 대한 참조를 포함하고 있는 특별한 종류의 파일

fstat : 인자로 받은 fd의 정보를 얻음

```c
#include <unistd.h>

int lstat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
```

**RETURN**

성공시 0

실패시 -1

### ✅ unlink(2)

파일 또는 링크를 삭제함

```

정확하게는 unlink는 hard link의 이름을 삭제하고 hard link가 참조하는 count를 1감소시킵니다. hard link의 참조 count가 0이 되면, 실제 파일의 내용이 저장되어 있는 disk space를 free하여 OS가 다른 파일을 위해서 사용할 수 있도록 합니다. 따라서 hard link를 생성하지 않은 파일은 바로 disk space를 해제하여 사실상 파일 삭제합니다.

그러나 open(2)으로 파일이 열려진 상태에서 unlink(2)를 호출하여 hard link 참조 count가 0이 되어도 directory entry에서 파일 이름 등의 정보는 삭제되지만 disk space는 해제되지 않습니다.

OS는 hard link 참조 count가 0이고 file open 참조 count가 0일 때에 파일의 내용이 저장된 disk space를 해제합니다.
```

출처: [https://www.it-note.kr/177](https://www.it-note.kr/177)

```c
#include <unistd.h>

int unlink(
	const char *pathname // 파일명 또는 파일의 상대결로나 절대경로
	);
```

**RETURN**

성공시 0

실패시 -1

### ✅ dup

fd를 복제해 다른 fd를 생성함

```c
#include <unistd.h>

int dup(int file_des);
```

**RETURN**

성공시 fd

실패시 -1

### ✅ dup2

fd2에 기존 fd를 복제함, fd2가 열러 있다면 닫은 후 복제함

```c
#include <unistd.h>

int dup2(
	int file_des1, // 기존 fd 
	int file_des2  // 새로운 fd
	);
```

**RETURN**

성공시 -1 이외 값

실패시 -1

## 🔴 터미널 관련 함수

### ✅ isatty

인자로 주어진 fd가 터미널에 연결되어 있는지 확인함

```c
#include <unistd.h>

int isatty(int fd); // 확인할 fd
```

**RETURN**

성공시 연결되어 있다면1, 터미널을 참조하고 있지 않다면 0

실패시 errno

### ✅ ttyname

fd에 연결된 터미널 이름을 반환함

```c
#include <unistd.h>

char *ttyname(int fd); // 확인할 fd
```

**RETURN**

성공시 터미널에 연결되어 있다면 해당 터미널 이름, 

실패시 NULL, errno

### ✅ ttyslot

/etc/ttys 파일에 있는 항목 중 호출 프로세스에서 사용중인 터미널의 인덱스를 반환, 

*일반적으로 이 값은 /etc/파일에 있는 현재 사용자에 대한 항목의 인덱스와 동일함

```c
#include <unistd.h>

int ttyslot(void);
```

**RETURN**

성공시 사용중인 터미널 인덱스 반환

실패시 0

### ✅ tcgetattr

현재 터미널의 속성을 받아옴

```c
#include <termios.h>

int tcgetattr(
							int fildes,               // 속성을 받아올 터미널
							struct termios *termios_p // 터미널 속성이 저장될 구조체 포인터
							);

/*
struct termios {
	tcflag_t        c_iflag;        // input flags
	tcflag_t        c_oflag;        // output flags
	tcflag_t        c_cflag;        // control flags
	tcflag_t        c_lflag;        // local flags
	cc_t            c_cc[NCCS];     // control chars
	speed_t         c_ispeed;       // input speed
	speed_t         c_ospeed;       // output speed
};
*/
```

**RETURN**

성공시 0

실패시 -1, errno

### ✅ tcsetarr

fildes에 해당하는 터미널 설정을 변경함

```c
#include <termios.h>

int tcsetattr(
	int fildes,                     // 설정을 변경할 터미널
	int optional_actions,           // 변경될 설정을 적용할 시기
	const struct termios *termios_p // 터미널의 속성을 담은 구조체 포인터
	);
```

- optional_actions
    - TCSANOW : 즉시 적용
    - TCSADRAIN : fildes에 관한 모든 출력이 이루어진 뒤 동작
    - TCSAFLUSH : fildes에 관한 모든 출력및 입력이 이루어진 뒤 동작

**RETURN**

성공시 0

실패시 -1, errno

### ✅ tgetent

단말명 입력을 bp에 추출함

name에 해당하는 터미널 엔트리를 불러오는 루틴

```c
#include <curses.h>
#include <term.h>

int tgetent(
	char *bp,        // 무시되어 보통 NULL 할당함
	const char *name // 단말명
	);
```

**RETURN**

성공시 1, 해당 항목이 없는 경우 0

실패시 -1

### ✅ tgetflag

id가 사용 가능한 지 확인함(불리언)

id가 단말 엔트리에 존재하는 지 확인

```c
#include <curses.h>
#include <term.h>

int tgetflag(char *id); // 확인할 id
```

**RETURN**

존재 시1, 아니면 0

### ✅ tgetnum

id가 사용 가능한 지 확인함(넘버)

```c
#include <curses.h>
#include <term.h>

int tgetnum(char *id); // 확인할 id
```

**RETURN**

존재시 양수, 아니면 -1

### ✅ tgetstr

id가 사용 가능한 지 확인함(스트링)

```c
#include <curses.h>
#include <term.h>

char *tgetstr(
	char *id,   // 확인할 id
	char **area // 확인 내용을 담을 문자열 이중포인터
	);
```

**RETURN**

성공시 문자열로 저장

실패시 NULL

### ✅ tgoto

매개변수로 지정된 기능을 인스턴스화함

반환값은 `tputs` 함수로 전달됨

```c
#include <curses.h>
#include <term.h>

char *tgoto(
	const char *cap, 
	int col, 
	int row
	);
```

**RETURN**

출력할 문자열

### ✅ tputs

패딩 인포메이션을 str에 적용함

`tgetstr`에서 반환된 문자열 출력

```c
#include <curses.h>
#include <term.h>

int tputs(
	const char *str, 
	int affcnt,      // 영향을 받는 행의 번호
	int (*putc)(int) // char가 한번에 하나씩 전달되는 putchar와 동일한 일을 수행
	);
```

**RETURN**

str이 NULL이면 에러를 반환

## 🔴 에러 관련 함수

### ✅ strerror

시스템 오류 번호를 오류 메시지 문자열로 반환함

```c
#include <string.h>

char *strerror(int errnum); // 오류 번호
```

**RETURN**

성공시 오류 번호와 일치하는 오류 메시지문자열

실패시 NULL 또는 "Unknown error nnn”

### ✅ errno

마지막으로 발생한 에러 번호

```c
#include <errno.h>

extern int errno;
```

## 🔴 환경변수 관련 함수

### ✅ getenv

name에 해당하는 환경변수를 찾음

```c
#include <stdlib.h>

char *getenv(const char *name); // 찾고 싶은 환경변수 명
```

**RETURN**

성공시 name에 해당하는 환경변수 값

실패시 NULL

## 🔴 제어 관련 함수

### ✅ ioctl

하드웨어의 제어나 정보를 얻기위해서 사용함

read(), write()와 같은 동작을 하거나, SPI 통신 속도를 조절하는 등의 작업도 가능

```c
#include <sys/ioctl.h>

int ioctl(
	int fildes,            // *open된 fd 값
	unsigned long request, // 전달할 값
	...);    // 보통 디바이스에 전달할 정보의 구조체 포인터로 사용함
```

**RETURN**

성공시 0

실패시 -1, errno

그 외

- `printf,`
- `malloc,`
- `free,`
- `write,`
- `open,`
- `read,`
- `close,`
- `exit,`
