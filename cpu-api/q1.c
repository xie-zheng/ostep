#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char* argv[]) {
    int var = 100;
    printf("parent thread (pid:%d) (var=%d)\n", (int) getpid(), var);

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
	var = 0; // 这个var与原来父进程的var没有关系了
        printf("hello, I am child (pid:%d) (var=%d)\n", (int) getpid(), var);
    } else {
        // parent goes down this path (original process)
	var = 1;
        printf("hello, I am parent of %d (pid:%d) (var=%d)\n",
	       rc, (int) getpid(), var);
	Spin(3);
	printf("parent sleep 3s (var=%d)\n", var);
    }
}
