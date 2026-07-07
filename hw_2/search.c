/* 
Name: Ethan Huynh
BlazerID: ethuynh
Assignment: Homework_02

To compile: "make" or
             gcc -Wall -o search search.c

To execute: "make run" or
            ./search
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int opt_S = 0;
int opt_s = -1;
char *opt_f_pattern = NULL;
int opt_f_depth = -1;

void traverse(const char *path, int depth) {
    // empty for now
}

int main(int argc, char *argv[]) {

    // empty getopt loop for now

    // determine starting directory

    // call traverse()

    return 0;
}
