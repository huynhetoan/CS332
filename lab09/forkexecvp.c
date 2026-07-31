/* 
Name: Ethan Huynh
BlazerID: ethuynh
Assignment: Lab 9

To compile: gcc -Wall -o forkexecvp forkexecvp.c

To execute: ./forkexecvp <command> [args]
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid = -1; // global so signal handlers can access it

// Ctrl-C will interrupt child
static void handle_sigint(int signo) {
    if (child_pid > 0) {
        kill(child_pid, SIGINT);
        write(STDOUT_FILENO, "Parent sent SIGINT to child\n", 29);
    }
}

// Ctrl-Z will suspend child
static void handle_sigtstp(int signo) {
    if (child_pid > 0) {
        kill(child_pid, SIGTSTP);
        write(STDOUT_FILENO, "Parent sent SIGTSTP to child\n", 29);
    }
}

// Ctrl-\ will quit parent (and child)
static void handle_sigquit(int signo) {
    if (child_pid > 0) {

        // catch SIGQUIT in the parent, but send SIGTERM to the child
        // SIGQUIT forces a core dump
        // SIGTERM cleanly shuts child down before parent exits
        kill(child_pid, SIGTERM);
        write(STDOUT_FILENO, "Parent quitting, sent SIGTERM to child\n", 40);
    }
    _exit(0); // exit from handler
}

int main(int argc, char **argv) {
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    // install parent signal handlers 
    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);
    signal(SIGQUIT, handle_sigquit);

    child_pid = fork();

    if (child_pid == 0) { 
        // child process 
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(-1);

    } else if (child_pid > 0) { 
        // parent process 
        printf("Parent: waiting for child...\n");

        while (1) {
            pid_t w = waitpid(child_pid, &status, WUNTRACED);

            if (w == -1) {
                perror("waitpid");
                break;
            }

            if (WIFEXITED(status)) {
                printf("Parent: child exited with status %d\n",
                       WEXITSTATUS(status));
                break;
            }

            if (WIFSIGNALED(status)) {
                printf("Parent: child terminated by signal %d\n",
                       WTERMSIG(status));
                break;
            }

            if (WIFSTOPPED(status)) {
                printf("Parent: child stopped by signal %d\n",
                       WSTOPSIG(status));
                // parent keeps waiting 
            }
        }

    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    printf("[%ld]: Exiting program...\n", (long)getpid());
    return 0;
}