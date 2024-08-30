#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIDE 3
#define EMPTY ' '
#define PLAYER 'X'
#define COMPUTER 'O'

// Function to print the board
void showBoard(const char board[][SIDE]) {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

// Function to initialize the board
void initialise(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            board[i][j] = EMPTY;
}

// Function to check for a winner
bool checkWin(const char board[][SIDE], char player) {
    for (int i = 0; i < SIDE; i++) {
        // Check rows
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        // Check columns
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// Function to check if the board is full
bool isBoardFull(const char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

// Function to get a list of empty cells
vector<pair<int, int>> getEmptyCells(const char board[][SIDE]) {
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == EMPTY) {
                emptyCells.push_back(make_pair(i, j));
            }
        }
    }
    return emptyCells;
}

// Function to make a move for the player
void playerMove(char board[][SIDE]) {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        move--;

        if (move < 0 || move >= 9) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        int x = move / SIDE;
        int y = move % SIDE;

        if (board[x][y] == EMPTY) {
            board[x][y] = PLAYER;
            break;
        } else {
            cout << "Cell already occupied. Try again." << endl;
        }
    }
}

// Function to evaluate the board state
int evaluate(const char board[][SIDE]) {
    if (checkWin(board, COMPUTER))
        return +10;
    if (checkWin(board, PLAYER))
        return -10;
    return 0;
}

// Minimax algorithm for the computer's move
int minimax(char board[][SIDE], bool isMax) {
    int score = evaluate(board);

    if (score == 10)
        return score;
    if (score == -10)
        return score;

    if (isBoardFull(board))
        return 0;

    if (isMax) {
        int best = -1000;
        vector<pair<int, int>> emptyCells = getEmptyCells(board);

        for (const auto& cell : emptyCells) {
            board[cell.first][cell.second] = COMPUTER;
            best = max(best, minimax(board, !isMax));
            board[cell.first][cell.second] = EMPTY;
        }
        return best;
    } else {
        int best = 1000;
        vector<pair<int, int>> emptyCells = getEmptyCells(board);

        for (const auto& cell : emptyCells) {
            board[cell.first][cell.second] = PLAYER;
            best = min(best, minimax(board, !isMax));
            board[cell.first][cell.second] = EMPTY;
        }
        return best;
    }
}

// Function to make a move for the computer using minimax algorithm
void computerMove(char board[][SIDE]) {
    int bestVal = -1000;
    int bestMoveRow = -1, bestMoveCol = -1;

    vector<pair<int, int>> emptyCells = getEmptyCells(board);

    for (const auto& cell : emptyCells) {
        board[cell.first][cell.second] = COMPUTER;
        int moveVal = minimax(board, false);
        board[cell.first][cell.second] = EMPTY;

        if (moveVal > bestVal) {
            bestMoveRow = cell.first;
            bestMoveCol = cell.second;
            bestVal = moveVal;
        }
    }
    board[bestMoveRow][bestMoveCol] = COMPUTER;
}

// Main function to play the game
void playTicTacToe() {
    char board[SIDE][SIDE];
    initialise(board);

    while (true) {
        showBoard(board);
        playerMove(board);
        if (checkWin(board, PLAYER)) {
            showBoard(board);
            cout << "You win!" << endl;
            return;
        }
        if (isBoardFull(board)) {
            showBoard(board);
            cout << "It's a draw!" << endl;
            return;
        }

        computerMove(board);
        if (checkWin(board, COMPUTER)) {
            showBoard(board);
            cout << "Computer wins!" << endl;
            return;
        }
        if (isBoardFull(board)) {
            showBoard(board);
            cout << "It's a draw!" << endl;
            return;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    char cont = 'y';
    while (cont == 'y') {
        playTicTacToe();
        cout << "Play again? (y/n): ";
        cin >> cont;
    }
    return 0;
}
