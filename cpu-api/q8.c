#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child 1 */
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        exit(EXIT_FAILURE);
    } else {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            /* Child 2 */
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            execlp("wc", "wc", NULL);
            exit(EXIT_FAILURE);
        } else {
            /* Parent */
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
