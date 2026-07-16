/*
Name: Ethan Huynh
BlazerID: ethuynh
Lab07 - runCommands.c

To compile: gcc -Wall -O -o runCommands runCommands.c
To run: ./runCommands inputfile.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // fork, execvp
#include <sys/types.h> // pid_t
#include <sys/wait.h> // WIFEXITED
#include <time.h>

//helper functions
//trim \n from fgets()
void trimNewline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

//splits a command line into argv[] for execvp()
char **parseCommand(char *line, int *argc_out) {
    // strtok() splits by spaces

    char **argv = malloc(32 * sizeof(char *));
    int count = 0;

    char *token = strtok(line, " ");
    while (token != NULL) {
        argv[count++] = token;
        token = strtok(NULL, " ");
    }

    argv[count] = NULL; // execvp requires NULL termination
    *argc_out = count;
    return argv;
}

// main function
int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./runCommands <inputfile>\n");
        exit(1);
    }

    // open input file
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("fopen");
        exit(1);
    }

    // open log file
    FILE *log = fopen("output.log", "w");
    if (!log) {
        perror("fopen");
        exit(1);
    }

    char line[256];

    // Read each line from input file
    while (fgets(line, sizeof(line), in) != NULL) {

        trimNewline(line); // remove newline from fgets()

        if (strlen(line) == 0)
            continue; // skip empty lines

        // make a copy because strtok modifies the string
        char lineCopy[256];
        strcpy(lineCopy, line);

        int argc_parsed = 0;
        char **cmd = parseCommand(lineCopy, &argc_parsed);

        //record start time before fork()
        time_t start = time(NULL);

        // fork a child process
        pid_t pid = fork();

        if (pid == 0) {
            // child process
            execvp(cmd[0], cmd); // run the command
            perror("execvp");    // only runs if exec fails
            exit(-1);
        }
        else if (pid > 0) {
            // parent process
            int status;
            wait(&status); // wait for child to finish

            // capture end time
            time_t end = time(NULL);

            // write to log file
            fprintf(log, "%s\t%s\t%s\n",
                    line,
                    ctime(&start),
                    ctime(&end));
        }
        else {
            perror("fork"); //fork failed
            exit(1);
        }

        //free allocated memory
        free(cmd);
    }

    //close files
    fclose(in);
    fclose(log);

    return 0;
}
