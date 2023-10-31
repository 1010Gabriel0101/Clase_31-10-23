#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpace();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main() {
    char winner = ' ';
    char respuesta = ' ';
    
    do {
        winner = ' ';
        respuesta = ' ';
        resetBoard();
        
        while (winner == ' ' && checkFreeSpace() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner();
            
            if (winner != ' ' || checkFreeSpace() == 0) {
                break;
            }
            
            computerMove();
            winner = checkWinner();
            
            if (winner != ' ' || checkFreeSpace() == 0) {
                break;
            }
        }
        
        printBoard();
        printWinner(winner);
        printf("\nQuieres jugar de nuevo? (Y/N): ");
        fflush(stdin); // Limpiar el búfer de entrada
        scanf(" %c", &respuesta);
        respuesta = toupper(respuesta);
    } while (respuesta == 'Y');
    
    printf("Gracias por jugar\n");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpace() {
    int freeSpaces = 9;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    
    return freeSpaces;
}

void playerMove() {
    int x, y;
    
    do {
        printf("Introduce fila #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Introduce la columna #(1-3): ");
        scanf("%d", &y);
        y--;
        
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
            printf("Movimiento no permitido\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove() {
    int x, y;
    
    if (checkFreeSpace() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
        board[x][y] = COMPUTER;
    }
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    
    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("GANASTE\n");
    } else if (winner == COMPUTER) {
        printf("PERDISTE\n");
    } else {
        printf("EMPATE\n");
    }
}
