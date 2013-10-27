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
    // free(status);
}

//---------------------------------------------------
//--------------------Example------------------------
//---------------------------------------------------
static int one (const struct dirent *unused) {
    return 1;
}

void listDirectoryContents(char * directory) {
    struct dirent **directoryContents;
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


void getDirectoryContents(char * directory, char * directoryList[]) {
    struct dirent **directoryContents;
    int size;

    size = scandir (directory, &directoryContents, one, alphasort);
    if (size >= 0) {
        int i;
        for (i = 0; i < size; ++i) {
            // directoryList[i] = directoryContents[i]->d_name;
            // puts(directoryList[i]);
            char * directoryName = directoryContents[i]->d_name;
            directoryList[i] = malloc(strlen(directoryName) + 1);
            strcpy(directoryList[i], directoryName);
        }
    } else {
        perror("Couldn't open the directory");
    }

    // for (int i = 0; i < 5; ++i) {
    //     directoryList[i] = malloc(strlen("foo") + 1);
    //     strcpy(directoryList[i], "foo");
    // }
}

// int* function(int tags){
//   int * var = malloc(sizeof(int)*tags);
//   //....
//   return var;
// }
// strs[i] = malloc(strlen("foo") + 1);
// strcpy(strs[i], "foo");

