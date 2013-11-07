#include "gateeMenu.h"

ITEM **listItems;
int inputChar;
MENU *menu;
int numListItems;

int main() {
	strcpy(choices[0],"Eren          ");
	strcpy(choices[1],"Test          ");
	
    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //init_pair(1, COLOR_RED, COLOR_BLACK);
    //init_pair(2, COLOR_GREEN, COLOR_BLACK);
    //init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

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
            case 10: /* Enter */{
                enterKeyPressed();
                break;
            }
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
    numListItems = ARRAY_SIZE(choices);
    listItems = (ITEM **)calloc(numListItems + 1, sizeof(ITEM *));
	int i;
    for (i = 0; i < numListItems; ++i) {
        listItems[i] = new_item(choices[i], choices[i]);
        /* Set the user pointer */
        set_item_userptr(listItems[i], printSelectedItemName);
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
    pos_menu_cursor(menu);

	strcpy(choices[0],"Changed          ");
	strcpy(choices[2],"Changed          ");
	strcpy(choices[3],"Changed          ");

    //Change Menu Pointers
    numListItems = ARRAY_SIZE(choices);
    listItems = (ITEM **)calloc(numListItems + 1, sizeof(ITEM *));
	int i;
    for(i = 0; i < numListItems; ++i) {
        listItems[i] = new_item(choices[i], choices[i]);
        /* Set the user pointer */
        set_item_userptr(listItems[i], printSelectedItemName);
    }
    listItems[numListItems] = (ITEM *)NULL;

    set_menu_items(menu, listItems);
    initItems();
    initMenu();
    post_menu(menu);
    refresh();
}

void printSelectedItemName(char *name) {
    int lineNumberToPrintAt = 10;

    move(lineNumberToPrintAt, 0);
    clrtoeol();
    //mvprintw(lineNumberToPrintAt, 0, "Item selected is : %s", name);
}

void destructor() {
    unpost_menu(menu);
	int i;
    for(i = 0; i < numListItems; ++i) {
        free_item(listItems[i]);
    }
    free_menu(menu);
    endwin();
}
