#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) { // child process
        int grandchild_pid = fork();
        if (grandchild_pid < 0) {
            printf("Fork failed\n");
            return 1;
        }
        else if (grandchild_pid == 0) { // grandchild process
            printf("I am the grandchild (%d)\n", getpid());
        }
        else { // child process
            wait(&status); // wait for the grandchild process to finish
            printf("I am the child (%d)\n", getpid());
        }
    }
    else { // parent process
        wait(&status); // wait for the child process to finish
        printf("I am the parent (%d)\n", getpid());
    }

    return 0;
}