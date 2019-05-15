#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "state.h"
#include "info.h"
#include "grid.h"
#include "textdisplay.h"

using namespace std;


Grid::~Grid() {
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
    delete this->ob;
    this->ob = ob;
}

bool Grid::isFull() const {
    for (auto &row : theGrid) {
        for (auto &c : row) {
            if (c.getInfo().colour == Colour::NoColour) return false;
        }
    }
    return true;
}

Colour Grid::whoWon() const {
    int white = 0;
    int black = 0;
    for (auto &row : theGrid) {
        for (auto &c : row) {
            if (c.getInfo().colour == Colour::White) ++white;
            else ++black;
        }
    }
    if (white > black) return Colour::White;
    else if (white < black) return Colour::Black;
    return Colour::NoColour;
}


void Grid::init(size_t n) {
    delete td;
    td = new TextDisplay{n};
    theGrid.clear();
    theGrid = vector<vector<Cell>>{n, vector<Cell>{}};
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            theGrid[r].emplace_back(r, c);
            theGrid[r][c].attach(td);
            theGrid[r][c].attach(ob);
        }
    }
    
    // default grid
    size_t med = n / 2 - 1;
    theGrid[med][med].setPiece(Colour::Black);
    theGrid[med][med+1].setPiece(Colour::White);
    theGrid[med+1][med].setPiece(Colour::White);
    theGrid[med+1][med+1].setPiece(Colour::Black);
    
    // c-1  c  c+1
    // [ ] [N] [ ] r-1
    // [W]  *  [E] r
    // [ ] [S] [ ] r+1
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            // last row
            if (r > 0) {
                // NW
                if (c > 0) theGrid[r][c].attach(&theGrid[r-1][c-1]);
                // N
                theGrid[r][c].attach(&theGrid[r-1][c]);
                // NE
                if (c < n-1) theGrid[r][c].attach(&theGrid[r-1][c+1]);
            }
            
            // current row
            // W
            if (c > 0) theGrid[r][c].attach(&theGrid[r][c-1]);
            // E
            if (c < n-1) theGrid[r][c].attach(&theGrid[r][c+1]);
            
            // next row
            if (r < n-1) {
                // SW
                if (c > 0) theGrid[r][c].attach(&theGrid[r+1][c-1]);
                // S
                theGrid[r][c].attach(&theGrid[r+1][c]);
                // SE
                if (c < n-1) theGrid[r][c].attach(&theGrid[r+1][c+1]);
            }
        }
    }
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if (!validRC(r, c)) {
        throw InvalidMove{};
    }
    theGrid[r][c].setPiece(colour);
}

void Grid::toggle(size_t r, size_t c) {
    if (!validRC(r, c)) {
        throw InvalidMove{};
    }
    
    theGrid[r][c].toggle();
}

ostream &operator<<(ostream &out, const Grid &g) {
    out << *g.td;
    return out;
}

bool Grid::validRC(size_t r, size_t c) const {
    return (0 <= r && r < theGrid.size() &&
            0 <= c && c < theGrid.size());
}
