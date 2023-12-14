#include "XO_games.h"
using namespace std;
// Set the board
X_O_Board::X_O_Board() {
    n_rows = n_cols = 3;
    board = new char* [n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}


// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}



// Display the board and the pieces on it
void X_O_Board::display_board() {
    for (int i : {0, 1, 2}) {
        cout << "\n| ";
        for (int j : {0, 1, 2}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool X_O_Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i : {0, 1, 2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i : {0, 1, 2}) {
        if ((row_win[i] && (row_win[i] == board[i][0])) ||
            (col_win[i] && (col_win[i] == board[0][i])))
        {
            return true;
        }
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
    {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over() {
    return n_moves >= 9;
}


GameManager::GameManager(Board* bPtr, Player* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {


        for (int i : {0, 1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {//index out ofrange
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()) {
                cout << players[i]->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}


RandomPlayer::RandomPlayer(char symbol, int dimension) :Player(symbol)
{
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move(int& x, int& y) {
    x = (int)(rand() / (RAND_MAX + 1.0) * dimension);
    y = (int)(rand() / (RAND_MAX + 1.0) * dimension);
}


Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player(int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string() {
    return "Player: " + name;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}


// Set the board
Pyramic::Pyramic() {
    n_rows = 3;
    n_cols = 1;
    board = new char* [n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++) {
            board[i][j] = 0;
        }
        n_cols += 2;
    }
}

bool Pyramic::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x > n_rows || y < 0 || y > n_cols) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

void Pyramic::display_board() {
    for (int i = 0; i < n_rows; i++) {
        cout << "\n";

        for (int k = 0; k < n_rows - i - 1; k++) {
            cout << "         ";
        }

        cout << "| ";

        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << "| ";
        }

        cout << "\n";


        for (int k = 0; k < n_rows - i - 1; k++) {
            cout << " ";
        }


        cout << "------------------------------------------------";

    }
    cout << "\n";
}

bool Pyramic::is_winner() {
    if (board[0][0] == board[1][1] && board[0][0] != 0) {
        if (board[1][1] == board[2][2] && board[1][1] != 0) {
            return true;
        }
    }
    else if (board[0][0] == board[1][0] && board[0][0] != 0) {
        if (board[1][0] == board[2][0] && board[1][0] != 0) {
            return true;
        }
    }
    else if (board[0][0] == board[1][2] && board[0][0] != 0) {
        if (board[1][2] == board[2][4] && board[1][2] != 0) {
            return true;
        }
    }
    else if (board[1][0] == board[1][1] && board[1][0] != 0) {
        if (board[1][1] == board[1][2] && board[1][1] != 0) {
            return true;
        }
    }
    else if (board[2][0] == board[2][1] && board[2][0] != 0) {
        if (board[2][1] == board[2][2] && board[2][1] != 0) {
            return true;
        }
    }
    else if (board[2][1] == board[2][2] && board[2][1] != 0) {
        if (board[2][2] == board[2][3] && board[2][2] != 0) {
            return true;
        }
    }
    else if (board[2][2] == board[2][3] && board[2][2] != 0) {
        if (board[2][3] == board[2][4] && board[2][3] != 0) {
            return true;
        }
    }
    return false;
}


bool Pyramic::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool Pyramic::game_is_over() {
    return n_moves >= 9;
}



Board_CONNECT4::Board_CONNECT4() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            arr[i][j] = "( " + to_string(i) + ", " + to_string(j) + " )";
        }
    }
    string checkWin = "";
}
void Board_CONNECT4::fisrtBoard() {
    cout << "This is the board, you will choose any of these places to put your symbol\n" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            cout << " " << arr[i][j] << " |";
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Now let's start the game\n" << endl;
}

void Board_CONNECT4::updateBoard(int pos1, int pos2, string symbol) {
    for (int i = 5; i >= 0; i--) {
        if (arr[i][pos2].size() > 1) {
            arr[i][pos2] = symbol;
            break;
        }
    }
}

void Board_CONNECT4::displayBoard() {
    cout << endl;
    for (int i = 0; i < 6; i++) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            if (arr[i][j].size() != 1) {
                cout << "   ";
            }
            else {
                cout << " " << arr[i][j] << " ";
            }
            cout << "|";
        }
        cout << "\n";
    }
    cout << "-----------------------------\n";
}

bool Board_CONNECT4::isWin() {
    for (int i = 0; i < 6; i++) { // check if there is horizontal line with four elements:
        checkWin = "";
        for (int j = 0; j < 7; j++) {
            checkWin += arr[i][j];
        }
        if (checkWin.find("XXXX") != string::npos || checkWin.find("OOOO") != string::npos) {
            checkWin = "";
            return true;
        }
    }

    for (int j = 0; j < 7; j++) { // check if there is vertical line with four elements:
        checkWin = "";
        for (int i = 0; i < 6; i++) {
            checkWin += arr[i][j];
        }
        if (checkWin.find("XXXX") != string::npos || checkWin.find("OOOO") != string::npos) {
            checkWin = "";
            return true;
        }
    }


    for (int i = 0; i < 3; i++) { // check diagonal lines (top-left to bottom-right)
        for (int j = 0; j < 4; j++) {
            checkWin = "";
            for (int count = 0; count < 4; count++) {
                checkWin += arr[i + count][j + count];
            }
            if (checkWin == "XXXX" || checkWin == "OOOO") {
                return true;
            }
        }
    }


    for (int i = 0; i < 3; i++) { // check diagonal lines (top-right to bottom-left)
        for (int j = 3; j < 7; j++) {
            checkWin = "";
            for (int count = 0; count < 4; count++) {
                checkWin += arr[i + count][j - count];
            }
            if (checkWin == "XXXX" || checkWin == "OOOO") {
                return true;
            }
        }
    }

    return false;
}
bool Board_CONNECT4::isGameOver() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (arr[i][j].size() > 1) {
                return false;
            }
        }
    }
    return true;
}

Players_CONNECT4::Players_CONNECT4(string n1, string n2) : Board_CONNECT4() {
    name1 = n1;
    name2 = n2;
    symbol1 = "X";
    symbol2 = "O";
    nPlayer = 1;
}
void Players_CONNECT4::run() {
    while (!isGameOver()) {
        if (nPlayer % 2 == 1) {
            cout << "Enter two positions separeted with space -> index of the place you want to put your symbol: ";
            cin >> pos1 >> pos2;
            while (pos1 > 5 || pos1 < 0 || pos2 > 6 || pos2 < 0) {
                cout << "Invalid position!\n";
                cout << "Enter two positions separeted with space -> index of the place you want to put your symbol: ";
                cin >> pos1 >> pos2;
            }
            
            updateBoard(pos1, pos2, "X");
            displayBoard();
            if (isWin()) {
                cout << name1 << " " << "wins the game\n";
                break;
            }

        }
        else {
            if (name2 != "Computer") {
                cout << "Enter two positions separeted with space (index of the place you want to put your symbol): ";
                cin >> pos1 >> pos2;
                while (pos1 > 5 || pos1 < 0 || pos2 > 6 || pos2 < 0) {
                    cout << "Invalid position!\n";
                    cout << "Enter two positions separeted with space -> index of the place you want to put your symbol: ";
                    cin >> pos1 >> pos2;
                }
                updateBoard(pos1, pos2, "O");
                displayBoard();
                if (isWin()) {
                    cout << name2 << " " << "wins the game\n";
                }
            }
            else {
                pos1 = 0 + (rand() % 6);
                pos2 = 0 + (rand() % 7);
                updateBoard(pos1, pos2, "O");
                cout << "Compter player: \n";
                displayBoard();
                if (isWin()) {
                    cout << name2 << " " << "wins the game\n";
                    break;
                }
            }
        }
        nPlayer++;

    }
}

