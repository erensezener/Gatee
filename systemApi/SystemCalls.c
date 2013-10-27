#include "SystemCalls.h"

char * getWorkingDir() {
    return getcwd(NULL, 0);
}
