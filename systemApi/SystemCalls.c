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
    // free(status);
}

//---------------------------------------------------
//--------------------Example------------------------
//---------------------------------------------------
int one (const struct dirent *unused) {
    return 1;
}

void listDirectoryContents(char * directory) {
    struct dirent * * directoryContents;
    int size;

    size = scandir (directory, &directoryContents, one, alphasort);

    if (size >= 0) {
        int i;
        for (i = 0; i < size; ++i) {
            puts(directoryContents[i]->d_name);
        }
    } else {
        perror("Couldn't open the directory");
    }
}
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

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
        int i;
		for (i = 0; i < *dirItemCount; ++i) {
            (*dirContentNames)[i] = malloc(strlen(directoryContents[i]->d_name) * sizeof(char *));
            strcpy((*dirContentNames)[i], directoryContents[i]->d_name);
        }
    } else {
        perror("Couldn't open the directory");
    }
}
