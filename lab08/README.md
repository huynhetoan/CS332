# Lab 08 – Process Control & /proc Testing Program  
**Name:** Ethan Huynh  

## Overview  
Lab 08 teaches how Linux handles processes, job control, monitoring tools, and the `/proc` filesystem.  
This README explains how to compile, run, and test a small program that demonstrates **all Lab 08 concepts**.

---

# 1. Test Program (lab08_test.c)

This program prints its PID every second so you can test:

- foreground processes  
- background processes  
- suspended jobs  
- resuming jobs  
- killing processes  
- inspecting `/proc/<PID>`  
- monitoring with `ps`, `pstree`, and `top`  

### Source Code
```c
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
```

---

## 2. How to Compile

Use `gcc`:

```bash
gcc -Wall -o lab08_test lab08_test.c
```

This creates the executable:

```
lab08_test
```

---

## 3. How to Run

Run in the foreground:

```bash
./lab08_test
```

You will see output every second.

---

## 4. Features You Can Test

### A. Foreground Process

Run normally:

```bash
./lab08_test
```

The program prints continuously.

---

### B. Suspend the Process (Ctrl‑Z)

While running, press:

```
Ctrl-Z
```

Check jobs:

```bash
jobs
```

Expected:

```
[1]+  Stopped  lab08_test
```

---

### C. Resume in Background

```bash
bg %1
```

Check again:

```bash
jobs
```

Expected:

```
Running lab08_test &
```

---

### D. Bring Back to Foreground

```bash
fg %1
```

---

### E. Kill the Process

Kill foreground:

```
Ctrl-C
```

Kill background:

```bash
kill %1
```

Kill by PID:

```bash
kill <PID>
kill -9 <PID>
```

---

## 5. Monitoring the Process

### View process info

```bash
ps -p <PID> -f
ps -p <PID> -F
```

### View process tree

```bash
pstree -np | more
```

### View all processes

```bash
ps -e | more
ps -ef | more
ps -eF | more
ps -ely | more
```

### Count processes

```bash
ps -e | wc -l
```

### Real-time monitoring

```bash
top
top -u <your_username>
```

---

## 6. Explore /proc/<PID>

### List its files

```bash
ls /proc/<PID>
```

### Command line used to start it

```bash
cat /proc/<PID>/cmdline
```

### Environment variables

```bash
strings /proc/<PID>/environ
```

### Process statistics

```bash
cat /proc/<PID>/stat
```
---