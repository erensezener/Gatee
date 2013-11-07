#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Test",
    "Deneme",
    "Example",
    "eren",
    "Exit",
};

void enterKeyPressed();

void downKeyPressed();

void upKeyPressed();

void leftKeyPressed();

void spaceKeyPressed();

void keyPressed(int inputChar);

void initItems();

void initMenu();

void printSelectedItemName(char *name);

void destructor();
