#ifndef AUTOCELL2D
#define AUTOCELL2D

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>
#include "Simulator.h"
#include "xml_dom.h"

//gameLife represents the interface of Conway's game of life, the class handles the widgets and slots of the interface
class gameLife : public QWidget{

    friend class MainWindow; //friend declaration so the main window can access the attributes of the gameLife widget
    Q_OBJECT

    //interface variable holders and labels
    QLabel* title;
    QComboBox* configSpe;
    QLabel* configSpel;
    QLabel* numAlivel[2];
    QLineEdit* numViv[2];
    QLabel* diml[2];
    QSpinBox* dim[2];
    QLabel* numDeadl[2];
    QLineEdit* numDead[2];
    QSpinBox* step;
    QLabel* stepl;
    QTableWidget* start;
    QTableWidget* states;
    QIntValidator* neighbors[2];

    //interface layout
    QVBoxLayout* configSpec;
    QVBoxLayout* dimc;
    QVBoxLayout* stepc;
    QVBoxLayout* numMinMax[2];
    QVBoxLayout* numMax[2];
    QHBoxLayout* parameters;
    QVBoxLayout* layer;
    QHBoxLayout* startC;
    QHBoxLayout* buttons[2];
    QTimer *timer;

    // interface variables
    unsigned int length; // number of columns
    unsigned int height; //number of rows
    unsigned int minA; //min number of alive neighbors for an alive cell to stay alive
    unsigned int maxA; //max number of alive neighbors for an alive cell to stay alive
    unsigned int minD; //min number of alive neighbors for a dead cell to become alive
    unsigned int maxD; //max number of alive neighbors for a dead cell to become alive
    unsigned int size=500; //pixel size of the grid
    unsigned int speed; //speed at which the simulation goes

    // interface buttons
    QPushButton* simulation;
    QPushButton* randomButton;
    QPushButton* change;
    QPushButton* simulAuto;
    QPushButton* stopSimulAuto;
    QPushButton* empty;
    QPushButton* configSpeB;

public:
    explicit gameLife(QWidget* parent = nullptr); //class constructor

private slots:
    void cellActivation(const QModelIndex& index); //colors a cell when double clicked
    void simulate2D(); //launches simulation
    void domainVerifMinAlive(const QString& s); //checks if the min number of alive cells is valid, if not, gives it a valid value
    void domainVerifMaxAlive(const QString& s); //checks if the max number of alive cells is valid, if not, gives it a valid value
    void domainVerifMinDead(const QString& s); //checks if the min number of dead cells is valid, if not, gives it a valid value
    void domainVerifMaxDead(const QString& s); //checks if the max number of dead cells is valid, if not, gives it a valid value
    void randomFill(); //randomly fills the cells
    void changeSize(); //changes the number of cells the automaton simulates
    void simulationAuto(); //launches automatic simulation
    void stopSimulationAuto(); //stops automatic simulation
    void emptyGrid(); //clears the grid
    void reset(); //stop the timer and clears all the cells
    void symetryRightLeft(); //applies symetry from right to left on the grid
    void symetryLeftRight(); //applies symetry from left to right on the grid
    void save(); //function to save the current automaton's data
    void configSpeciale(); //applies the chosen special configuration

};

#endif
