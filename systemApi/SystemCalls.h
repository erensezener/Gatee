#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdio.h>
#include <stdlib.h>
// #include </usr/include/sys/syscall.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

char * getWorkingDirectory();

void changeDirectoryTo(char *);

void listDirectoryContents(char *);

void getDirectoryContents(char *, char * []);

#endif
