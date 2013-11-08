#include <unistd.h>
#include <fcntl.h>
#include "SystemAPI/SystemCalls.h"

int main()
{
    /*
    int filedesc = open("testfile.txt", O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return 1;

    if(write(filedesc,"This will be output to testfile.txt\n", 36) != 36)
    {
        write(2,"There was an error writing to testfile.txt\n",43);
        return 1;
    }
    */

    char *currentWorkingDirectory = getWorkingDirectory();

    printf("%s\n", currentWorkingDirectory);
	printf("End");

    char *cd = "/Usersss";
    changeDirectoryTo(cd);

    cd = "/Users/aemreunal/Documents";
    changeDirectoryTo(cd);

    currentWorkingDirectory = getWorkingDirectory();

    printf("%s\n", currentWorkingDirectory);

<<<<<<< HEAD
=======
    // int dirItemCount = 0;
    // struct dirent * * directoryContents = getDirectoryContents(getWorkingDirectory(), &dirItemCount);

    // for (int i = 0; i < dirItemCount; ++i) {
    //     printf("%s\n", directoryContents[i]->d_name);
    // }
    // printf("%d\n", dirItemCount);

    // listDirectoryContents(currentWorkingDirectory);


>>>>>>> e67966fd7f29baf019afe69021c0cfd05e0b1d02
    int dirItemCount;
    char * * dirContents;
    getDirectoryContentNames(currentWorkingDirectory, &dirItemCount, &dirContents);

    printf("Number of items in the directory: %d\n", dirItemCount);
	int i;
    for (i = 0; i < dirItemCount; ++i) {
        printf("%s\n", dirContents[i]);
    }

    return 0;
}
