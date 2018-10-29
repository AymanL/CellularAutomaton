#ifndef AUTOMATE_H
#define AUTOMATE_H
/*!
 * \file automaton.h
 * \brief Les trois automatons cellulaires de notre projet
 * \author Laure, Ayman et Caroline
 * \version 5
 */
#include "Etat.h"
#include <iostream>

/*! \class AutomatonException
   * \brief classe representant la gestion des exceptions d'Automatons
   *
   *  La classe gere l'appel d'une exception après rencontre d'une erreur dans des methodes ou fonctions traitant des automatons.
   */
class AutomatonException {
public:
    /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe AutomatonException
        *
        *  \param message : message qui sera afficher lors d'une rencontre d'une erreur.
        */
    AutomatonException(const std::string& message) :info(message) {}
    /*!
         *  \brief REcupération du message
         *
         *  Methode qui permet de recupérer l'attribut info qui est le message à afficher
         *
         *  \return info: chaine de caractère consistant au message d'erreur
         */
    std::string getInfo() const { return info; }
private:
    std::string info;/*!< message d'erreur */
};


/*! \class Automaton
   * \brief classe abstraite representant les automatons en général.
   *
   *  La classe gère les méthodes partagées par tout type d'automaton
   */
class Automaton{
public :

    /*!
         *  \brief Transition entre deux états
         *
         *  Methode qui permet le passage d'un état à un autre (une génération à la suivante).
         * Cette méthode est une méthode virtuelle pure.
         */
    virtual void transition(const Etat& dep, Etat& dest) const=0;
    /*!
     *  \brief Destructeur virtuel
     *
     *  Destructeur virtuel de la classe abstraite Automaton
     */
    virtual ~Automaton(){}
};

/*! \class Dimension1
   * \brief classe  representant les automatons à une dimension.
   *
   *  La classe gère la création de l'objet automaton une dimension.
   */
class Dimension1: public Automaton {
    unsigned short int numero;/*!< numero de la règle de l'automaton (de type entier) */
    std::string numeroBit;/*!< numero de la règle de l'automaton (de type string(bit)) */
    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe Dimension1 avec un numero de règle en entier
      *
      *  \param n : unsigned short int
      */
    Dimension1(const unsigned short int n);
    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe Dimension1 avec un numero de règle en bit
      *
      *  \param n : string&
      */
    Dimension1(const std::string& n);
    /*!
     *  \brief Destructeur virtuel
     *
     *  Destructeur virtuel de la classe Dimension1
     */
    virtual ~Dimension1(){}
    /*!
     *  \brief opérateur de recopie
     *
     *  Opérateur de recopie d'un automaton une dimension.
     */
    Dimension1(const Dimension1& d);
    /*!
     *  \brief Opérateur d'affectation
     *
     *  Opérateur d'affectation surchargé pour affecter des automatons une dimension entre eux.
     */
    Dimension1& operator=(const Dimension1& d);
    /*!
     *  \brief Déclaration d'amitié
     *
     *  Déclaration d'amitié avec la classe AutomatonManager, ce qui permet à la classe
     * AutomatonManager d'acceder aux attributs de cette classe.
     */
    friend class AutomatonManager;
public :
    /*!
         *  \brief Recupération du numero (type entier)
         *
         *  Methode qui permet de recupérer l'attribut numero de type entier
         *
         *  \return numero: numero de la règle de l'automaton
         */
    unsigned short int getNumero() const { return numero; }
    /*!
         *  \brief Recupération du numero (type string, bit)
         *
         *  Methode qui permet de recupérer l'attribut numero de type string
         *
         *  \return numero: numero de la règle de l'automaton en Bit
         */
    const std::string& getNumeroBit() const { return numeroBit; }
    /*!
         *  \brief Transition entre deux états
         *
         *  Methode qui permet le passage d'un état à un autre (une génération à la suivante)
         *  pour les automatons une dimension.
         */
    void transition(const Etat& dep, Etat& dest) const;
};

/*! \class JeuDeLaVie
   * \brief classe  representant les automatons du Jeu de La Vie de John Horton Conway..
   *
   *  La classe gère la création de l'objet Jeu de La Vie.
   */

class JeuDeLaVie: public Automaton {

    unsigned int minAlive;/*!< nombre minimum de cellule voisine vivante pour rester en vie si la cellule est vivant */
    unsigned int maxAlive;/*!< nombre maximum de cellule voisine vivante pour rester en vie si la cellule est vivant */
    unsigned int minDead;/*!< nombre minimum de cellule voisine vivante pour rester en vie si la cellule est Deade*/
    unsigned int maxDead;/*!< nombre maximum de cellule voisine vivante pour rester en vie si la cellule est Deade */

    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe JeuDeLaVie
      *
      *  \param minA, maxA, minM, maxM : unsigned int
      */
    JeuDeLaVie(const unsigned int minA, const unsigned int maxA, const unsigned int minM, const unsigned int maxM ):minAlive(minA),maxAlive(maxA), minDead(minM), maxDead(maxM){}
    /*!
     *  \brief Destructeur virtuel
     *
     *  Destructeur virtuel de la classe JeuDeLaVie
     */
    ~JeuDeLaVie(){}
    /*!
     *  \brief opérateur de recopie
     *
     *  Opérateur de recopie d'un automaton jeu de la vie.
     */
    JeuDeLaVie(const JeuDeLaVie& j);
    /*!
     *  \brief Opérateur d'affectation
     *
     *  Opérateur d'affectation surchargé pour affecter des automatons deux dimensions, jeu de la vie entre eux.
     */
    JeuDeLaVie& operator=(const JeuDeLaVie& j);
    /*!
     *  \brief Déclaration d'amitié
     *
     *  Déclaration d'amitié avec la classe AutomatonManager, ce qui permet à la classe
     * AutomatonManager d'acceder aux attributs de cette classe.
     */
    friend class AutomatonManager;
public :
    /*!
         *  \brief Recupération du nombre minAlive
         *
         *  Methode qui permet de recupérer nombre minimum de cellule voisine vivante
         * pour rester en vie si la cellule est vivant
         *
         *  \return minAlive: unsigned int
         */
    unsigned int get_minAlive() const { return minAlive; }
    /*!
         *  \brief Recupération du nombre maxAlive
         *
         *  Methode qui permet de recupérer nombre maximum de cellule voisine vivante
         * pour rester en vie si la cellule est vivant
         *
         *  \return maxAlive: unsigned int
         */
    unsigned int get_maxAlive() const { return maxAlive; }
    /*!
         *  \brief Recupération du nombre minDead
         *
         *  Methode qui permet de récuperer le nombre minimum de cellule voisine vivante
         * pour rester en vie si la cellule est Deade.
         *
         *  \return minDead: unsigned int
         */
    unsigned int get_minDead() const { return minDead; }
    /*!
         *  \brief Recupération du nombre maxDead
         *
         *  Methode qui permet de récuperer le nombre maximum de cellule voisine vivante
         * pour rester en vie si la cellule est Deade.
         *
         *  \return maxDead: unsigned int
         */
    unsigned int get_maxDead() const { return maxDead; }
    /*!
         *  \brief Transition entre deux états
         *
         *  Methode qui permet le passage d'un état à un autre (une génération à la suivante)
         *  pour les automatons du jeu de la vie.
         */
    void transition(const Etat& dep, Etat& dest) const;
};


/*! \class forestFireInstance
   * \brief classe  representant les automatons d'une Forest prenant feu.
   *
   *  La classe gère la création de l'objet Forest prenant feu.
   */
class forestFireInstance:public Automaton {
    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe forestFireInstance
      */
    forestFireInstance(){}
    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe forestFireInstance
     */
    ~forestFireInstance(){}
    /*!
     *  \brief opérateur de recopie
     *
     *  Opérateur de recopie d'un automaton D'un feu de forêt.
     */
    forestFireInstance(const forestFireInstance& f);
    /*!
     *  \brief Opérateur d'affectation
     *
     *  Opérateur d'affectation surchargé pour affecter des automatons de feu de forêt entre eux.
     */
    forestFireInstance& operator=(const forestFireInstance& f);
    /*!
     *  \brief Déclaration d'amitié
     *
     *  Déclaration d'amitié avec la classe AutomatonManager, ce qui permet à la classe
     * AutomatonManager d'acceder aux attributs de cette classe.
     */
    friend class AutomatonManager;
public :
    /*!
         *  \brief Transition entre deux états
         *
         *  Methode qui permet le passage d'un état suivant dans l'avancé du feu dans notre forêt.
         */
    void transition(const Etat& dep, Etat& dest) const;
};


/*! \class AutomatonManager
   * \brief classe qui manage tous les automatons crées.
   *
   *  La classe gère les automatons crées dans l'application.
   */
class AutomatonManager{
        bool feu; /*! booléen pour savoir si l'on a créé un automaton pour le feu de forêt */
        unsigned int nb; /*!< nombre d'automaton que l'Automatonmanager manage */
        Automaton** automatonsgen; /*!< tableau remplit de pointeur d'automaton */
        unsigned int nbMax;/*!< nombre ;ax dans tableau */
        /*!
          *  \brief Constructeur
          *
          *  Constructeur de la classe AutomatonManager
          */
        AutomatonManager();
        /*!
          *  \brief Destructeur
          *
          *  Destructeur de la classe AutomatonManager
          */
        ~AutomatonManager();
        /*!
         *  \brief opérateur de recopie
         *
         *  Opérateur de recopie d'un automatonManager.
         */
        AutomatonManager(const AutomatonManager& a);
        /*!
         *  \brief opérateur d'affectation
         *
         *  Opérateur d'affectation d'un automatonManager.
         */
        AutomatonManager& operator=(const AutomatonManager& a);
        static AutomatonManager* instance;/*!< singleton */
    public:
        void AgrandirTableau();
        /*!
             *  \brief Recupération d'un automaton une dimension
             *
             *  Methode qui permet de récuperer un automaton une dimension qui a la règle num (entier)
             *
             *  \param num : unsigned short int
             *  \return const Automaton&
             */
        const Automaton& getAutomaton(unsigned short int num);
        /*!
             *  \brief Recupération d'un automaton une dimension
             *
             *  Methode qui permet de récuperer un automaton une dimension qui a la règle num (bit)
             *
             *  \param num : const string&
             *  \return const Automaton&
             */
        const Automaton& getAutomaton(const std::string& num);
        /*!
             *  \brief Recupération d'un automaton jeu de la vie
             *
             *  Methode qui permet de récuperer un automaton jeu de la vie
             * qui a les nombres spécifiques des neighbors vivants, ...,  passé en paramètre
             *
             *  \param i, j : unsigned int
             *  \return const Automaton&
             */
        const Automaton& getAutomaton(unsigned int i, unsigned int j, unsigned int, unsigned int);
        /*!
             *  \brief Recupération d'un automaton Feu de Forêt
             *
             *  Methode qui permet de récuperer un automaton feu de forêt
             *
             *  \return const Automaton&
             */
        const Automaton& getFireAutomaton();
        /*!
             *  \brief Recupération d'un automaton
             *
             *  Methode qui permet de récuperer l'adresse d'un automaton en fonction de sa règle.
             *
             * \param num : unsigned int
             *  \return Automaton* : adresse de l'automaton trouvé
             */
        Automaton* findAutomaton(unsigned int num);
        /*!
             *  \brief Recupération d'un automaton
             *
             *  Methode qui permet de récuperer l'adresse d'un automaton 2d
             *
             * \param i, j : unsigned int
             *  \return Automaton* : adresse de l'automaton trouvé
             */
        Automaton* findAutomaton(unsigned int i, unsigned int j, unsigned int, unsigned int);
        /*!
             *  \brief Recupération du singleton automatonManager
             *
             *  \return static AutomatonManager&
             */
        static AutomatonManager& getAutomatonManager();
        /*!
             *  \brief Libération du singleton AutomatonManager
             */
        static void freeAutomatonManager();
};

#endif
