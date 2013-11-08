#include "gateeMenu.h"

ITEM **listItems;
int inputChar;
MENU *menu;
int numListItems;

int main() {

    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize items */
    initItems();

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
            default:
                keyPressed(inputChar);
                break;
        }
    }
    destructor();
}

void initItems() {
    changeDirectoryTo("/Users/aemreunal/Documents");

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
    printSelectedItemName(item_name(currentSelectedItem));

    pos_menu_cursor(menu);

    // set_menu_items(menu, listItems);
    // initItems();
    // initMenu();
    // post_menu(menu);
    // refresh();
}


//Not in use
//Prints the selected item
void printSelectedItemName(char *name) {
    int lineNumberToPrintAt = 26;
    move(lineNumberToPrintAt, 0);
    clrtoeol();
    mvprintw(lineNumberToPrintAt, 0, "Item selected is : %s", name);

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
