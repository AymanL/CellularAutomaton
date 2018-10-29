#include "automaton.h"
/*!
 * \file automaton.cpp
 * \brief Programme de definition de méthodes des différents automatons.
 * \author Laure, Ayman et Caroline
 * \version 5
 */


short unsigned int NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomatonException("Numero d'automaton indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomatonException("Numero d'automaton indefini");
        puissance *= 2;
    }
    return numero;
}

std::string NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomatonException("Numero d'automaton indefini");
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

Dimension1::Dimension1(unsigned short int num):numero(num),numeroBit(NumToNumBit(num)){
}

Dimension1::Dimension1(const std::string& num) :numero(NumBitToNum(num)),numeroBit(num) {
}


void Dimension1::transition(const Etat& dep, Etat& dest) const {
    if (dep.getLargeur() != dest.getLargeur()) dest = dep;
    for (unsigned int i = 0; i < dep.getLargeur(); i++) {
        unsigned short int conf=0;
        if (i > 0) conf+=dep.getCellule(i - 1) * 4;
        conf+=dep.getCellule(i)*2;
        if (i < dep.getLargeur()-1) conf+=dep.getCellule(i + 1);
        dest.setCellule(i, numeroBit[7-conf]-'0');
    }
}

AutomatonManager::AutomatonManager(): nb(1), feu(false), nbMax(256), automatonsgen(new Automaton*[256]) {
    for (unsigned int i = 0; i < 256; i++) automatonsgen[i] = nullptr;
}

AutomatonManager::~AutomatonManager() {
    //for (unsigned int i = 0; i < 256; i++) delete automatons[i];
    //for(unsigned int i=0; i<15; i++) delete automatonsVie[i];
    for (unsigned int i = 0; i < nbMax; i++) delete automatonsgen[i];

}

AutomatonManager* AutomatonManager::instance = nullptr;

AutomatonManager& AutomatonManager::getAutomatonManager() {
    if (!instance) instance = new AutomatonManager;
    return *instance;
}

void AutomatonManager::freeAutomatonManager() {
    delete instance;
    instance = nullptr;
}


const Automaton& AutomatonManager::getAutomaton(unsigned short int num) {
    Automaton* pt = findAutomaton(num);

        if (pt==nullptr){
            if(nb==nbMax) AgrandirTableau();
            automatonsgen[nb] = new Dimension1(num);
            nb++;
            return *automatonsgen[(nb-1)];
        }
        else return *pt;
}

const Automaton& AutomatonManager::getAutomaton(unsigned int i, unsigned int j, unsigned int k, unsigned int l) {
    Automaton* pt = findAutomaton(i,j,k,l);

        if(pt==nullptr){
            if(nb==nbMax) AgrandirTableau();
            automatonsgen[nb] = new JeuDeLaVie(i,j,k,l);
            nb++;
            return *automatonsgen[(nb-1)];
        }
        else return *pt;
}

void JeuDeLaVie::transition(const Etat& dep, Etat& dest) const{
    if (dep.getLongueur() != dest.getLongueur()) dest = dep;
      for (unsigned int i = 0; i < dep.getLongueur(); i++) {
         for(unsigned int j = 0; j<dep.getLargeur(); j++){
            unsigned short int conf=0;
            // récupération des neighbors directs
            if (i != 0) conf+=dep.getCellule(j,i-1);
            if (j != 0) conf+=dep.getCellule(j-1,i);
            if (i != dep.getLongueur()-1) conf+=dep.getCellule(j,i+1);
            if (j != dep.getLargeur()-1) conf+= dep.getCellule(j+1,i);

            //récupération des neighbors dans les coins
            if (i != 0 && j != 0) conf+=dep.getCellule(j-1,i-1);
            if (i != 0 && j != dep.getLargeur()-1) conf+=dep.getCellule(j+1,i-1);
            if (i != dep.getLongueur()-1 && j != 0) conf+=dep.getCellule(j-1,i+1);
            if (i != dep.getLongueur()-1 && j != dep.getLargeur()-1) conf+=dep.getCellule(j+1,i+1);

            //bool value;
            unsigned int value;
            if(dep.getCellule(j,i)){
                    if (conf<get_minAlive() || conf>get_maxAlive()) value=0;
                    else value=1;
            }
            else{
                if (conf<get_minDead() || conf>get_maxDead()) value=0;
                else value=1;
            }
            dest.setCellule(j, i , value );
         }
    }
}

const Automaton& AutomatonManager::getFireAutomaton(){
    if(!feu) automatonsgen[0] = new forestFireInstance();
    return *automatonsgen[0];
}

void forestFireInstance::transition(const Etat& dep, Etat& dest) const{
    if (dep.getLongueur() != dest.getLongueur()) dest = dep;
unsigned int value=1;

   for (unsigned int i = 0; i < dep.getLongueur(); i++) {
        for(unsigned int j = 0; j<dep.getLargeur(); j++){

            if(dep.getCellule(j,i)==0) value=0;
            if(dep.getCellule(j,i)==3) value=3;
            if(dep.getCellule(j,i)==2) value=3;
            if(dep.getCellule(j,i)==1){
                if((j!=0)&&(dep.getCellule(j-1,i)==2)) value=2;
                else if((i!=0)&&(dep.getCellule(j,i-1)==2)) value=2;
                else if((i!= dep.getLongueur()-1)&& dep.getCellule(j,i+1)==2) value=2;
                else if((j!= dep.getLargeur()-1)&& dep.getCellule(j+1,i)==2) value=2;
                else value=1;
            }
        dest.setCellule(j, i , value );
        }
    }
}

Automaton* AutomatonManager::findAutomaton(unsigned int num){
    for(unsigned int i=1; i<nb;i++){
        Dimension1* pt = dynamic_cast<Dimension1*>(automatonsgen[i]);
        if(pt && pt->getNumero()==num){
            return automatonsgen[i];
        }
    }
    return nullptr;
}

Automaton* AutomatonManager::findAutomaton(const unsigned int minA, const unsigned int maxA, const unsigned int minM, const unsigned int maxM ){
    for(unsigned int i=1; i<nb;i++){
        JeuDeLaVie* pt = dynamic_cast<JeuDeLaVie*>(automatonsgen[i]);
        if(pt && pt->get_minDead()==minM && pt->get_maxDead()==maxM && pt->get_minAlive()==minA && pt->get_maxAlive()==maxA){
            return automatonsgen[i];
        }
    }
    return nullptr;
}
void AutomatonManager::AgrandirTableau(){
        Automaton** newtab= new Automaton*[nbMax+50];
        for(unsigned int i=0; i<nbMax; i++){
            newtab[i] = automatonsgen[i];
        }
        Automaton** old = automatonsgen;
        automatonsgen = newtab;
        nbMax += 50;
        delete[] old;
}
