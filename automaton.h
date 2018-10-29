#ifndef AUTOMATE_H
#define AUTOMATE_H

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include "State.h"
#include <iostream>


//handles the automaton-related exceptions
class AutomatonException {
public:
    AutomatonException(const std::string& message) :info(message) {} //class contructor
    std::string getInfo() const { return info; } //returns the error message

private:
    std::string info;

};


class Automaton{ //abstract class representing all of the aumaton common features
public :

    virtual void transition(const State& dep, State& dest) const=0; //transitions from dep state to dest state
    virtual ~Automaton(){} //virtual destructor
};


class oneDimensionInstance: public Automaton { //1 dimension automaton
    unsigned short int numero; //integer rule
    std::string numeroBit; //binary rule

    oneDimensionInstance(const unsigned short int n); //constructs a 1 dimension automaton from its integer rule
    oneDimensionInstance(const std::string& n); //constructs a 1 dimension automaton from its binary rule
    virtual ~oneDimensionInstance(){} //destructor
    oneDimensionInstance(const oneDimensionInstance& d); //copy operator
    oneDimensionInstance& operator=(const oneDimensionInstance& d); //affectation operator

    friend class AutomatonManager; //friend declaration to allow AutomatonManager to access the 1 dimension attributes

public :
    unsigned short int getNumero() const { return numero; } //returns the automaton's integer rule
    const std::string& getNumeroBit() const { return numeroBit; } //returns the automaton's binary rule
    void transition(const State& dep, State& dest) const;

};


class gameLifeInstance: public Automaton { //Conway's game of life automaton

    unsigned int minAlive;//min number of alive neighbors for an alive cell to stay alive
    unsigned int maxAlive;//max number of alive neighbors for an alive cell to stay alive
    unsigned int minDead;//min number of alive neighbors for a dead cell to become alive
    unsigned int maxDead;//max number of alive neighbors for a dead cell to become alive

    //builds a game of life automaton from the required information
    gameLifeInstance(const unsigned int minA, const unsigned int maxA, const unsigned int minD, const unsigned int maxD ):minAlive(minA),maxAlive(maxA), minDead(minD), maxDead(maxD){}

    ~gameLifeInstance(){}
    gameLifeInstance(const gameLifeInstance& j); //copy operator

    friend class AutomatonManager;  //friend declaration to allow AutomatonManager to access the game of life attributes

public :
    //accessors
    unsigned int get_minAlive() const { return minAlive; }
    unsigned int get_maxAlive() const { return maxAlive; }
    unsigned int get_minDead() const { return minDead; }
    unsigned int get_maxDead() const { return maxDead; }

    void transition(const State& dep, State& dest) const;
};


class forestFireInstance:public Automaton {

    forestFireInstance(){}
    ~forestFireInstance(){}
    forestFireInstance(const forestFireInstance& f); //copy operator
    forestFireInstance& operator=(const forestFireInstance& f); //affectation operator

    friend class AutomatonManager; //friend declaration to allow AutomatonManager to access the forest fire automaton attributes

public :
    void transition(const State& dep, State& dest) const;
};


class AutomatonManager{ //class handling the construction and destruction of all the other automata
        bool fire; //indicates if a fire automaton has been created
        unsigned int nb; //indicates the current number of automata the manager handles
        Automaton** automatonsgen; //automaton table
        unsigned int nbMax; //max automata in the table

        AutomatonManager();
        ~AutomatonManager();
        AutomatonManager(const AutomatonManager& a); //copy operator
        AutomatonManager& operator=(const AutomatonManager& a); //affectation operator

        static AutomatonManager* instance; //singleton

    public:
        void enlargeTable(); //enlarges the automata table when it's full

        //accessors to the automata, creates them if they don't exist yet
        const Automaton& getAutomaton(unsigned short int num); //returns the automaton associated with the integer rule
        const Automaton& getAutomaton(const std::string& num); //returns the automaton associated with the binary rule
        const Automaton& getAutomaton(unsigned int i, unsigned int j, unsigned int, unsigned int); // returns the game of life automata associated with the given parameters
        const Automaton& getFireAutomaton(); //returns a reference to the adress of the fire automaton

        Automaton* findAutomaton(unsigned int num); //returns the adress of the 1 dimension automaton or null if not found
        Automaton* findAutomaton(unsigned int i, unsigned int j, unsigned int, unsigned int); //returns the adress of the game of life automaton or null if not found

        static AutomatonManager& getAutomatonManager(); //returns a reference to the singleton automatonManager
        static void freeAutomatonManager();
};

#endif
