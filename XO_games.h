#ifndef UNTITLED11_XO_GAME_H
#define UNTITLED11_XO_GAME_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Board {
protected:
    int n_rows, n_cols;
    char** board;
    int  n_moves = 0;

public:
    // Return true  if move is valid and put it on board
    // within board boundaries in empty cell
    // Return false otherwise
    virtual bool update_board(int x, int y, char symbol) = 0;
    // Returns true if there is any winner
    // either X or O
    // Written in a complex way. DO NOT DO LIKE THIS.
    virtual bool is_winner() = 0;
    // Return true if all moves are done and no winner
    virtual bool is_draw() = 0;
    // Display the board and the pieces on it
    virtual void display_board() = 0;
    // Return true if game is over
    virtual bool game_is_over() = 0;
};


///////////////////////////////////////////
// This class represents a 3 x 3 board
// used in X_O game
class X_O_Board :public Board {
public:
    X_O_Board();
    bool update_board(int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
};

///////////////////////////////////////////
class Pyramic :public Board {
public:
    Pyramic();
    bool update_board(int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();

};


///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
protected:
    string name;
    char symbol;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player(char symbol); // Needed for computer players
    Player(int order, char symbol);
    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
};


///////////////////////////////////////////
// This class represents a random computer player
// that generates random positions x y (0 to 2)
// If invalid, game manager asks to regenerate
class RandomPlayer : public Player {
protected:
    int dimension;
public:
    // Take a symbol and pass it to parent
    RandomPlayer(char symbol, int dimension);
    // Generate a random move
    void get_move(int& x, int& y);
};


///////////////////////////////////////////
class GameManager {
private:
    Board* boardPtr;
    Player* players[2];
public:
    GameManager(Board*, Player* playerPtr[2]);
    void run();
    // This method creates board and players
    // It displays board
    // While True
    //   For each player
    //      It takes a valid move as x, y pair (between 0 - 2)
    //      It updates board and displays otit
    //      If winner, declare so and end
    //      If draw, declare so and end

};


#endif //UNTITLED11_XO_GAME_H


class Board_CONNECT4 {
protected:
	string checkWin;
	string arr[6][7];
public:
	Board_CONNECT4(); // default constructor to assign the board with indices
	virtual void fisrtBoard();
	virtual void updateBoard(int pos1, int pos2, string symbol);
	virtual void displayBoard();
	virtual bool isWin();
	virtual bool isGameOver();

};
class Players_CONNECT4 : public Board_CONNECT4 {
protected:
	string name1, name2, symbol1, symbol2;
	int nPlayer, pos1, pos2;
public:
	Players_CONNECT4(string n1, string n2);
	void run();
};
/*

int main() {
	cout << "********************************" << endl;
	cout << "WELCOME TO CONNECT FOUR GAME\n";
	cout << "********************************" << endl;
	cout << "Please, enter your name as player one: ";
	string name1, name2 = "Computer";
	cin >> name1;
	cout << "If you want to play with a friend enter 1\nIf you want to play with the computer enter 0\n";
	int chosen;
	cin >> chosen;
	if (chosen == 1) {
		cout << "Please, enter the name of your friend as player two: ";
		cin >> name2;

		Board_CONNECT4* p = new Players_CONNECT4(name1, name2);
		p->fisrtBoard();
		((Players_CONNECT4*)p)->run();
	}
	else if (chosen == 0) {
		Board_CONNECT4* p = new Players_CONNECT4(name1, name2);
		p->fisrtBoard();
		((Players_CONNECT4*)p)->run();
	}
}









*/