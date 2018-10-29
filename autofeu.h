#ifndef AUTOFEU_H
#define AUTOFEU_H

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
#include "Simulator.h"
#include "xml_dom.h"


//forestFire represents the propagation of a fire in a forest, the class handles the widgets and slots of the interface
class forestFire : public QWidget{

    friend class MainWindow; //friend declaration so the main window can access the attributes of the gameLife widget
    Q_OBJECT

    //interface variable holders and labels
    QLabel* title;
    QComboBox* configSpe;
    QLabel* configSpel;
    QLabel* diml[2];
    QSpinBox* dim[2];
    QSpinBox* step;
    QLabel* stepl;
    QTableWidget* start; //starting grid
    QTableWidget* states;
    QTimer *timer;

    //interface layout
    QVBoxLayout* configSpec;
    QVBoxLayout* dimc;
    QVBoxLayout* stepc;
    QVBoxLayout* layer;
    QHBoxLayout* startC;
    QHBoxLayout* parameters;
    QHBoxLayout* buttons[2];

    // interface variables
    unsigned int length; // number of columns
    unsigned int height; //number of rows
    unsigned int size=600; //pixel size of the grid
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
    explicit forestFire(QWidget* parent = nullptr); //class constructor

private slots:
    void cellActivation(const QModelIndex& index); //colors a cell when double clicked
    void simulateFire(); //launches simulation
    void randomFill(); //randomly fills the cells
    void changeSize(); //changes the number of cells the automaton simulates
    void simulationAuto(); //launches automatic simulation
    void stopSimulationAuto(); //stops automatic simulation
    void reset(); //stop the timer and clears all the cells
    void emptyGrid(); //clears the grid
    void save(); //function to save the current automaton's data
    void symetryLeftRight(); //applies symetry from left to right on the grid
    void symetryRightLeft(); //applies symetry from right to left on the grid
    void configSpeciale(); //applies the chosen special configuration

};

#endif // AUTOFEU_H
