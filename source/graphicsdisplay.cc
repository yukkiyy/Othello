#include "graphicsdisplay.h"
#include "window.h"


#include <iostream>
#include <vector>
#include <cstddef>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "cell.h"

using namespace std;


GraphicsDisplay::GraphicsDisplay(size_t n) : gridSize(n), cubeSize(500/gridSize) {
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            w.fillRectangle(c * cubeSize, r * cubeSize, cubeSize, cubeSize, Xwindow::Blue);
        }
    }
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
    State s = whoNotified.getState();
    Info i = whoNotified.getInfo();
    if (s.type == StateType::NewPiece || s.type == StateType::Reply) {
        if (i.colour == Colour::Black) {
            w.fillRectangle(i.col * cubeSize, i.row * cubeSize, cubeSize, cubeSize, Xwindow::Black);
        }
        else {
            w.fillRectangle(i.col * cubeSize, i.row * cubeSize, cubeSize, cubeSize, Xwindow::White);
        }
    }
}
