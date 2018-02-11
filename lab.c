#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
int main()
{
	pid_t pid =1074;
	char *a="hello world";
	long int sys = syscall(315,pid,a);
	printf("%d\n",errno);
	printf("System call returned this %ld\n",sys);
	
	return 0;
}
