#ifndef SIMULATEUR_H
#define SIMULATEUR_H
/*!
 * \file Simulator.h
 * \brief Permet la simulation des évolutions de génération en génération des automatons
 * \author Laure, Ayman et Caroline
 * \version 5
 */
#include "automaton.h"

/*! \class Simulator
  * \brief classe représentant le Simulator d'états
  *
  *  La classe gère la simulation des générations des automatons.
  */
class Simulator {
    const Automaton& automaton; /*!< automaton géré par le simulateur */
    Etat** states;/*!< tableau de pointeurs d'states */
    const Etat* start; /*!< pointeur sur l'Etat de start*/
    unsigned int nbMaxEtats; /*!< nombre maximum d'état, de génération */
    unsigned int rank;  /*!< indice de la génération/de l'état où on est */
    /*!
         *  \brief Construction de l'état d'une cellule
         *
         *  Methode qui permet d'alloué un etat (nul pour l'instant) à une certaine cellule,
         *  ici le numéro de la cellule est passé en paramètre.
         *
         * \param c: unsigned int, position de la cellule.
         */
    void build(unsigned int c);
    /*!
     *  \brief opérateur de recopie
     *
     *  Opérateur de recopie d'un objet simulateur.
     */
    Simulator(const Simulator& s);
    /*!
     *  \brief opérateur d'affectation
     *
     *  Opérateur d'affectation d'un objet simulateur.
     */
    Simulator& operator=(const Simulator& s);
public:
    /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe Simluateur prenant en paramètre une référence d'un automaton et
        * un buffer qui stocke un nombre maximum d'états générés.
        *
        *  \param a : const Automaton&
        *  \param buffer : unsigned int, initialisé à 2
        */
    Simulator(const Automaton& a, unsigned int buffer = 2);
    /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe Simluateur prenant en paramètre une référence d'un automaton,
        * un etat de départ et un buffer qui stocke un nombre maximum d'états générés.
        * Le constructeur est surchargé pour une variante avec un etat de départ.
        *
        *  \param a : const Automaton&
        *  \param dep : const Etat&
        *  \param buffer : unsigned int, initialisé à 2
        */
    Simulator(const Automaton& a, const Etat& dep, unsigned int buffer = 2);
    /*!
         *  \brief Fixation de l'état de départ
         *
         *  Methode qui permet de fixer l'état de départ pour l'automaton pris en charge par le simulateur.
         *
         *  \param e: const Etat&
         */
    void setEtatDepart(const Etat& e);
    /*!
         *  \brief Simulation en marche
         *
         *  Methode qui permet de générer la simulation pour un nombre spécifié d'états (de génération).
         *
         *  \param nbSteps: unsigned int
         */
    void run(unsigned int nbSteps);
    /*!
         *  \brief Etat suivant
         *
         *  Methode qui permet de générer le prochain état.
         */
    void next();
    /*!
         *  \brief Recupération du dernier Etat
         *
         *  Methode qui permet de recupérer le dernier état généré.
         *
         *  \return const Etat&: réféence du dernier état de l'automaton.
         */
    const Etat& dernier() const;
    /*!
         *  \brief Recupération de la valeur du rank du dernier Etat
         *
         *  Methode qui permet de recupérer la valeur du rank du dernier état généré.
         *
         *  \return unsigned int: valeur du rank du dernier état.
         */
    unsigned int getRangDernier() const { return rank; }
    /*!
         *  \brief Remise à zéro
         *
         *  Methode qui permet de revenir à l'état de départ.
         */
    void reset();
    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Simulator
     */
    ~Simulator();
};

#endif // SIMULATEUR_H
