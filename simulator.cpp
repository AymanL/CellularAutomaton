#include "Simulator.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

//the buffer is necessary during the building process since the old grid cells are needed
//to define the new states, they cannot be changed until the last cell of the new grid is defined
//therefore a buffer of a minimum of 2 states is mandatory

//class constructor, initiated with a buffer of 2 states
Simulator::Simulator(const Automaton& a, unsigned int buffer):
    automaton(a), states(nullptr), start(nullptr), nbMaxstates(buffer),rank(0) {
    states = new State*[nbMaxstates];
    for (unsigned int i = 0; i < nbMaxstates; i++) states[i] = nullptr;
}

//class constructor, initiated with a buffer of 2 states and a starting state
Simulator::Simulator(const Automaton& a, const State& dep, unsigned int buffer):
    automaton(a), states(nullptr), start(&dep), nbMaxstates(buffer),rank(0) {
    states = new State*[nbMaxstates];
    for (unsigned int i = 0; i < nbMaxstates; i++) states[i] = nullptr;
    states[0] = new State(dep);
}

void Simulator::build(unsigned int cellule) {
    if (cellule >= nbMaxstates) throw AutomatonException("buffer size error");
    if (states[cellule] == nullptr) states[cellule] = new State;
}

void Simulator::setStartingState(const State& e) {
    start = &e;
    reset();
}

void Simulator::reset() {
    if (start==nullptr) throw AutomatonException("Undefined starting state");
    build(0); *states[0] = *start;
    rank = 0;
}

void Simulator::next() {
    if (start == nullptr) throw AutomatonException("Undefined starting state");
    rank++;
    build(rank%nbMaxstates);
    automaton.transition(*states[(rank - 1) % nbMaxstates], *states[rank%nbMaxstates]);
}

//runs the simulation nbSteps times
void Simulator::run(unsigned int nb_steps) {
    for (unsigned int i = 0; i < nb_steps; i++) next();
}

//returns te last simulated state
const State& Simulator::getLast() const {
    return *states[rank%nbMaxstates];
}

//frees all the dynamically allocated states and destroys the simulator
Simulator::~Simulator() {
    for (unsigned int i = 0; i < nbMaxstates; i++) delete states[i];
    delete[] states;
}
