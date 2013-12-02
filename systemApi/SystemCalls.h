#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define LOG_FILE_NAME "log.txt"
#define READ R_OK
#define WRITE W_OK
#define EXECUTE X_OK

#define PARENT_DIR_NAME "< Parent Directory"

int i;

char * getWorkingDirectory();

void changeDirectoryTo(char * directory);

void listDirectoryContents(char * directory);

struct dirent * *  getDirectoryContents(char * directory, int * dirItemCount);

void getDirectoryContentNames(char * directory, int * dirItemCount, char * * * dirContentNames);

void logToFile(char * stringToLog);

void logToFileAt(char * stringToLog, char * logFilePath);

void logToFileAtRoot(char * stringToLog);

int canRead(char * filePath);

int canWriteTo(char * filePath);

int canExecute(char * filePath);

int canAccessTo(char * filePath, int accessType);

#endif
