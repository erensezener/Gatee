#include "SystemCalls.h"

char * getWorkingDirectory() {
    return getcwd(NULL, 0);
}

void changeDirectoryTo(char * directoryPath) {
    int status = chdir(directoryPath);
    if(status == 0) {
        // Successfully changed the directory
    } else if(errno == EACCES) {
        // Permission denied
        printf("Permission denied to explore directory \"%s\".\n", directoryPath);
    } else if(errno == ENOENT) {
        // Directory does not exist
        printf("Directory \"%s\" does not exist.\n", directoryPath);
    } else if(errno == ENOTDIR) {
        // Referenced item exists but is not a directory
        printf("\"%s\" is not a directory.\n", directoryPath);
    } else if(errno == ELOOP) {
        // Too many symbolic links were resolved while trying to look up the file name
        printf("Symbolic link loop detected when exploring \"%s\".\n", directoryPath);
    } else {
        // Another error.
        printf("Error ocurred when trying to change directory!\n");
    }
}

/*
 * NO USAGE.
 */

int one (const struct dirent *unused) {
    return 1;
}

struct dirent * * getDirectoryContents(char * directory, int * dirItemCount) {
    struct dirent * * directoryContents;
    *dirItemCount = scandir (directory, &directoryContents, one, alphasort);
    printf("%d\n", *dirItemCount);

    if (*dirItemCount >= 0) {
        return directoryContents;
    } else {
        perror("Couldn't open the directory");
        return NULL;
    }
}

void getDirectoryContentNames(char * directory, int * dirItemCount, char * * * dirContentNames) {
    struct dirent * * directoryContents;
    *dirItemCount = scandir (directory, &directoryContents, one, alphasort);

    if (*dirItemCount >= 0) {
        *dirContentNames = malloc(((int)dirItemCount - 1) * sizeof(char * *));
		for (i = 0; i < *dirItemCount; ++i) {
            if(strcmp(directoryContents[i]->d_name, ".") == 0) {
                /* Don't include the current directory pointer */
            } else if(strcmp(directoryContents[i]->d_name, "..") == 0) {
                (*dirContentNames)[i - 1] = malloc(strlen(PARENT_DIR_NAME) * sizeof(char *));
                strcpy((*dirContentNames)[i - 1], PARENT_DIR_NAME);
            } else {
                (*dirContentNames)[i - 1] = malloc((strlen(directoryContents[i]->d_name) + PREFIX_SIZE) * sizeof(char *));
                if(fileOrDir(directoryContents[i]->d_name) == DIR_ID) {
                    strcpy((*dirContentNames)[i - 1], DIR_PREFIX);
                    strcat((*dirContentNames)[i - 1], directoryContents[i]->d_name);
                } else {
                    strcpy((*dirContentNames)[i - 1], FILE_PREFIX);
                    strcat((*dirContentNames)[i - 1], directoryContents[i]->d_name);
                }
            }
        }
        *dirItemCount = *dirItemCount - 1; /* To remove the current directory pointer count */
    } else {
        perror("Couldn't open the directory");
    }
}

int fileOrDir(char * name) {
    struct stat status;
    lstat(name, &status);
    if(S_ISDIR(status.st_mode)) {
        // It's a directory
        return 0;
    } else {
        // It's a file
        return 1;
    }
}

void logToFile(char * stringToLog) {
    FILE *file = fopen(LOG_FILE_NAME, "a+");

    time_t rawTime;
    time(&rawTime);
    struct tm * currTime = localtime(&rawTime);

    if (file == NULL) {
        printf("Error opening file, unable to log!\n");
    } else {
        fprintf(file, "%d/%d/%d %d:%d:%d - %s\n", currTime->tm_mday, (currTime->tm_mon + 1), (currTime->tm_year + 1900), currTime->tm_hour, currTime->tm_min, currTime->tm_sec, stringToLog);
        fclose(file);
    }
}

void logToFileAt(char * stringToLog, char * logFilePath) {
    char * currentDir = getWorkingDirectory();
    changeDirectoryTo(logFilePath);
    logToFile(stringToLog);
    changeDirectoryTo(currentDir);
}

void logToFileAtRoot(char * stringToLog) {
    if(canWriteTo("/") == 0) {
        logToFileAt(stringToLog, "/");
    } else {
        printf("Error when logging to file at the root folder (no write permissions for \"/\").\n");
        printf("To write to the root folder, try running Gatee as sudo (sudo gatee).\n");
    }
}

int canRead(char * filePath) {
    return canAccessTo(filePath, READ);
}

int canWriteTo(char * filePath) {
    return canAccessTo(filePath, WRITE);
}

int canExecute(char * filePath) {
    return canAccessTo(filePath, EXECUTE);
}

int canAccessTo(char * filePath, int accessType) {
    int status = access(filePath, accessType);
    if(status == 0) {
        // Successfully changed the directory
        return 0;
    } else if(errno == EACCES) {
        // Permission denied
        char * doWhat;
        if(accessType == READ) {
            doWhat = "read";
        } else if(accessType == WRITE) {
            doWhat = "write to";
        } else {
            doWhat = "execute";
        }
        printf("Permission denied to %s file \"%s\".\n", doWhat, filePath);
        return EACCES;
    } else if(errno == ENOENT) {
        // Directory does not exist
        printf("File \"%s\" does not exist.\n", filePath);
        return ENOENT;
    } else if(errno == EROFS) {
        // Write permission was requested for a file on a read-only file system
        printf("You can not write on a read-only file system.\n");
        return EROFS;
    } else {
        // Another error.
        printf("Error ocurred when trying to access file.\n");
        return -99;
    }
}
