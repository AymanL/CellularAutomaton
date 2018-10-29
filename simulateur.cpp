#include "Simulator.h"
/*!
 * \file Simulator.cpp
 * \brief Programme de definition des déclarations faites dans le fichier Simulator.h.
 * \author Laure, Ayman et Caroline
 * \version 5
 */

Simulator::Simulator(const Automaton& a, unsigned int buffer):
    automaton(a), states(nullptr), start(nullptr), nbMaxEtats(buffer),rank(0) {
    states = new Etat*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++) states[i] = nullptr;
}

Simulator::Simulator(const Automaton& a, const Etat& dep, unsigned int buffer):
    automaton(a), states(nullptr), start(&dep), nbMaxEtats(buffer),rank(0) {
    states = new Etat*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++) states[i] = nullptr;
    states[0] = new Etat(dep);
}

void Simulator::build(unsigned int cellule) {
    if (cellule >= nbMaxEtats) throw AutomatonException("erreur taille buffer");
    if (states[cellule] == nullptr) states[cellule] = new Etat;
}

void Simulator::setEtatDepart(const Etat& e) {
    start = &e;
    reset();
}

void Simulator::reset() {
    if (start==nullptr) throw AutomatonException("etat start indefini");
    build(0); *states[0] = *start;
    rank = 0;
}

void Simulator::next() {
    if (start == nullptr) throw AutomatonException("etat start indefini");
    rank++;
    build(rank%nbMaxEtats);
    automaton.transition(*states[(rank - 1) % nbMaxEtats], *states[rank%nbMaxEtats]);
}

void Simulator::run(unsigned int nb_steps) {
    for (unsigned int i = 0; i < nb_steps; i++) next();
}

const Etat& Simulator::dernier() const {
    return *states[rank%nbMaxEtats];
}

Simulator::~Simulator() {
    for (unsigned int i = 0; i < nbMaxEtats; i++) delete states[i];
    delete[] states;
}
