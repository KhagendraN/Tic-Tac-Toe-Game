#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

bool isMoveValid(int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void displayResult(char winner, char player) {
    if (winner == player) {
        printf("You win!\n");
    } else {
        printf("You lost!\n");
    }
}

void playWithComputer() {
    initializeBoard();
    srand(time(0));
    int currentPlayer = rand() % 2;
    char players[2] = {'X', 'O'};
    int row, col;
    char input[10];
    while (true) {
        printBoard();
        if (currentPlayer == 0) {
            printf("Your turn. Enter row and column (0-2): ");
            fflush(stdin);
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d %d", &row, &col) != 2 || !isMoveValid(row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = 'X';
        } else {
            printf("Computer is making a move...\n");
            int r, c;
            do {
                r = rand() % 3;
                c = rand() % 3;
            } while (!isMoveValid(r, c));
            board[r][c] = 'O';
        }
        if (checkWin(players[currentPlayer])) {
            printBoard();
            displayResult(players[currentPlayer], 'X');
            return;
        }
        if (isBoardFull()) break;
        currentPlayer = 1 - currentPlayer;
    }
    printBoard();
    printf("It's a draw!\n");
}

void playWithFriend(int isServer) {
    int sock;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    if (isServer) {
        int server_fd, new_socket;
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        bind(server_fd, (struct sockaddr*)&address, sizeof(address));
        listen(server_fd, 3);
        printf("Waiting for another player to connect...\n");
        new_socket = accept(server_fd, NULL, NULL);
        sock = new_socket;
    } else {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
        connect(sock, (struct sockaddr*)&address, sizeof(address));
    }
    
    initializeBoard();
    srand(time(0));
    int currentPlayer = rand() % 2;
    char players[2] = {'X', 'O'};
    int row, col;
    char input[10];
    while (true) {
        printBoard();
        if (currentPlayer == isServer) {
            printf("Your turn. Enter row and column (0-2): ");
            fflush(stdin);
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d %d", &row, &col) != 2 || !isMoveValid(row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = players[isServer];
            snprintf(buffer, sizeof(buffer), "%d %d", row, col);
            send(sock, buffer, strlen(buffer), 0);
            printf("You made a move. Waiting for opponent...\n");
        } else {
            printf("Waiting for opponent's move...\n");
            recv(sock, buffer, sizeof(buffer), 0);
            sscanf(buffer, "%d %d", &row, &col);
            board[row][col] = players[1 - isServer];
            printf("Opponent made a move at (%d, %d)\n", row, col);
        }
        if (checkWin(players[currentPlayer])) {
            printBoard();
            displayResult(players[currentPlayer], players[isServer]);
            close(sock);
            return;
        }
        if (isBoardFull()) break;
        currentPlayer = 1 - currentPlayer;
    }
    printBoard();
    printf("It's a draw!\n");
    close(sock);
}

int main() {
    srand(time(0));
    int choice;
    printf("1. Play with Computer\n2. Play with Friend (Localhost)\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1) {
        playWithComputer();
    } else if (choice == 2) {
        int isServer;
        printf("Enter 1 to host or 0 to join: ");
        scanf("%d", &isServer);
        getchar();
        playWithFriend(isServer);
    } else {
        printf("Invalid choice. Exiting.\n");
    }
    return 0;
}
