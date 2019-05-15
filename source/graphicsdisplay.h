#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"

class Cell;

class GraphicsDisplay: public Observer<Info, State> {
    Xwindow w;
    const size_t gridSize;
    const size_t cubeSize;
public:
    GraphicsDisplay(size_t n);
    
    void notify(Subject<Info, State> &whoNotified) override;
};
#endif
