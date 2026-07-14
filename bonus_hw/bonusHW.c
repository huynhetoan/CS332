/* 
Name: Ethan Huynh
BlazerID: ethuynh
Assignment: Bonus Homework

To compile: "make" or
             gcc -Wall -o bonusHW bonusHW.c

To execute: "make run" or
            ./bonusHW input.txt > average.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // fork, pipe, read, write, close
#include <sys/types.h> // pid_t
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

// Constants
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 20
#define NUM_PER_PRODUCER 500 // generates 500 numbers
#define NUM_PER_CONSUMER 250 // reads 250 numbers
#define RAND_MAX_VALUE 1000 // only numbers from 0 to 1000

// Total numbers: 10 * 500 = 5000
// Consumers: 20 * 250 = 5000

// pipefd[0] = read end
// pipefd[1] = write end

// main
int main(int argc, char *argv[]) {
    // make pipe
    return 0;
}
