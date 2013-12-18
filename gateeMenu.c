#include "gateeMenu.h"

int main() {
    strcpy(baseDir, "/");

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
    destructor(baseDir);
}

void initItems(char * folderName) {
	if (strcmp(folderName, "") == 0){
		logToFileAt("Empty Folder Name case, returning to base directory.", logDir);
    	changeDirectoryTo(baseDir);
	} else {
        switch (getType(folderName)) {
            case PAR_DIR:
                strcpy(newFolderName, baseDir);
                strcat(newFolderName, "/..");
                break;
            case DIR:
                strcpy(newFolderName, baseDir);
                strcat(newFolderName, "/");
                folderName = folderName + 2; //Ignore first 2 charactes: "> "
                strcat(newFolderName, folderName);
                break;
            case FILE:
                strcpy(newFolderName, baseDir);
                strcat(newFolderName, "/");
                folderName = folderName + 2; //Ignore first 2 charactes: "  "
                strcat(newFolderName, folderName);

                destructor(newFolderName);
                exit(0);
                break;
            default:
                logToFileAt("Wrong Prefix! File is: ", logDir);
                logToFileAt(folderName, logDir);
                break;
        }
		changeDirectoryTo(newFolderName);
		strcpy(baseDir, newFolderName);
	}
    printDirList();
    printCurrentDirectory();
}

int getType(char * folderName) {
    if (folderName[0] == '>' && folderName[1] == ' ') {
        /* Directory case */
        return DIR;
    } else if (folderName[0] == ' ' && folderName[1] == ' ') {
        /* File case */
        return FILE;
    } else if (folderName[0] == '<' && folderName[1] == ' ') {
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

// void spaceKeyPressed() {
//     menu_driver(menu, REQ_NEXT_MATCH);
// }

void enterKeyPressed() {
    ITEM *currentSelectedItem;
    void (*p)(char *);

    currentSelectedItem = current_item(menu);

    p = item_userptr(currentSelectedItem);
    p((char *)item_name(currentSelectedItem));
    //printSelectedItemName(item_name(currentSelectedItem));
    pos_menu_cursor(menu);

	clear();
    char *postfixDir = (char*) item_name(currentSelectedItem);
    initItems(postfixDir);
    initMenu();
    post_menu(menu);
    refresh();

}

//Duplicate of leftKeyPressed
// void backspaceKeyPressed() {
//     menu_driver(menu, REQ_BACK_PATTERN);
// }


void println(char *string, int lineNumberToPrintAt) {
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "%s", string);
}

//Prints the current directory
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
