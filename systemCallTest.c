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

 //    char *currentWorkingDirectory = getWorkingDirectory();

 //    printf("%s\n", currentWorkingDirectory);
	// printf("End");

    char *cd = "/Usersss";
    // changeDirectoryTo(cd);

    cd = "/Users/aemreunal/Documents/University/2013 - 2014/";
    changeDirectoryTo(cd);

    // currentWorkingDirectory = getWorkingDirectory();

    // printf("%s\n", currentWorkingDirectory);

    int dirItemCount;
    char * * dirContents;
    getDirectoryContentNames(cd, &dirItemCount, &dirContents);

    printf("Number of items in the directory: %d\n", dirItemCount);
	int i;
    for (i = 0; i < dirItemCount; ++i) {
        printf("%s\n", dirContents[i]);
    }

    // changeDirectoryTo("/Users/aemreunal/Documents/GitHub Repositories/Gatee");
    // logToFile("Deneme 123");

    // logToFileAtRoot("hop");

    // printf("%d\n", canRead("/log.txt"));
    // printf("%d\n", canWriteTo("/log.txt"));

    return 0;
}
