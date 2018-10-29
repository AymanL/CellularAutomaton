#ifndef ETAT_H
#define ETAT_H

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include <iostream>

class StateException { //handles automaton exceptions
public:

    StateException(const std::string& message) :info(message) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};


class State { //represents a configuration of cells
    unsigned int* value; //value table of the automaton cells
    unsigned int length;
    unsigned int height;
public :

    State():value(nullptr), length(0), height(0){}
    State(unsigned int i);
    State(unsigned int i, unsigned int j);
    State(const State& e);
    State& operator=(const State& e);
    ~State(){delete [] value;}
    void setLongueur(unsigned int l){length = l;};
    void setLargeur(unsigned int l) {height = l;};
    void setCell(unsigned int i, bool val);
    void setCell(unsigned int i, unsigned int j, unsigned int val);
    bool getCell(unsigned int i) const;
    unsigned int getCell(unsigned int i, unsigned int j) const;
    unsigned int getLongueur() const {return length;}
    unsigned int getLargeur() const {return height;}
};


#endif // ETAT_H
