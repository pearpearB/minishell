/*
	char *prompt 를 터미널에 띄워주고 터미널에서 입력된 문자열을 리턴함

	SYNOPSIS
	#include <readline/readline.h>
	#include <readline/history.h>

	char *readline (const char *prompt);

	RETURN
	성공시 개행이 제거된 읽어들인 문자열, eof의 경우 NULL
	실패시 errno
*/

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

int main()
{
    char *str;

    while (1)
    {
        str = readline("jabae's prompt : ");

        if (str)
            printf("%s\n", str);
        else
            break ;

        add_history(str); 
				/* 방향키로 이전 명령어들을 가져올 수 있음 */
        free(str);
    }
    return(0);
}

/*
실행방법
gcc readline.c -lreadline
a.out
*/