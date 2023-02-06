#include "BleKeyboard.h"
#include <stdint.h>

#define MATRIX_ROWS 8
#define MATRIX_COLS 16
#define MATRIX_LAYERS 2
#define row1  14
#define row2  32
#define row3  15
#define row4  33
#define row5  27
#define row6  12
#define row7  13
#define row8  21

uint8_t rows[MATRIX_ROWS] = {row1, row2 , row3, row4, row5, row6, row7, row8};

uint8_t keymap[MATRIX_LAYERS][MATRIX_ROWS][MATRIX_COLS] = 
{ {{' ',' ',' ',' ',' ','b',' ','n',' ',' ','/',KEY_DOWN_ARROW, KEY_RIGHT_ARROW,' ',KEY_LEFT_ARROW,KEY_RIGHT_ALT},
    {KEY_RIGHT_CTRL,KEY_RIGHT_SHIFT,'z','x','c','v',KEY_NUM_ENTER,'m',',','.',' ',' ',' ',' ',' ',' '},
    {' ',' ','a','s','d','f','\\','j','k','l',';',' ',' ',' ',' ',' '},
    {' ',' ','q','w','e','r',' ','u','i','o','p',' ',' ',' ',' ',' '},
    {' ',' ','1','2','3','4',KEY_F10,'7','8','9','0',KEY_F11,KEY_F12,KEY_PAGE_DOWN,KEY_END,KEY_PRTSC},
    {KEY_LEFT_CTRL,' ','`',KEY_F1,KEY_F2,'5',KEY_F9,'6','=',KEY_F8,'-',KEY_DELETE,KEY_INSERT,KEY_PAGE_UP,KEY_HOME,' '},
    {' ',KEY_LEFT_SHIFT, KEY_TAB, KEY_CAPS_LOCK,KEY_F3,'t',KEY_BACKSPACE,'y',']',KEY_F7,'[',' ',' ',' ',' ',' '},
    {' ',' ',KEY_ESC,' ',KEY_F4,'g',KEY_F5,'h',KEY_F6,' ','\'',' ',' ',' ',KEY_UP_ARROW,KEY_LEFT_ALT}},

  {{' ',' ',' ',' ',' ','B',' ','N',' ',' ','?',KEY_DOWN_ARROW, KEY_RIGHT_ARROW,' ',KEY_LEFT_ARROW,KEY_RIGHT_ALT},
    {KEY_RIGHT_CTRL,KEY_RIGHT_SHIFT,'Z','X','C','V',KEY_NUM_ENTER,'M','<','>',' ',' ',' ',' ',' ',' '},
    {' ',' ','A','S','D','F','|','J','K','L',':',' ',' ',' ',' ',' '},
    {' ',' ','Q','W','E','R',' ','U','I','O','P',' ',' ',' ',' ',' '},
    {' ',' ','!','@','#','$',KEY_F10,'&','*','(',')',KEY_F11,KEY_F12,KEY_PAGE_DOWN,KEY_END,KEY_PRTSC},
    {KEY_LEFT_CTRL,' ','~',KEY_F1,KEY_F2,'%',KEY_F9,'&','+',KEY_F8,'_',KEY_DELETE,KEY_INSERT,KEY_PAGE_UP,KEY_HOME,' '},
    {' ',KEY_LEFT_SHIFT, KEY_TAB, KEY_CAPS_LOCK,KEY_F3,'T',KEY_BACKSPACE,'Y','}',KEY_F7,'{',' ',' ',' ',' ',' '},
    {' ',' ',KEY_ESC,' ',KEY_F4,'G',KEY_F5,'H',KEY_F6,' ','\"',' ',' ',' ',KEY_UP_ARROW,KEY_LEFT_ALT}}
};

bool pressedMap[MATRIX_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {false};