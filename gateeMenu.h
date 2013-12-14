#ifndef GATEEMENU_H
#define GATEEMENU_H

#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include "SystemAPI/SystemCalls.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char newFolderName[300];

char logDir[100];

int i;

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

#endif
