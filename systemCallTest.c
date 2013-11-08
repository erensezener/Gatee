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

    char *cd = "/Usersss";
    changeDirectoryTo(cd);

    cd = "/Users/aemreunal/Documents";
    changeDirectoryTo(cd);

    currentWorkingDirectory = getWorkingDirectory();

    printf("%s\n", currentWorkingDirectory);

    int dirItemCount;
    char * * dirContents;
    getDirectoryContentNames(currentWorkingDirectory, &dirItemCount, &dirContents);

    printf("Number of items in the directory: %d\n", dirItemCount);

    for (int i = 0; i < dirItemCount; ++i) {
        printf("%s\n", dirContents[i]);
    }

    return 0;
}
