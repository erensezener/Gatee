#ifndef GATEEMENU_H
#define GATEEMENU_H

#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <locale.h>
#include "SystemAPI/SystemCalls.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4
#define KEY_SPACE ' '
#define KEY_ENTER_NCURSES 10

#define PAR_DIR 0
#define DIR 1
#define FILE 2

MENU * menu;
ITEM * * listItems;
int numListItems;

char baseDir[1000];
char logDir[1000];
char newFolderName[300];

int inputChar;
int i;

// TEST
// char * buffer;
// buffer = malloc((strlen(newFolderName) + 5) * sizeof(char));
// memset(buffer, '\0', (strlen(newFolderName) + 5));
// snprintf(buffer, (strlen(newFolderName) + 5), "nano %s", newFolderName);
// TEST

void enterKeyPressed();

void downKeyPressed();

void upKeyPressed();

void leftKeyPressed();

void spaceKeyPressed();

void keyPressed(int inputChar);

void initItems(char *folderName, char*baseDir);

void initMenu();

void println(char *string, int lineNumberToPrintAt);

void destructor();

void printCurrentDirectory();

void printDirList();

int getType(char * folderName);

#endif
