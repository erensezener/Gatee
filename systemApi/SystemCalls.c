#include "SystemCalls.h"

/*
 * Usage:
 *
 * char *currentWorkingDirectory = getWorkingDirectory();
 *
 * printf("%s\n", currentWorkingDirectory);
 */

char * getWorkingDirectory() {
    return getcwd(NULL, 0);
}

/*
 * Usage:
 *
 * changeDirectoryTo("/Users/--something--/Documents");
 */

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
 * Usage:
 *
 * int dirItemCount;
 * struct dirent * * directoryContents = getDirectoryContents(getWorkingDirectory(), &dirItemCount);
 *
 * for (int i = 0; i < dirItemCount; ++i) {
 *     printf("%s\n", directoryContents[i]->d_name);
 * }
 */

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
 */

void getDirectoryContentNames(char * directory, int * dirItemCount, char * * * dirContentNames) {
    struct dirent * * directoryContents;
    *dirItemCount = scandir (directory, &directoryContents, one, alphasort);

    if (*dirItemCount >= 0) {
        *dirContentNames = malloc((int)dirItemCount * sizeof(char * *));
		for (i = 0; i < *dirItemCount; ++i) {
            (*dirContentNames)[i] = malloc(strlen(directoryContents[i]->d_name) * sizeof(char *));
            strcpy((*dirContentNames)[i], directoryContents[i]->d_name);
        }
    } else {
        perror("Couldn't open the directory");
    }
}

/*
 * Usage:
 *
 * logToFile(--some string--);
 *
 * Creates the log at the current working directory.
 * More info: http://www.cprogramming.com/tutorial/cfileio.html
 */

void logToFile(char * stringToLog) {

    // ----------IMPORTANT, DON'T DELETE-----------
    // char *bp;
    // size_t size;
    // FILE *stream;

    // stream = open_memstream (&bp, &size);

    // fprintf (stream, "hello");
    // fflush (stream);

    // printf ("buf = `%s', size = %d\n", bp, size);

    // fprintf (stream, ", world");
    // fflush (stream);
    // fclose (stream);

    // printf ("buf = `%s', size = %d\n", bp, size);

    // free(stream);
    // ----------IMPORTANT, DON'T DELETE-----------

    FILE *file = fopen(LOG_FILE_NAME, "a+");

    if (file == NULL) {
        printf("Error opening file, unable to log!\n");
    } else {
        fprintf(file, "%s\n", stringToLog);
        fclose(file);
    }

    // ----------IMPORTANT, DON'T DELETE-----------
    // /* print some text */
    // const char *text = "Write this to the file";
    // fprintf(file, "Some text: %s\n", text);

    // /* print integers and floats */
    // int i = 1;
    // float py = 3.1415927;
    // fprintf(file, "Integer: %d, float: %f\n", i, py);

    // /* printing single chatacters */
    // char c = 'A';
    // fprintf(file, "A character: %c\n", c);
    // ----------IMPORTANT, DON'T DELETE-----------

}

/*
 * Usage:
 *
 * logToFileAt(--some string--, "/bin/logs");
 */

void logToFileAt(char * stringToLog, char * logFilePath) {
    char * currentDir = getWorkingDirectory();
    changeDirectoryTo(logFilePath);
    logToFile(stringToLog);
    changeDirectoryTo(currentDir);
}

/*
 * Usage:
 *
 * logToFileAtRoot(--some string--);
 */

void logToFileAtRoot(char * stringToLog) {
    if(canWriteTo("/") == 0) {
        logToFileAt(stringToLog, "/");
    } else {
        printf("Error when logging to file at the root folder (no write permissions for \"/\").\n");
        printf("To write to the root folder, try running Gatee as sudo (sudo gatee).\n");
    }
}

/*
 * Usage:
 *
 * canRead("/bin/logs") == 0;
 * canRead("/bin/logs/log.txt") == 0;
 */

int canRead(char * filePath) {
    return canAccessTo(filePath, READ);
}

/*
 * Usage:
 *
 * canWriteTo("/") == 0;
 * canWriteTo("/log.txt") == 0;
 */

int canWriteTo(char * filePath) {
    return canAccessTo(filePath, WRITE);
}

/*
 * Usage:
 *
 * canExecute("/bin/gatee");
 */

int canExecute(char * filePath) {
    return canAccessTo(filePath, EXECUTE);
}

/*
 * Usage:
 *
 * canAccessTo("/bin/logs/log.txt", READ);
 * canAccessTo("/bin/logs/log.txt", WRITE);
 * canAccessTo("/bin/gatee", EXECUTE);
 */

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
