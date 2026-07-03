/* Ethan Huynh
To compile use: gcc -Wall -o dirTraverse dirTraverse.c
To execute use: ./dirTraverse <directory>
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // opendir, readdir, closedir
#include <sys/stat.h> // lstat, struct stat
#include <string.h> // strcmp
#include <unistd.h> // lstat

// recursively takes a directory name and prints everything inside it
void traverse(const char *dirname) {
    DIR *dir; //pointer
    struct dirent *entry; //struct
    struct stat info;
    char path[1024]; //buffer

    // try to open the directory
    dir = opendir(dirname);
    if (dir == NULL) {
        printf("Error opening directory: %s\n", dirname);
        return;
    }

    printf("\nDirectory: %s\n", dirname);

    // read each entry inside the directory
    while ((entry = readdir(dir)) != NULL) {

        // skip . and .. to avoid infinite recursion
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // full path (dirname/filename)
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        // lstat for file information
        if (lstat(path, &info) < 0) {
            printf("lstat error on %s\n", path);
            continue;
        }

        // print name
        printf("  %s", entry->d_name);

        // determine file type using macros
        if (S_ISREG(info.st_mode)) {
            printf(" (regular file)\n");
        } else if (S_ISDIR(info.st_mode)) {
            printf(" (directory)\n");

            // recursively traverse subdirectory
            traverse(path);
        } else if (S_ISLNK(info.st_mode)) {
            printf(" (symbolic link)\n");
        } else if (S_ISCHR(info.st_mode)) {
            printf(" (character device)\n");
        } else if (S_ISBLK(info.st_mode)) {
            printf(" (block device)\n");
        } else if (S_ISFIFO(info.st_mode)) {
            printf(" (FIFO)\n");
        } else if (S_ISSOCK(info.st_mode)) {
            printf(" (socket)\n");
        } else {
            printf(" (unknown)\n");
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {

    // provide a directory name
    if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    // start recursive traversal
    traverse(argv[1]);

    return 0;
}
