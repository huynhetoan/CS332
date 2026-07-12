/* 
Name: Ethan Huynh
BlazerID: ethuynh
Assignment: Homework_02

To compile: "make" or
             gcc -Wall -o search search.c

To execute: "make run" or
            ./search [options] [directory]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // getopt(), readlink()
#include <dirent.h> // opendir(), readdir()
#include <sys/stat.h> // lstat(), file info
#include <sys/types.h> // mode_t, ssize_t
#include <time.h> // access time formatting

// Global option flags
int opt_S = 0; // -S
int opt_s = -1; // -s <size>
char *opt_f_pattern = NULL; // -f <pattern>
int opt_f_depth = -1; // -f <depth>

// Function pointer type
// removes the need of switch statements in traverse()
// allows main() to choose the correct print function
typedef void (*ACTION_FUNC)(const char *path, const struct stat *info, int depth);

// Declarations
void print_symlink(const char *path, const struct stat *info, int depth);
void print_info(const char *path, const struct stat *info, int depth);

// display name
void display_name(const char *path, const struct stat *info, int depth) {
    const char *name = strrchr(path, '/'); // finds the last '/' in the path
    if (name) name++; else name = path;

    printf("%*s%s\n", depth * 4, "", name); // indent by 4 spaces
}

// Function pointer for traverse() to print files
// Avoids option specific checks
ACTION_FUNC action = display_name;

// Filter checking function
int passes_filters(const char *path, const struct stat *info, int depth) {

    // -s <size> filter
    if (opt_s != -1) {
        if (!S_ISDIR(info->st_mode)) { // directories always pass
            if (info->st_size > opt_s) {
                return 0;
            }
        }
    }

    // -f <pattern> <depth> filter
    if (opt_f_pattern != NULL) {
        const char *filename = strrchr(path, '/');
        if (filename) filename++; else filename = path;

        if (strstr(filename, opt_f_pattern) == NULL) {
            return 0; // substring not found
        }

        if (depth > opt_f_depth) {
            return 0; // too deep
        }
    }

    return 1; // passed all filters
}

// Print symbolic link
void print_symlink(const char *path, const struct stat *info, int depth) {
    char target[1024];
    ssize_t len = readlink(path, target, sizeof(target) - 1);
    // readlink() does not null-terminate
    // '\0' is added manually
    const char *name = strrchr(path, '/');
    if (name) name++; else name = path;

    if (len != -1) {
        target[len] = '\0';
        printf("%*s%s -> %s\n", depth * 4, "", name, target);
    } else {
        printf("%*s%s (broken link)\n", depth * 4, "", name);
    }
}

// -S printing (size, perms, access time)
void print_info(const char *path, const struct stat *info, int depth) {
    const char *name = strrchr(path, '/');
    if (name) name++; else name = path;

    //permissions
    char perms[11];
    // snprintf() avoids buffer overflow, safer than sprintf()
    snprintf(perms, sizeof(perms), "%c%c%c%c%c%c%c%c%c",
        (info->st_mode & S_IRUSR) ? 'r' : '-',
        (info->st_mode & S_IWUSR) ? 'w' : '-',
        (info->st_mode & S_IXUSR) ? 'x' : '-',
        (info->st_mode & S_IRGRP) ? 'r' : '-',
        (info->st_mode & S_IWGRP) ? 'w' : '-',
        (info->st_mode & S_IXGRP) ? 'x' : '-',
        (info->st_mode & S_IROTH) ? 'r' : '-',
        (info->st_mode & S_IWOTH) ? 'w' : '-',
        (info->st_mode & S_IXOTH) ? 'x' : '-'
    );

    // last access time
    char timebuf[64];
    struct tm *tm = localtime(&info->st_atime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm);

    // directories have size 0
    long size = S_ISDIR(info->st_mode) ? 0 : info->st_size;

    printf("%*s%s (size=%ld, perms=%s, access=%s)\n",
           depth * 4, "", name, size, perms, timebuf);
}

// Recursive directory traversal
void traverse(const char *path, int depth) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        // skips . and ..
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // build full path
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // get file info
        struct stat info;
        if (lstat(fullpath, &info) == -1) {
            perror(fullpath);
            continue;
        }

        // handle symbolic links first
        if (S_ISLNK(info.st_mode)) {
            print_symlink(fullpath, &info, depth);
            continue;
        }

        // print directory name BEFORE contents
        if (S_ISDIR(info.st_mode)) {
            printf("%*s%s\n", depth * 4, "", entry->d_name);
        }

        // apply filters
        if (!passes_filters(fullpath, &info, depth)) {
            continue;
        }

        // print file info
        if (!S_ISDIR(info.st_mode)) {
            action(fullpath, &info, depth);
        }

        // recurse into directories
        if (S_ISDIR(info.st_mode)) {
            traverse(fullpath, depth + 1);
        }
    }

    closedir(dir);
}

// main function (option parsing and traversal)
int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "Ss:f:")) != -1) {
        switch (opt) {
            case 'S':
                opt_S = 1;
                break;
            case 's':
                opt_s = atoi(optarg);
                break;
            case 'f':
                opt_f_pattern = optarg;
                if (optind < argc) {
                    opt_f_depth = atoi(argv[optind]);
                    optind++;
                } else {
                    fprintf(stderr, "Error: -f requires <pattern> <depth>\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "Usage: ./search [-S] [-s bytes] [-f pattern depth] [directory]\n");
                exit(1);
        }
    }

    // assign action function
    if (opt_S)
        action = print_info;
    else
        action = display_name;

    // determine starting directory
    const char *start_dir = (optind < argc) ? argv[optind] : ".";

    // begin traversal
    traverse(start_dir, 0);

    return 0;
}
