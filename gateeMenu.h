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

char * logDir = "/";

MENU * menu;
ITEM * * listItems;
int numListItems;

char sourceDir[1000];
char targetDir[1000];

/* Temp variables */
int inputChar;
int type;
int i;
/* Temp variables */

// TEST
// char * buffer;
// buffer = malloc((strlen(targetDir) + 5) * sizeof(char));
// memset(buffer, '\0', (strlen(targetDir) + 5));
// snprintf(buffer, (strlen(targetDir) + 5), "nano %s", targetDir);
// TEST

void enterKeyPressed();

void downKeyPressed();

void upKeyPressed();

void leftKeyPressed();

void rightKeyPressed();

void spaceKeyPressed();

void keyPressed(int inputChar);

void initItems(char * selectedFile);

void initMenu();

void println(char * string, int lineNumberToPrintAt);

void destructor();

void printCurrentDirectory();

void printDirList();

int getType(char * fileName);

#endif
