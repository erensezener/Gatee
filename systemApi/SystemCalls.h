#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

char * getWorkingDirectory();

void changeDirectoryTo(char * directory);

void listDirectoryContents(char * directory);

struct dirent * *  getDirectoryContents(char * directory, int * dirItemCount);

void getDirectoryContentNames(char * directory, int * dirItemCount, char * * * dirContentNames);

#endif
