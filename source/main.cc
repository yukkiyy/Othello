#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;
    
    // Add code here
    bool isBlack = true;
    
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "new") {
                int n;
                cin >> n;
                // Add code here
                // omit invalid input n
                if (n < 4 || n % 2 != 0) continue;
                GraphicsDisplay *gd = new GraphicsDisplay{(size_t)n};
                g.setObserver(gd);
                g.init(n);
                isBlack = true;
                cout << g;
            }
            else if (cmd == "play") {
                int r = 0, c = 0;
                cin >> r >> c;
                // Add code here
                try {
                    if (isBlack) {
                        g.setPiece(r, c, Colour::Black);
                    }
                    else {
                        g.setPiece(r, c, Colour::White);
                    }
                    isBlack = !isBlack;
                    cout << g;
                } catch (InvalidMove &im) {
                    // ignore this move and isBlack is not changed
                }
                
                if (g.isFull()) {
                    Colour winner = g.whoWon();
                    if (winner == Colour::Black) {
                        cout << "Black wins!" << endl;
                    }
                    else if (winner == Colour::White) {
                        cout << "White wins!" << endl;
                    }
                    else {
                        cout << "Tie!" << endl;
                    }
                    // the program ends when the game is over
                    break;
                }
                
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
