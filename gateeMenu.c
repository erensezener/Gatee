#include "gateeMenu.h"

ITEM **listItems;
int inputChar;
MENU *menu;
int numListItems;
char newFolderName[300];
char baseDir[300];

int main() {
	
	strcpy(baseDir, "/Users/erensezener/Documents");
	
	logToFileAt("---------", "/Users/erensezener/Gatee");
	
    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize items */
    initItems("", baseDir);
    // initItems();
	

    /* Create menu */
    initMenu();

    /* Post the menu */
    mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
    mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
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
	logToFileAt("BaseDir is: ", "/Users/erensezener/Gatee");
	logToFileAt(baseDir, "/Users/erensezener/Gatee");
	
	//logToFileAt("In init items", "/Users/erensezener/Gatee");
// void initItems() {
	// char *folderName = "";
	if (strcmp(folderName, "") == 0){
		logToFileAt("Empty Folder Name Case", "/Users/erensezener/Gatee");
    	changeDirectoryTo(baseDir);
		//logToFileAt("changeDirectoryTo(baseDir);", "/Users/erensezener/Gatee");
	}else{
		logToFileAt("Folder Name Case", "/Users/erensezener/Gatee");
		//char *newFolderName[200] ;
// 		
// 		if((newFolderName = malloc(strlen(baseDir)+strlen(folderName)+1)) != NULL){
// 		    newFolderName[0] = '\0';   // ensures the memory is an empty string
// 		    strcat(baseDir,folderName);
// 		    strcat(baseDir,folderName);
		strcpy(newFolderName, baseDir);
		//logToFileAt("strcpy(newFolderName, baseDir);", "/Users/erensezener/Gatee");
		
		strcat(newFolderName, "/");
		//logToFileAt("strcat(newFolderName,);", "/Users/erensezener/Gatee");
		
		strcat(newFolderName, folderName);
		//logToFileAt("strcat(newFolderName, folderName);", "/Users/erensezener/Gatee");
		
		changeDirectoryTo(newFolderName);
		strcpy(baseDir,newFolderName);
		
		logToFileAt("Folder Name is: ", "/Users/erensezener/Gatee");
		logToFileAt(newFolderName, "/Users/erensezener/Gatee");
		
		
		
		//} 
		
	}
	//logToFileAt("After if-else", "/Users/erensezener/Gatee");
    int dirItemCount;
    char * * dirContents;
    getDirectoryContentNames(getWorkingDirectory(), &dirItemCount, &dirContents);
	//logToFileAt("getDirectoryContentNames", "/Users/erensezener/Gatee");

    numListItems = dirItemCount;
    listItems = (ITEM **)calloc(numListItems + 1, sizeof(ITEM *));
	int i;
    for (i = 0; i < numListItems; ++i) {
        listItems[i] = new_item(dirContents[i], "");
        /* Set the user pointer */
        set_item_userptr(listItems[i], printCurrentDirectory);
    }
	//logToFileAt("for", "/Users/erensezener/Gatee");
	
    listItems[numListItems] = (ITEM *)NULL;
	//logToFileAt("End of init items", "/Users/erensezener/Gatee");
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
	//logToFileAt("currentSelectedItem = current_item(menu);", "/Users/erensezener/Gatee");
	
    p = item_userptr(currentSelectedItem);
	//logToFileAt("p = item_userptr(currentSelectedItem);", "/Users/erensezener/Gatee");
	
    p((char *)item_name(currentSelectedItem));
	//logToFileAt("p((char *)item_name(currentSelectedItem));", "/Users/erensezener/Gatee");
	
    printSelectedItemName(item_name(currentSelectedItem));
	//logToFileAt("printSelectedItemName(item_name(currentSelectedItem));", "/Users/erensezener/Gatee");
	

    pos_menu_cursor(menu);
	//logToFileAt("pos_menu_cursor(menu);", "/Users/erensezener/Gatee");
	

    // set_menu_items(menu, listItems);
    initItems(item_name(currentSelectedItem), baseDir);
	//logToFileAt("initItems("");", "/Users/erensezener/Gatee");
	
    initMenu();
	//logToFileAt("initMenu();", "/Users/erensezener/Gatee");
	
    post_menu(menu);
	//logToFileAt("post_menu(menu);", "/Users/erensezener/Gatee");
	
    refresh();
	//logToFileAt("refresh();", "/Users/erensezener/Gatee");
	
}

//Duplicate of leftKeyPressed
// void backspaceKeyPressed() { 
//     menu_driver(menu, REQ_BACK_PATTERN);
// }


//Not in use
//Prints the selected item
void printSelectedItemName(const char *name) {
    int lineNumberToPrintAt = 26;
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "Item selected is : %s", name);
	
	// initItems();
    // initItems(name);
    // initMenu();
    // post_menu(menu);
    // refresh();
	

    /* TEST */
    // lineNumberToPrintAt += 1;
    // changeDirectoryTo("/Users/aemreunal/Documents");
    // move(lineNumberToPrintAt, 0);
    // clrtoeol();
    // mvprintw(lineNumberToPrintAt, 0, "Current working directory is : %s", getWorkingDirectory());

    // lineNumberToPrintAt += 1;

    // int dirItemCount;
    // char * * dirContents;
    // getDirectoryContentNames(getWorkingDirectory(), &dirItemCount, &dirContents);

    // for (i = 0; i < dirItemCount; ++i) {
    //     move(lineNumberToPrintAt + i, 0);
    //     clrtoeol();
    //     mvprintw((lineNumberToPrintAt + i), 0, "%s", dirContents[i]);
    // }
    /* TEST */
}

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
