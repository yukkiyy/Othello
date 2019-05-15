#include "cell.h"
#include "state.h"
#include "info.h"
#include "subject.h"
#include "grid.h"
#include <cstddef>


using namespace std;


Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
    if (this->colour != Colour::NoColour) throw InvalidMove{};
    this->colour = colour;
    setState(State{StateType::NewPiece, colour, Direction::N});
    notifyObservers();
}

void Cell::toggle() {
    if (colour == Colour::NoColour) return;
    if (colour == Colour::Black) colour = Colour::White;
    else colour = Colour::Black;
}

void Cell::notify(Subject<Info, State> &whoFrom) {

    // an empty cell does nothing
    if (colour == Colour::NoColour) return;
    
    Info info = whoFrom.getInfo();
    State state = whoFrom.getState();
    
    
    if (state.type == StateType::NewPiece) {
        // if same color, and neighbor(caller) is newPiece,
        // nothing happened
        if (info.colour == colour) return;
        
        setState(State{StateType::Relay, colour, relDir(info.row, info.col)});

    }
    else if (state.type == StateType::Relay) {
        // not in the correct direction
        if (relDir(info.row, info.col) != state.direction) return;
        
        // relay broadcast stop here, starting reply back
        if (info.colour != colour) {
            setState(State{StateType::Reply, colour, invDir(state.direction)});
        }
        else {
            // relay cell will have same state(type, color, direction) as last relay cell
            setState(state);
        }
    }
    else { // Reply
        // have backed to the NewPiece one
        if (colour == info.colour) return;
        // not in the correct direction
        if (relDir(info.row, info.col) != state.direction) return;
        
        toggle();
        // reply cell will have same state(type, color, direction) as last reply cell
        setState(state);
    }
    
    
    notifyObservers();
}

Info Cell::getInfo() const{
    return Info{r, c, colour};
}

// customized prived methods

Direction Cell::invDir(Direction d) const {
    if (d == Direction::NW) {
        return Direction::SE;
    }
    if (d == Direction::N) {
        return Direction::S;
    }
    if (d == Direction::NE) {
        return Direction::SW;
    }
    if (d == Direction::W) {
        return Direction::E;
    }
    if (d == Direction::E) {
        return Direction::W;
    }
    if (d == Direction::SW) {
        return Direction::NE;
    }
    if (d == Direction::S) {
        return Direction::N;
    }
    // d == Direction::SE
    return Direction::NW;
}


Direction Cell::relDir(size_t row, size_t col) const {
    // c<  c=  c>
    // [ ] [N] [ ] r<
    // [W]  *  [E] r=
    // [ ] [S] [ ] r>
    if (r < row && c < col) {
        return Direction::NW;
    }
    if (r < row && c == col) {
        return Direction::N;
    }
    if (r < row && c > col) {
        return Direction::NE;
    }
    if (r == row && c < col) {
        return Direction::W;
    }
    if (r == row && c > col) {
        return Direction::E;
    }
    if (r > row && c < col) {
        return Direction::SW;
    }
    if (r > row && c == col) {
        return Direction::S;
    }
    // (r > row && c > col)
    return Direction::SE;
}


