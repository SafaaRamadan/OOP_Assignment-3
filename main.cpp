#include "XO_games.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Welcome to FCAI X-O Games :)\n";
    cout << "Choose a game: \n"
        "1- XO game(3x3)\n2- Pyramic Tic-Tac-Toe\n3- Connect-Four game\n";
    int choice2;
    cin >> choice2;
    if (choice2 == 1) {
        int choice;
        Player* players[2];
        players[0] = new Player(1, 'x');

        cout << "Press 1 if you want to play with computer: ";
        cin >> choice;
        if (choice != 1)
            players[1] = new Player(2, 'o');
        else
            //Player pointer points to child
            players[1] = new RandomPlayer('o', 3);
        GameManager x_o_game(new X_O_Board(), players);
        x_o_game.run();
        system("pause");
    }
    else if (choice2 == 2) {
        int choice;
        Player* players[2];
        players[0] = new Player(1, 'x');

        cout << "Press 1 if you want to play with computer: ";
        cin >> choice;
        if (choice != 1)
            players[1] = new Player(2, 'o');
        else
            //Player pointer points to child
            players[1] = new RandomPlayer('o', 3);
        GameManager pyramic(new Pyramic(), players);
        pyramic.run();
        system("pause");
    }
    else if (choice2 == 3) {
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
}

