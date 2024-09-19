/*
========================================================================================================
Name : 19
Author : Prajyot Shende
Description : Create a FIFO file by
	a. mknod command
	b. mkfifo command
	c. use strace command to find out, which command (mknod or mkfifo) is better.
	c. mknod system call
	d. mkfifo library function
Date: 18 Sept, 2024.
========================================================================================================
*/


#include <stdio.h>
#include <sys/stat.h>

int main()
{


	int a =  mknod( "FIFO1", 0666, 0 ); 
	if(a==0)
	{
		printf("Used mknod to create fifo\n");
        }


	int b = mkfifo("FIFO2",0666); 
	if(b==0)
	{
		printf("Library function Makefifo used to create fifo\n");
	}


	return 0;
}

/*
========================================================================================================

./a.out
  Makenode used to create fifo
Library function Makefifo used to create fifo


strace ./19
execve("./19", ["./19"], 0x7ffced1f0f20  44 vars ) = 0
brk(NULL)                               = 0x55ae52e04000
arch_prctl(0x3001  ARCH_??? , 0x7ffee1d8eae0) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd33d22c000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=64227, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 64227, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fd33d21c000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P<\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2072888, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2117488, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fd33d000000
mmap(0x7fd33d022000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7fd33d022000
mmap(0x7fd33d19a000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7fd33d19a000
mmap(0x7fd33d1f2000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f1000) = 0x7fd33d1f2000
mmap(0x7fd33d1f8000, 53104, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fd33d1f8000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd33d219000
arch_prctl(ARCH_SET_FS, 0x7fd33d219740) = 0
set_tid_address(0x7fd33d219a10)         = 16615
set_robust_list(0x7fd33d219a20, 24)     = 0
rseq(0x7fd33d21a060, 0x20, 0, 0x53053053) = 0
mprotect(0x7fd33d1f2000, 16384, PROT_READ) = 0
mprotect(0x55ae50fb0000, 4096, PROT_READ) = 0
mprotect(0x7fd33d261000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7fd33d21c000, 64227)           = 0
mknodat(AT_FDCWD, "FIFO1", S_IFIFO|0666) = -1 EEXIST (File exists)
mknodat(AT_FDCWD, "FIFO2", S_IFIFO|0666) = -1 EEXIST (File exists)
exit_group(0)                           = ?
+++ exited with 0 +++

 

========================================================================================================
*/
