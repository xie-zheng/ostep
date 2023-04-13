#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int
main(int argc, char* argv[])
{
	int rc = fork();
	if (rc < 0) {
        	// fork failed; exit
        	fprintf(stderr, "fork failed\n");
        	exit(1);
    	} else if (rc == 0) {
        	// child (new process)
        	printf("hello, I am child (pid:%d)\n", (int) getpid());
    	} else {
		// 这个sleep基本能保证parent在child之后执行
		Spin(1);
		printf("world, I am parent (pid:%d)\n", (int) getpid());
	}
}
