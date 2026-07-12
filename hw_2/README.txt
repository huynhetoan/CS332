Ethan Huynh (BlazerID: ethuynh)
CS 332 – Homework 02

Compile:
    make
or
    gcc -Wall -o search search.c

Run:
    make run
or
    ./search [options] [directory]

Description:
    No arguments lists all files and subdirectories
    starting from current directory.

        ./search projects
    recursively list everything inside the 'projects' folder.

Options:
    -S              Print size, permissions, and last access time.
    -s <bytes>      List files smaller than the given size. (Directories always print)
    -f <pattern> <depth>
                    Only list files whose names contain <pattern>,
                    and only up to the given depth.