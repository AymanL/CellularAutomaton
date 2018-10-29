#include "State.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

State::State(unsigned int n): height(n), length(1), value(new unsigned int[n]) {
    for (unsigned int i = 0; i < n; i++) value[i] = 0;
}

void State::setCell(unsigned int i, bool val) {
    if (i >= height) throw StateException("Cell Error");
    value[i] = val;
}

bool State::getCell(unsigned int i) const{
    if (i >= height) throw StateException("Cell Error");
    return value[i];
}

State::State(const State& e):length(e.length), height(e.height), value(new unsigned int[e.length*e.height])
{
    for (unsigned int i = 0; i < length*height; i++) value[i] = e.value[i];
}

std::ostream& operator<<(std::ostream& f, const State& e) {
    for (unsigned int i = 0; i < e.getLongueur(); i++)
        if (e.getCell(i)) f << char(178); else f << " ";
    return f;
}

State& State::operator=(const State& e) {
    if (this != &e) {
        if (height != e.height || length != e.length) {
            unsigned int* newvalue = new unsigned int[e.height*e.length];
            for (unsigned int i = 0; i < e.height*e.length; i++){
                   newvalue[i] = e.value[i];
            }
            unsigned int* old = value;
            value = newvalue;
            height = e.height;
            length = e.length;
            delete[] old;
        }
        else for (unsigned int i = 0; i < e.height*e.height; i++){
                value[i] = e.value[i];
    }
    return *this;
}
}

State::State(unsigned int n, unsigned int m):
    height(n),length(m),
        value(new unsigned int[n*m]) { //allocates a one dimension table to hold the 2 dimension cells
    for (unsigned int i = 0; i < n*m; i++){
            value[i] = 0;
    }
}

void State::setCell(unsigned int i, unsigned int j, unsigned int val) {
    if (i >= height || j >= length) throw StateException("Erreur Cellule");
    value[i + j*height] = val; // to access the (i,j) cell, on the i-th row of the j-th column, we need to fetch the i + j*height cell
                                // we suppose the cells are stored in the table line by line (0,0) then (0,1) etc... (0,n) then (1,0)
}


unsigned int State::getCell(unsigned int i, unsigned int j) const {
    if (i >= height || j >= length) throw StateException("Cell Error");
    return value[i + j*height]; //same logic
}

