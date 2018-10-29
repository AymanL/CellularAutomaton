#include "automaton.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */


short unsigned int NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomatonException("Undefined Automaton Rule");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomatonException("Undefined Automaton Rule");
        puissance *= 2;
    }
    return numero;
}

std::string NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomatonException("Undefined Automaton Rule");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) {
            numeroBit.push_back('1');
            num -= p;
        }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;

}

oneDimensionInstance::oneDimensionInstance(unsigned short int num):numero(num),numeroBit(NumToNumBit(num)){}

oneDimensionInstance::oneDimensionInstance(const std::string& num) :numero(NumBitToNum(num)),numeroBit(num) {}


void oneDimensionInstance::transition(const State& dep, State& dest) const {
    if (dep.getLargeur() != dest.getLargeur()) dest = dep;
    for (unsigned int i = 0; i < dep.getLargeur(); i++) {
        unsigned short int conf=0;
        if (i > 0) conf+=dep.getCell(i - 1) * 4;
        conf+=dep.getCell(i)*2;
        if (i < dep.getLargeur()-1) conf+=dep.getCell(i + 1);
        dest.setCell(i, numeroBit[7-conf]-'0');
    }
}

//AutomatonManger initiation
AutomatonManager::AutomatonManager(): nb(1), fire(false), nbMax(256), automatonsgen(new Automaton*[256]) {
    for (unsigned int i = 0; i < 256; i++) automatonsgen[i] = nullptr;
}

//Automaton manager destruction, destructs all of the handled automata
AutomatonManager::~AutomatonManager() {
    for (unsigned int i = 0; i < nbMax; i++) delete automatonsgen[i];

}

//singleton
AutomatonManager* AutomatonManager::instance = nullptr;

AutomatonManager& AutomatonManager::getAutomatonManager() {
    if (!instance) instance = new AutomatonManager;
    return *instance;
}

void AutomatonManager::freeAutomatonManager() {
    delete instance;
    instance = nullptr;
}


//searches for and returns the automaton associated with the integer rule
const Automaton& AutomatonManager::getAutomaton(unsigned short int num) {
    Automaton* pt = findAutomaton(num);

        if (pt==nullptr){
            if(nb==nbMax) enlargeTable();
            automatonsgen[nb] = new oneDimensionInstance(num);
            nb++;
            return *automatonsgen[(nb-1)];
        }
        else return *pt;
}

//searches for and returns the game of life automaton associated with the given parameters
const Automaton& AutomatonManager::getAutomaton(unsigned int i, unsigned int j, unsigned int k, unsigned int l) {
    Automaton* pt = findAutomaton(i,j,k,l);

        if(pt==nullptr){
            if(nb==nbMax) enlargeTable();
            automatonsgen[nb] = new gameLifeInstance(i,j,k,l);
            nb++;
            return *automatonsgen[(nb-1)];
        }
        else return *pt;
}

//counts the neighbors and gives the next generation state for each cell
void gameLifeInstance::transition(const State& dep, State& dest) const{
    if (dep.getLongueur() != dest.getLongueur()) dest = dep;
      for (unsigned int i = 0; i < dep.getLongueur(); i++) {
         for(unsigned int j = 0; j<dep.getLargeur(); j++){
            unsigned short int conf=0;
            // direct neighbors
            if (i != 0) conf+=dep.getCell(j,i-1);
            if (j != 0) conf+=dep.getCell(j-1,i);
            if (i != dep.getLongueur()-1) conf+=dep.getCell(j,i+1);
            if (j != dep.getLargeur()-1) conf+= dep.getCell(j+1,i);

            // corner neighbors
            if (i != 0 && j != 0) conf+=dep.getCell(j-1,i-1);
            if (i != 0 && j != dep.getLargeur()-1) conf+=dep.getCell(j+1,i-1);
            if (i != dep.getLongueur()-1 && j != 0) conf+=dep.getCell(j-1,i+1);
            if (i != dep.getLongueur()-1 && j != dep.getLargeur()-1) conf+=dep.getCell(j+1,i+1);

            //bool value;
            unsigned int value;
            if(dep.getCell(j,i)){
                    if (conf<get_minAlive() || conf>get_maxAlive()) value=0;
                    else value=1;
            }
            else{
                if (conf<get_minDead() || conf>get_maxDead()) value=0;
                else value=1;
            }
            dest.setCell(j, i , value );
         }
    }
}

//returns a reference to the adress of the fire automaton, creates it if it doesn't exist
const Automaton& AutomatonManager::getFireAutomaton(){
    if(!fire) automatonsgen[0] = new forestFireInstance();
    return *automatonsgen[0];
}

//if a cell is empty it stays empty
//if a cell is on fire it becomes ash
//if a cell is occupied by a tree and is near a fire, it lights up
void forestFireInstance::transition(const State& dep, State& dest) const{
    if (dep.getLongueur() != dest.getLongueur()) dest = dep;
unsigned int value=1;

   for (unsigned int i = 0; i < dep.getLongueur(); i++) {
        for(unsigned int j = 0; j<dep.getLargeur(); j++){

            if(dep.getCell(j,i)==0) value=0;
            if(dep.getCell(j,i)==3) value=3;
            if(dep.getCell(j,i)==2) value=3;
            if(dep.getCell(j,i)==1){
                if((j!=0)&&(dep.getCell(j-1,i)==2)) value=2;
                else if((i!=0)&&(dep.getCell(j,i-1)==2)) value=2;
                else if((i!= dep.getLongueur()-1)&& dep.getCell(j,i+1)==2) value=2;
                else if((j!= dep.getLargeur()-1)&& dep.getCell(j+1,i)==2) value=2;
                else value=1;
            }
        dest.setCell(j, i , value );
        }
    }
}

//returns the adress of the 1 dimension automaton or null if not found
Automaton* AutomatonManager::findAutomaton(unsigned int num){
    for(unsigned int i=1; i<nb;i++){
        oneDimensionInstance* pt = dynamic_cast<oneDimensionInstance*>(automatonsgen[i]);
        if(pt && pt->getNumero()==num){
            return automatonsgen[i];
        }
    }
    return nullptr;
}

//returns the adress of the game of life automaton or null if not found
Automaton* AutomatonManager::findAutomaton(const unsigned int minA, const unsigned int maxA, const unsigned int minD, const unsigned int maxD ){
    for(unsigned int i=1; i<nb;i++){
        gameLifeInstance* pt = dynamic_cast<gameLifeInstance*>(automatonsgen[i]);
        if(pt && pt->get_minDead()==minD && pt->get_maxDead()==maxD && pt->get_minAlive()==minA && pt->get_maxAlive()==maxA){
            return automatonsgen[i];
        }
    }
    return nullptr;
}

//enlarges the table if full by creating a new one and migrating the values from the old one
void AutomatonManager::enlargeTable(){
        Automaton** newtab= new Automaton*[nbMax+50];
        for(unsigned int i=0; i<nbMax; i++){
            newtab[i] = automatonsgen[i];
        }
        Automaton** old = automatonsgen;
        automatonsgen = newtab;
        nbMax += 50;
        delete[] old;
}
