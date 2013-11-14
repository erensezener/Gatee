#include "gateeMenu.h"

ITEM **listItems;
int inputChar;
MENU *menu;
int numListItems;
char newFolderName[300];
char baseDir[300];
char logDir[100];

int main() {
	/* Logs are created in this directory */
	strcpy(logDir,"/Users/erensezener/Gatee");
	
	/* Navigation starts from this directory*/
	strcpy(baseDir, "/Users/erensezener/Documents");
	
	logToFileAt("---------", logDir);
	
    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
	
	// 2nd and 3rd param are # of rows and # of columns respectively
	set_menu_format(menu, 40,1); 

    /* Initialize items */
    initItems("", baseDir);
	
    /* Create menu */
    initMenu();

    /* Post the menu */
    //mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
    //mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
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
            case 10: /* Enter */
                enterKeyPressed();
                break;
            case KEY_LEFT:
                leftKeyPressed();
                break;
            case ' ':
                spaceKeyPressed();
                break;
			// case KEY_DC:
			// 	backspaceKeyPressed();
			// 	break;
            default:
                keyPressed(inputChar);
                break;
        }
    }
    destructor();
}

void initItems(char *folderName, char *baseDir) {
	logToFileAt("BaseDir is: ", logDir);
	logToFileAt(baseDir, logDir);
	
	if (strcmp(folderName, "") == 0){
		logToFileAt("Empty Folder Name Case", logDir);
    	changeDirectoryTo(baseDir);

	}else{
		logToFileAt("Folder Name Case", logDir);

		strcpy(newFolderName, baseDir);		
		strcat(newFolderName, "/");
		strcat(newFolderName, folderName);
		
		changeDirectoryTo(newFolderName);
		strcpy(baseDir,newFolderName);
		
		logToFileAt("Folder Name is: ", logDir);
		logToFileAt(newFolderName, logDir);
		
	}
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

void spaceKeyPressed() {
    menu_driver(menu, REQ_NEXT_MATCH);
}

void enterKeyPressed() {
    ITEM *currentSelectedItem;
    void (*p)(char *);

    currentSelectedItem = current_item(menu);
	
    p = item_userptr(currentSelectedItem);	
    p((char *)item_name(currentSelectedItem));
    //printSelectedItemName(item_name(currentSelectedItem));
    pos_menu_cursor(menu);
	
	clear();
    initItems(item_name(currentSelectedItem), baseDir);
    initMenu();
    post_menu(menu);
    refresh();	

}

//Duplicate of leftKeyPressed
// void backspaceKeyPressed() { 
//     menu_driver(menu, REQ_BACK_PATTERN);
// }


//Prints the current directory
void printCurrentDirectory() {
    int lineNumberToPrintAt = LINES - 5;
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "Your current directory is %s", getWorkingDirectory());
}

void destructor() {
    unpost_menu(menu);
	for(i = 0; i < numListItems; ++i) {
        free_item(listItems[i]);
    }
    free_menu(menu);
    endwin();
}

void println(char *string, int lineNumberToPrintAt) {
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "%s", string);
}
