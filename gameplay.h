#include <stdio.h>
#include <stdbool.h>
#include "gba.h"

#define BOARD_HEIGHT 21
#define BOARD_WIDTH 10
#define BOARD_CORNER_ROW 143
#define BOARD_CORNER_COL 85
#define SQUARE_SIZE 7

#define Q0_ROW 30
#define Q1_ROW 60
#define Q2_ROW 90
#define Q_COL 170

#define H_ROW 24
#define H_COL 64


enum shape {
    O,
    I,
    L,
    J,
    S,
    Z,
    T
};

enum direction {
    UP,
    LEFT,
    DOWN,
    RIGHT
};

typedef struct {
    int row;
    int col;
} coord;

typedef struct {
    enum shape shape;
    enum direction direction; //direction tetromino is facing
    u16 color;
    coord squares[4]; //index 0 is pivot square
    coord currCoord;
} tetromino;

//Prototypes
void initBoard(int a);
void initTetromino(int shape);
void initFakeTetromino(int shape, int row, int col);
void setTetrominoSquares(int a);
coord coords(int row, int col);
void drawBoard(int startRow, int endRow);
void drawQueue(int a);
void drawHold(int a);
void drawTetromino(int a);
void undrawTetromino(int a);
void updateTetromino(int newRow, int newCol, int direction);
void moveTetromino(int direction);
void rotateTetromino(int direction);
void hardDrop(int a);
int clearLines(int a);
void newPiece(int a);
bool onGround(int a);
tetromino copy(int a);
bool gameOver(int a);
void refreshPrevRows(int a);