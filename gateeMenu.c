#include "gateeMenu.h"

int main() {
    strcpy(sourceDir, getWorkingDirectory());

    setlocale(LC_CTYPE, "");

    /* Initialize curses */
    initscr();
    //start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

	// 2nd and 3rd param are # of rows wanted and # of columns wanted (for the list), respectively
	set_menu_format(menu, getNumTerminalRows() - 2, 1);

    /* Initialize items */
    initItems("");

    /* Create menu */
    initMenu();

    /* Post the menu */
    post_menu(menu);
    refresh();

    /* Main program loop */
    while((inputChar = getch()) != KEY_F(1)) {
        switch(inputChar) {
            case KEY_DOWN:
                downKeyPressed();
                break;
            case KEY_UP:
                upKeyPressed();
                break;
            case KEY_ENTER_NCURSES:
                enterKeyPressed();
                break;
            case KEY_LEFT:
                leftKeyPressed();
                break;
            case KEY_RIGHT:
                rightKeyPressed();
                break;
            // case KEY_SPACE:
            //     spaceKeyPressed();
            //     break;
			// case KEY_DC:
			//     backspaceKeyPressed();
			// 	   break;
            default:
                keyPressed(inputChar);
                break;
        }
    }
    destructor(sourceDir);
}

void initItems(char * selectedFile) {
	if (strcmp(selectedFile, "") == 0){
		logToFileAt("Empty Folder Name case, returning to base directory.", logDir);
    	changeDirectoryTo(sourceDir);
	} else {
        switch (type = getType(selectedFile)) {
            case PAR_DIR:
                strcpy(targetDir, sourceDir);
                strcat(targetDir, "/..");
                break;
            case DIR:
            case FILE:
                strcpy(targetDir, sourceDir);
                strcat(targetDir, "/");
                /* +2 to ignore the first character: " " or ">" */
                strcat(targetDir, (selectedFile + PREFIX_SIZE));
                if (type == FILE) {
                    destructor(targetDir);
                    exit(0);
                }
                break;
            default:
                logToFileAt("Wrong Prefix! File is: ", logDir);
                logToFileAt(selectedFile, logDir);
                break;
        }
		changeDirectoryTo(targetDir);
		strcpy(sourceDir, targetDir);
	}
    printDirList();
    printCurrentDirectory();
}

int getType(char * fileName) {
    if (fileName[0] == '>') {
        /* Directory case */
        return DIR;
    } else if (fileName[0] == ' ') {
        /* File case */
        return FILE;
    } else if (fileName[0] == '<') {
        /* Parent directory case */
        return PAR_DIR;
    } else {
        return -1;
    }

}

void printDirList() {
    int dirItemCount;
    char * * dirContents;
    getDirectoryContentNames(getWorkingDirectory(), &dirItemCount, &dirContents);

    numListItems = dirItemCount;
    listItems = (ITEM **)calloc(numListItems + 1, sizeof(ITEM *));
    int i;
    for (i = 0; i < numListItems; ++i) {
        listItems[i] = new_item(dirContents[i], "");
        /* Set the user pointer */
        set_item_userptr(listItems[i], printCurrentDirectory);
    }
    listItems[numListItems] = (ITEM *)NULL;
}

void initMenu() {
    menu = new_menu((ITEM **)listItems);
}

void keyPressed(int inputChar) {
    menu_driver(menu, inputChar);
}

void downKeyPressed() {
    menu_driver(menu, REQ_DOWN_ITEM);
}

void upKeyPressed() {
    menu_driver(menu, REQ_UP_ITEM);
}

void leftKeyPressed() {
    menu_driver(menu, REQ_BACK_PATTERN);
}

void rightKeyPressed() {
    menu_driver(menu, REQ_NEXT_MATCH);
}

void spaceKeyPressed() {
    menu_driver(menu, REQ_NEXT_MATCH);
}

void enterKeyPressed() {
    ITEM *currentSelectedItem;
    void (*p)(char *);

    currentSelectedItem = current_item(menu);

    p = item_userptr(currentSelectedItem);
    p((char *)item_name(currentSelectedItem));
    pos_menu_cursor(menu);

	clear();
    char *postfixDir = (char*) item_name(currentSelectedItem);
    initItems(postfixDir);
    initMenu();
    post_menu(menu);
    refresh();

}

// Duplicate of leftKeyPressed
//
// void backspaceKeyPressed() {
//     menu_driver(menu, REQ_BACK_PATTERN);
// }


void println(char *string, int lineNumberToPrintAt) {
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "%s", string);
}

void printCurrentDirectory() {
    int lineNumberToPrintAt = LINES - 1;
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "Working dir: %s", getWorkingDirectory());
}

void destructor(char * dirToExit) {
    prepareToExit(dirToExit);
    unpost_menu(menu);
    for(i = 0; i < numListItems; ++i) {
        free_item(listItems[i]);
    }
    free_menu(menu);
    endwin();
}
