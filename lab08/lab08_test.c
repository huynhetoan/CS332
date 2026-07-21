#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Process started!\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("Check me with: ps -p %d -f\n", getpid());
    printf("Or inspect /proc/%d/\n", getpid());

    while (1) {
        printf("Still running... (PID %d)\n", getpid());
        sleep(1);
    }

    return 0;
}
