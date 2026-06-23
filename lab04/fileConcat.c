/* Ethan Huynh
To compile use: gcc -o fileConcat fileConcat.c
To execute use: ./fileConcat file1 file2
Check results: cat file1
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //open, O_RDONLY, O_WRONLY, O_APPEND flags
#include <unistd.h> //read, write, close
#include <string.h>

//buffer for reading chunks (2^10 = 1024)
#define BUFFSIZE 1024

int main(int argc, char *argv[]) {
    int fd1, fd2;
    int n;
    char buffer[BUFFSIZE];

    //check argument, it must be 3 (fileConcat.c, file1, file2)
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        exit(1); //stop program if not 3 arguments
    }

    //check filename
    //strcmp checks if the strings are the same
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Error: The two filenames must be different.\n");
        exit(1); //stop program if files are the same name
    }

    //open first file in append to add instead of overwriting
    fd1 = open(argv[1], O_WRONLY | O_APPEND);
    if (fd1 < 0) {
        printf("Error opening first file.\n");
        exit(1); //stop program if unable to open file
    }

    //open second file in read only
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        printf("Error opening second file.\n");
        close(fd1);
        exit(1);
    }

    //read file2 and append to file1
    while ((n = read(fd2, buffer, BUFFSIZE)) > 0) {
        if (write(fd1, buffer, n) != n) {
            printf("Write error.\n");
            close(fd1);
            close(fd2);
            exit(1);
        }
    }

    //if -1 is returned, there is an error
    if (n < 0) {
        printf("Read error.\n");
    }

    //close files
    close(fd1);
    close(fd2);

    return 0;
}