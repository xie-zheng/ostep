#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	        char *myargs[3];
	        myargs[0] = strdup("ls");   // program: "wc" (word count)
        	myargs[1] = strdup(".");    // argument: file to count
	        myargs[2] = NULL;           // marks end of array
        	// execvp(myargs[0], myargs);  // runs word count
		execl("/bin/ls", ".");
    	} else {
		printf("I am parent (pid:%d)\n", (int) getpid());
	}
}
