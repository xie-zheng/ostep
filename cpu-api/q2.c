#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int fd = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    assert(fd >= 0);
    
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: redirect standard output to a file
        char buffer[20];
        sprintf(buffer, "hello world child\n");
        int rc = write(fd, buffer, strlen(buffer));
        assert(rc == (strlen(buffer)));
	fsync(fd);
        close(fd);

    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        assert(wc >= 0);

        char buffer[20];
        sprintf(buffer, "hello world parent\n");
        int rc = write(fd, buffer, strlen(buffer));
        assert(rc == (strlen(buffer)));
        fsync(fd);
        close(fd);
    }
    return 0;
}
