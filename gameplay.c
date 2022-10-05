#include "gameplay.h"

#define _VOID UNUSED(a)

u16 board[BOARD_HEIGHT][BOARD_WIDTH];

tetromino curr;
bool holdPieceUsed;
enum shape heldTetromino;
enum shape queue[3];
int prevRow1;
int prevRow2;

//initialize playing field and board (only done in beginning of games)
void initBoard(int a) {
    _VOID;
    initTetromino(randint(7));
    holdPieceUsed = false;
    queue[0] = (enum shape) randint(7);
    queue[1] = (enum shape) randint(7);
    queue[2] = (enum shape) randint(7);
    drawQueue(0);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = BLACK;
        }
    }
    prevRow1 = -1;
    prevRow2 = -1;
}

//basically a constructor for a tetromino
void initTetromino(int shape) {
    curr.shape = (enum shape) shape;
    updateTetromino(BOARD_HEIGHT - 2, BOARD_WIDTH / 2, UP);
}

//constructor for a tetromino not in play
void initFakeTetromino(int shape, int row, int col) {
    curr.shape = (enum shape) shape;
    curr.direction = UP;
    curr.currCoord = coords(row, col);
    setTetrominoSquares(0);
}

//set squares of tetromino based on orientation, position, and shape
void setTetrominoSquares(int a) {
    _VOID;
    switch (curr.shape) {
        case O:
            curr.color = YELLOW;
            curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
            curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
            curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col - 1);
            curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col);
            break;
        case I:
            curr.color = CYAN;
            switch (curr.direction) {
                case UP:
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row - 2, curr.currCoord.col);
                    break;
                case LEFT:
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col + 2);
                    break;
            }
            break;
        case L:
            curr.color = ORANGE;
            switch (curr.direction) {
                case UP:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col - 2);
                    break;
                case LEFT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row - 2, curr.currCoord.col);
                    break;
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col + 2);
                    break;
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[2] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row + 2, curr.currCoord.col);
                    break;
            }
            break;
        case J:
            curr.color = BLUE;
            switch (curr.direction) {
                case UP:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col + 2);
                    break;
                case LEFT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[2] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row + 2, curr.currCoord.col);
                    break;
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col - 2);
                    break;
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row - 2, curr.currCoord.col);
                    break;
            }
            break;
        case S:
            curr.color = GREEN;
            switch (curr.direction) {
                case UP:
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col - 1);
                    break;
                case LEFT:
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col + 1);
                    break;
            }
            break;
        case Z:
            curr.color = RED;
            switch (curr.direction) {
                case UP:
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col + 1);
                    break;
                case LEFT:
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col - 1);
                    break;
            }
            break;
        case T:
            curr.color = MAGENTA;
            switch (curr.direction) {
                case UP:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    break;
                case LEFT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    curr.squares[3] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    break;
                case DOWN:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[2] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    curr.squares[3] = coords(curr.currCoord.row, curr.currCoord.col - 1);
                    break;
                case RIGHT:
                    curr.squares[0] = coords(curr.currCoord.row, curr.currCoord.col);
                    curr.squares[1] = coords(curr.currCoord.row + 1, curr.currCoord.col);
                    curr.squares[2] = coords(curr.currCoord.row, curr.currCoord.col + 1);
                    curr.squares[3] = coords(curr.currCoord.row - 1, curr.currCoord.col);
                    break;
            }
            break;
    }
}

coord coords(int row, int col) {
    coord returnCoord;
    returnCoord.row = row;
    returnCoord.col = col;
    return returnCoord;
}

void drawBoard(int startRow, int endRow) {
    for (int i = startRow; i <= endRow; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            drawRectDMA(BOARD_CORNER_ROW - i * SQUARE_SIZE, BOARD_CORNER_COL + j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, board[i][j]);
        }
    }
}

void drawQueue(int a) {
    _VOID;
    for (int i = 0; i < 3; i++) {
        u16 colorOfSquare = BLACK;
        switch (queue[i]) {
            case O:
                colorOfSquare = YELLOW;
                break;
            case I:
                colorOfSquare = CYAN;
                break;
            case L:
                colorOfSquare = ORANGE;
                break;
            case J:
                colorOfSquare = BLUE;
                break;
            case S:
                colorOfSquare = GREEN;
                break;
            case Z:
                colorOfSquare = RED;
                break;
            case T:
                colorOfSquare = MAGENTA;
                break;
        }
        drawRectDMA(20 + 32 * i, 170, SQUARE_SIZE * 2, SQUARE_SIZE * 2, colorOfSquare);
    }
}

void drawHold(int a) {
    _VOID;
    drawRectDMA(10, 44, 40, 40, BLACK);
    if (!holdPieceUsed) {
        return;
    }
    tetromino currCopy = copy(0);
    initFakeTetromino(heldTetromino, H_ROW, H_COL);
    drawTetromino(0);
    curr = currCopy;
}

void drawTetromino(int a) {
    _VOID;
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[0].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[0].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, curr.color);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[1].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[1].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, curr.color);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[2].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[2].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, curr.color);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[3].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[3].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, curr.color);
}

void undrawTetromino(int a) {
    _VOID;
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[0].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[0].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[1].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[1].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[2].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[2].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
    drawRectDMA(BOARD_CORNER_ROW - curr.squares[3].row * SQUARE_SIZE, BOARD_CORNER_COL + curr.squares[3].col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
}

//update tetromino's coords or direction and draws new piece
void updateTetromino(int newRow, int newCol, int direction) {
    waitForVBlank(0);
    undrawTetromino(0);
    tetromino prev = copy(0); //store copy of old curr
    curr.currCoord = coords(newRow, newCol); //update piece
    curr.direction = (enum direction) direction;
    setTetrominoSquares(0);
    for (int i = 0; i < 4; i++) {
        if (curr.squares[i].col < 0 || curr.squares[i].col >= BOARD_WIDTH || curr.squares[i].row < 0 || board[curr.squares[i].row][curr.squares[i].col] != BLACK) { //collision test
            curr = prev; //reset curr back to prev
        }
    }
    drawTetromino(0);
}

//move tetromino: 1 = left, 2 = down, 3 = right, 0 = hard drop
void moveTetromino(int direction) {
    switch ((enum direction) direction) {
        case LEFT:
            updateTetromino(curr.currCoord.row, curr.currCoord.col - 1, curr.direction);
            break;
        case RIGHT:
            updateTetromino(curr.currCoord.row, curr.currCoord.col + 1, curr.direction);
            break;
        case DOWN:
            updateTetromino(curr.currCoord.row - 1, curr.currCoord.col, curr.direction);
            break;
        case UP:
            for (int i = 0; i < curr.currCoord.row; i++) {
                tetromino prev = copy(0);
                updateTetromino(i, curr.currCoord.col, curr.direction);
                if (curr.currCoord.row != prev.currCoord.row) {
                    break;
                }
            }
            break;
    }
}

//rotate tetromino: 1 = counterclockwise, 3 = clockwise
void rotateTetromino(int direction) {
    updateTetromino(curr.currCoord.row, curr.currCoord.col, (curr.direction + direction) % 4);
}

void hardDrop(int a) {
    _VOID;
    if (!onGround(0)) {
        moveTetromino(0);
    }
    for (int i = 0; i < 4; i++) {
        board[curr.squares[i].row][curr.squares[i].col] = curr.color;
    }
}

//returns how many lines were cleared
int clearLines(int a) {
    _VOID;
    int rowsCleared[4] = {-1, -1, -1, -1}; //list of row indices cleared
    int linesCleared = 0;
    int minRow = curr.squares[0].row;
    int maxRow = curr.squares[0].row;
    for (int i = 1; i < 4; i++) { //find range of rows covered by curr
        if (curr.squares[i].row < minRow) {
            minRow = curr.squares[i].row;
        }
        if (curr.squares[i].row > maxRow) {
            maxRow = curr.squares[i].row;
        }
    }
    for (int i = minRow; i <= maxRow; i++) { //check for lines to clear
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == BLACK) {
                break;
            }
            if (j == BOARD_WIDTH - 1) {
                rowsCleared[linesCleared++] = i;
            }
        }
    }
    if (linesCleared == 0) {
        prevRow1 = minRow;
        prevRow2 = maxRow;
        return 0;
    }
    for (int flickers = 0; flickers < 3; flickers++) {
        waitForVBlank(0);
        for (int i = 0; i < linesCleared; i++) {
            drawRectDMA(BOARD_CORNER_ROW - rowsCleared[i] * SQUARE_SIZE, BOARD_CORNER_COL, BOARD_WIDTH * SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        for(int i = 0; i < 4; i++) {
            waitForVBlank(0);
        }
        for (int i = 0; i < linesCleared; i++) {
            drawRectDMA(BOARD_CORNER_ROW - rowsCleared[i] * SQUARE_SIZE, BOARD_CORNER_COL, BOARD_WIDTH * SQUARE_SIZE, SQUARE_SIZE, BLACK);
        }
    }
    for (int i = 0; i < linesCleared; i++) {
         for (int j = 0; j < BOARD_WIDTH; j++) { //set cleared lines to black
            board[rowsCleared[i]][j] = BLACK;
        }
    }
    for (int i = minRow; i < BOARD_HEIGHT - 1; i++) { //have rows above fall down
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] != BLACK) {
                int newRow = i;
                int lineFellCount = 0;
                while (newRow != 0 && board[newRow - 1][j] == BLACK && lineFellCount <= linesCleared) {
                    board[newRow - 1][j] = board[newRow][j];
                    board[newRow][j] = BLACK;
                    newRow--;
                    lineFellCount++;
                }
            }
        }
    }
    prevRow1 = -1;
    prevRow2 = -1;
    return linesCleared;
}

void newPiece(int a) {
    _VOID;
    initTetromino(queue[0]);
    queue[0] = queue[1];
    queue[1] = queue[2];
    queue[2] = (enum shape) randint(7);
    drawQueue(0);
}

//if piece cant move any farther
bool onGround(int a) {
    _VOID;
    for (int i = 0; i < 4; i++) {
        if (curr.squares[i].row == 0 || board[curr.squares[i].row - 1][curr.squares[i].col] != BLACK) {
            return true;
        }
    }
    return false;
}

tetromino copy(int a) {
    _VOID;
    tetromino copy;
    copy.shape = curr.shape;
    copy.direction = curr.direction;
    copy.color = curr.color;
    for (int i = 0; i < 4; i++) {
        copy.squares[i].row = curr.squares[i].row;
        copy.squares[i].col = curr.squares[i].col;
    }
    copy.currCoord.row = curr.currCoord.row;
    copy.currCoord.col = curr.currCoord.col;
    return copy;
}

bool gameOver(int a) {
    _VOID;
    for (int i = 0; i < 4; i++) {
        if (board[curr.squares[i].row][curr.squares[i].col] != BLACK) {
            return true;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (board[BOARD_HEIGHT - 1][i] != BLACK) {
            return true;
        }
    }
    return false;
}

void refreshPrevRows(int a) {
    _VOID;
    if (prevRow1 != -1) {
        drawBoard(prevRow1, prevRow2);
    }
}
