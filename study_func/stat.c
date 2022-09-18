/*
	man 2 stat
	디렉토리 또는 파일의 정보(크기, 권한, 생성일시, 최종 변경일 등)를 얻음(== ls -al)

	SYNOPSIS
	#include <sys/stat.h>

	int stat(
					const char *restrict path, // 파일명 또는 파일의 상대결로나 절대경로
					struct stat *restrict buf  // 파일의 정보가 저장됨
					);

	RETURN
	성공시 0
	실패시 -1
*/

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(void)
{
	struct stat	info;

	stat("/Users/baejaeyeong/42_ing/", &info); // 디렉토리, 파일, 상대 경로도 가능하다.

	printf("ID : %d\n", info.st_dev);
	printf("inode : %llu\n", info.st_ino);
	printf("mode : %d\n", info.st_mode);
	printf("hard link : %d\n", info.st_nlink);
	printf("user ID : %d\n", info.st_uid);
	printf("group ID : %d\n", info.st_gid);
	printf("device ID : %d\n", info.st_rdev);
	printf("size : %lld bytes\n", info.st_size);
	printf("block size : %d\n", info.st_blksize);
	printf("alloc blocks : %lld\n", info.st_blocks);
	printf("time of last access : %s", ctime(&info.st_atime));
	printf("time of last modification : %s", ctime(&info.st_mtime));
	printf("time of last status change : %s", ctime(&info.st_ctime));

	return (0);
}

/*
struct stat {
    dev_t     st_dev;     // ID of device containing file
    ino_t     st_ino;     // inode number
    mode_t    st_mode;    // 파일의 종류 및 접근권한 ***여기가 젤루 종요하다고 한다
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