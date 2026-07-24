/* 
Name: Ethan Huynh
BlazerID: ethuynh
Assignment: Homework 3

To compile: "make" or
             gcc -Wall -o fileProcessManager fileProcessManager.c

To execute:
            ./fileProcessManager <directory>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // fork
#include <sys/types.h> // DIR, pid_t
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>

// check if filename ends with ".txt"
int is_txt_file(const char *name) {
    const char *dot = strrchr(name, '.'); // find last '.'
    if (!dot) return 0;                   // no extension
    return strcmp(dot, ".txt") == 0;
}

// count words in a file (words separated by spaces)
// tabs/newlines = separators
int count_words_in_file(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("fopen");
        return -1; // error
    }

    int c;
    int in_word = 0;
    int word_count = 0;

    // read file one character at a time
    while ((c = fgetc(fp)) != EOF) {
        // check if c is a separator (space, tab, newline)
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            // leaving a word
            in_word = 0;
        } else {
            // inside a word
            if (!in_word) {
                word_count++;
                in_word = 1;
            }
        }
    }

    fclose(fp);
    return word_count;
}

// child process: handle one file
void handle_file(const char *dirpath, const char *filename) {
    // build full path: dirpath + "/" + filename
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, filename);

    struct stat info;
    if (stat(fullpath, &info) == -1) {
        perror("stat");
        exit(1);
    }

    // file size in bytes
    long size = (long)info.st_size;

    // base output: file name and size
    printf("File: %s | Size: %ld bytes", filename, size);

    // only count words for .txt files
    if (is_txt_file(filename)) {
        int words = count_words_in_file(fullpath);
        if (words >= 0) {
            printf(" | Words: %d", words);
        } else {
            printf(" | Words: ERROR (could not read file)");
        }
    }

    printf("\n");

    exit(0); // child exits after handling one file
}

// main
int main(int argc, char *argv[]) {

    // check command-line arguments
    if (argc != 2) {
        printf("Usage: ./hw3 <directory_name>\n");
        exit(1);
    }

    const char *dirpath = argv[1];

    // open directory
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir");
        printf("Error: Directory not found.\n");
        exit(1);
    }

    struct dirent *entry;

    // traverse directory entries
    while ((entry = readdir(dir)) != NULL) {

        // skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // build full path to check type
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);

        struct stat info;
        if (stat(fullpath, &info) == -1) {
            perror("stat");
            continue; // skip this entry
        }

        // skip subdirectories, only handle regular files
        if (S_ISDIR(info.st_mode)) {
            continue;
        }

        if (!S_ISREG(info.st_mode)) {
            // not a regular file
            continue;
        }

        // create child process for this file
        pid_t pid = fork();

        if (pid < 0) {
            // fork failed
            perror("fork");
            closedir(dir);
            exit(1);
        } else if (pid == 0) {
            // child process
            handle_file(dirpath, entry->d_name);
            // handle_file() calls exit(), no return here
        } else {
            // parent process: continue to next file
            // wait for all children after the loop
        }
    }

    closedir(dir);

    // parent waits for all child processes
    int status;
    pid_t wpid;

    // wait() returns -1 when there are no more children
    while ((wpid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            // child exited normally
        } else {
            // child did not terminate normally
        }
    }

    return 0;
}
