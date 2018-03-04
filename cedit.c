/* 

PROGRAM C Editor - An editor with top-down menus.

@author : Velorek
@version : 1.0
Last modified : 04/3/2018

*/

#include <stdio.h>
#include <string.h>
#include "c_cool.h"
#include "list_choice.h"
#include "screen_buffer.h"

LISTCHOICE *mylist, data;
BCELL  *my_screen;

int     rows, columns, old_rows, old_columns;
int     exitp = 0;
char    kglobal; //Global variables should be turned into functions

//Function declarations
void credits();
int main_screen();
void loadmenus(int choice);
void filemenu();
void optionsmenu();
void helpmenu();
int confirmation();


//PROGRAM
int main() {
  char    ch;
  //hidecursor();
  create_screen();
  main_screen();
  do {
    ch = getch();
    if(ch == 'a' || ch == 'A') {
      loadmenus(0);		// horizontal menu
      start_hmenu(&data);
      free_list(mylist);
      kglobal = 0;		//reset kglobal
      //drop-down menu loop -1 value indicates that vertical arrows can be used
      do {
	if(data.index == 0) {
	  filemenu();
	  if(kglobal == -1) {
	    data.index = 1;
	  }
	  if(kglobal == -2) {
	    data.index = 2;
	  }
	}
	if(data.index == 1) {
	  optionsmenu();
	  if(kglobal == -1) {
	    data.index = 2;
	  }
	  if(kglobal == -2) {
	    data.index = 0;
	  }
	}
	if(data.index == 2) {
	  helpmenu();
	  if(kglobal == -1) {
	    data.index = 0;
	  }
	  if(kglobal == -2) {
	    data.index = 1;
	  }
	}
      } while(kglobal != 10);
    }

  } while(exitp != 1);
  credits();
  //showcursor;
  return 0;
}

/* FUNCTION DEFINITIONS */

/* Draw the main screen */
int main_screen() {
  int     i;
  rows = 0;
  columns = 0;

  //Save previous values
  old_rows = rows;
  old_columns = columns;
  get_terminal_dimensions(&rows, &columns);

  if(rows == 0)
    rows = 25;		//just in case it can't find the terminal dimensions
  if(columns == 0)
    columns = 80;

  bscreen_color(B_BLUE);
  //Draw upper and lower bars
  for(i = 1; i <= columns; i++) {
    write_ch(i, 1, 32, B_WHITE, F_WHITE);
  }

  for(i = 1; i < columns; i++) {
    write_ch(i, rows, 32, B_WHITE, F_WHITE);
  }

  write_str(1, 1, "File  Options  Help", B_WHITE, F_BLACK);
  write_str(1, rows, ">> [C-Edit] - Coded by Velorek", B_WHITE, F_BLACK);
  write_num(columns - 10, 1, rows, 3, B_WHITE, F_BLACK);
  write_str(2, 3, "Press A to activate menus", B_BLUE, F_WHITE);
  update_screen();
  return 0;
}


/* Load current menu into circular linked list */ 
void loadmenus(int choice) {
  if(choice == 0) {
    add_item(mylist, "File", 1, 1, B_WHITE, F_BLACK, B_BLACK, FH_WHITE);
    add_item(mylist, "Options", 7, 1, B_WHITE, F_BLACK, B_BLACK, FH_WHITE);
    add_item(mylist, "Help", 16, 1, B_WHITE, F_BLACK, B_BLACK, FH_WHITE);
  }

  if(choice == 1) {
    add_item(mylist, "Option 1", 3, 3, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Option 2", 3, 4, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Option 3", 3, 5, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Option 4", 3, 6, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Option 5", 3, 7, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Exit", 3, 8, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
  }
  if(choice == 2) {
    add_item(mylist, "Settings", 9, 3, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Colors", 9, 4, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
    add_item(mylist, "Profiles", 9, 5, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
  }
  if(choice == 3) {
    add_item(mylist, "Help...F1", 18, 3, B_WHITE, F_BLACK, B_BLACK,
	     F_WHITE);
    add_item(mylist, "About", 18, 4, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
  }

  if(choice == 5) {
    add_item(mylist, "<YES>", 28, 12, B_WHITE, F_BLACK, B_BLACK,
	     F_WHITE);
    add_item(mylist, "<NO>", 40, 12, B_WHITE, F_BLACK, B_BLACK, F_WHITE);
  }
}

/* Display File Menu */
void filemenu() {
  loadmenus(1);
  write_str(1, 1, "File", B_BLACK, F_WHITE);
  draw_window(1, 2, 13, 9, B_WHITE, F_BLACK, 1);
  kglobal = start_vmenu(&data);
  close_window();
  write_str(1, 1, "File  Options  Help", B_WHITE, F_BLACK);
  update_screen();
  free_list(mylist);
  if(data.index == 5) {
	exitp = confirmation(); //Shall we exit? Global variable (to be updated)
  }
  data.index = -1;
}

/* Display Options Menu */
void optionsmenu() {
  loadmenus(2);
  write_str(7, 1, "Options", B_BLACK, F_WHITE);
  draw_window(7, 2, 19, 6, B_WHITE, F_BLACK, 1);
  kglobal = start_vmenu(&data);
  close_window();
  write_str(1, 1, "File  Options  Help", B_WHITE, F_BLACK);
  update_screen();
  free_list(mylist);
  data.index = -1;
}

/* Display Help Menu */
void helpmenu() {
  loadmenus(3);
  write_str(16, 1, "Help", B_BLACK, F_WHITE);
  draw_window(16, 2, 28, 5, B_WHITE, F_BLACK, 1);
  kglobal = start_vmenu(&data);
  close_window();
  write_str(1, 1, "File  Options  Help", B_WHITE, F_BLACK);
  update_screen();
  free_list(mylist);
  data.index = -1;
}

/* Displays a window to asks user for confirmation */
int confirmation(){
    int ok=0;
    loadmenus(5);
    draw_window(16, 6, columns - 20, rows - 10, B_WHITE, F_BLACK, 1);
    write_str(23, 8, "Are you sure you want to quit?", F_BLACK, B_WHITE);
    start_hmenu(&data);
    free_list(mylist);
    if(data.index == 0)
      ok = 1; //Confirmation has been given
    close_window();
    return ok; 
}

/* Frees memory and displays goodbye message */
void credits(){
  free_buffer();
  screencol(0);
  outputcolor(7, 0);
  printf("[C-Edit] coded by Velorek. \n");
}