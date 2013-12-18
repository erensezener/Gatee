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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define LOG_FILE_NAME ".gatee_log"
#define CD_FILE_NAME ".gatee_cd"
#define READ R_OK
#define WRITE W_OK
#define EXECUTE X_OK

#define PARENT_DIR_NAME "< Parent Directory"
/* Possible prefixes: "< ", "> ", "  " */
#define PREFIX_SIZE 2
#define DIR_ID 0
#define DIR_PREFIX "> "
#define FILE_ID 1
#define FILE_PREFIX "  "

int i;

/*
 * Usage:
 *
 * char *currentWorkingDirectory = getWorkingDirectory();
 *
 * printf("%s\n", currentWorkingDirectory);
 */
char * getWorkingDirectory();

/*
 * Usage:
 *
 * changeDirectoryTo("/Users/--something--/Documents");
 */
void changeDirectoryTo(char * directory);

/*
 * Usage:
 *
 * int dirItemCount;
 * struct dirent * * directoryContents = getDirectoryContents(getWorkingDirectory(), &dirItemCount);
 *
 * for (int i = 0; i < dirItemCount; ++i) {
 *     printf("%s\n", directoryContents[i]->d_name);
 * }
 */
struct dirent * *  getDirectoryContents(char * directory, int * dirItemCount);

/*
 * Usage:
 *
 * int dirItemCount;
 * char * * dirContents;
 * getDirectoryContentNames(currentWorkingDirectory, &dirItemCount, &dirContents);
 *
 * for (int i = 0; i < dirItemCount; ++i) {
 *     printf("%s\n", dirContents[i]);
 * }
 *
 * Disclaimer 1: Omitting the current directory pointer and renaming the parent
 * directory pointer to PARENT_DIR_NAME defined in SystemCalls.h.
 *
 * Disclaimer 2: If a directory content entry is a directory, it will have a
 * DIR_PREFIX appended to the front of it's name. If it is a file, it will
 * have a FILE_PREFIX appended to the front of it's name.
 */
void getDirectoryContentNames(char * directory, int * dirItemCount, char * * * dirContentNames);

/*
 * Usage:
 *
 * fileOrDir(--some filename-- == DIR_ID) {
 *     > it's a directory
 * }
 */
int fileOrDir(char * name);

/*
 * Usage:
 *
 * logToFile(--some string--);
 *
 * Creates the log at the current working directory.
 * More info: http://www.cprogramming.com/tutorial/cfileio.html
 */
void logToFile(char * stringToLog);

/*
 * Usage:
 *
 * logToFileAt(--some string--, "/bin/logs");
 */
void logToFileAt(char * stringToLog, char * logFilePath);

/*
 * Usage:
 *
 * logToFileAtRoot(--some string--);
 */
void logToFileAtRoot(char * stringToLog);

/*
 * Usage:
 *
 * canRead("/bin/logs") == 0;
 * canRead("/bin/logs/log.txt") == 0;
 */
int canRead(char * filePath);

/*
 * Usage:
 *
 * canWriteTo("/") == 0;
 * canWriteTo("/log.txt") == 0;
 */
int canWriteTo(char * filePath);

/*
 * Usage:
 *
 * canExecute("/bin/gatee");
 */
int canExecute(char * filePath);

/*
 * Usage:
 *
 * canAccessTo("/bin/logs/log.txt", READ);
 * canAccessTo("/bin/logs/log.txt", WRITE);
 * canAccessTo("/bin/gatee", EXECUTE);
 */
int canAccessTo(char * filePath, int accessType);

/*
 * Usage:
 *
 * getNumTerminalRows();
 */

int getNumTerminalRows();

/*
 * Usage:
 *
 * getNumTerminalColumns();
 */

int getNumTerminalColumns();

/*
 * Usage:
 *
 * prepareToExit("/");
 */
void prepareToExit(char * dirToExit);

#endif
