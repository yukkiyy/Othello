#include <iostream>
#include <vector>
#include <cstddef>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "cell.h"
#include "textdisplay.h"

using namespace std;


TextDisplay::TextDisplay(size_t n) : theDisplay{n, vector<char>(n, '-')}, gridSize(n)
{}




void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    State s = whoNotified.getState();
    Info i = whoNotified.getInfo();
    if (s.type == StateType::NewPiece || s.type == StateType::Reply) {
        theDisplay[i.row][i.col] = (i.colour == Colour::Black ? 'B' : 'W');
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (auto &row : td.theDisplay) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
    
    return out;
}


