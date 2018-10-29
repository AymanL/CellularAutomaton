#ifndef SIMULATEUR_H
#define SIMULATEUR_H

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include "automaton.h"

//the class handles the simulation of the automaton generations
class Simulator {
    const Automaton& automaton; //automaton handled by the simulator
    State** states; //state pointers table
    const State* start; //starting state pointer
    unsigned int nbMaxstates; //max simulated states (used for the 1 dimension automaton)
    unsigned int rank;  //indicates the row we are currently simulating (1 dimension automaton)

    void build(unsigned int c); //builds the next generation
    Simulator(const Simulator& s); //copy operator
    Simulator& operator=(const Simulator& s); //affectation operator
public:

    Simulator(const Automaton& a, unsigned int buffer = 2); //class constructor, initiated with a buffer of 2 states
    Simulator(const Automaton& a, const State& dep, unsigned int buffer = 2); //class constructor, initiated with a buffer of 2 states and a starting state
    void setStartingState(const State& e);
    void run(unsigned int nbSteps); //runs the simulation nbSteps times
    void next(); //generates the next state
    const State& getLast() const; //returns te last simulated state
    unsigned int getRankLast() const { return rank; }
    void reset(); //clears grid and goes back to starting state
    ~Simulator();

};

#endif // SIMULATEUR_H
