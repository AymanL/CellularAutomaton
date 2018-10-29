#ifndef AUTOCELL
#define AUTOCELL

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
#include "automaton.h"
#include "State.h"
#include "simulator.h"
#include "xml_dom.h"
#include "interface.h"


short unsigned int NumBitToNum(const std::string& num); //converts "num" from binary to integer

std::string NumToNumBit(short unsigned int num); // converts "num" from integer to binary


//AutoCell represents the interface of a 1 dimension cellular automaton, the class handles the widgets and slots of the interface
class AutoCell : public QWidget{

    friend class MainWindow; //friend declaration so the main window can access the attributes of the AutoCell widget
    Q_OBJECT

    //interface variable holders and labels
    QLabel* title;
    QSpinBox* num; // rule number
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl; // rule label
    QLabel* numeroBitl[8];
    QSpinBox* step; //speed at which the simulator goes
    QLabel* stepl; // speed label
    QLabel* diml[2];
    QSpinBox* dim[2];
    QIntValidator* zeroOneValidator; //int validator to keep the binary numbers within the right domain
    QTimer* timer;

    //interface layout
    QVBoxLayout* numc; //layout for the numbers
    QVBoxLayout* bitc[8]; //layout for the numbers making the binary rule
    QHBoxLayout* numeroc;
    QHBoxLayout* startC;
    QVBoxLayout* dimc;
    QHBoxLayout* parameters;
    QVBoxLayout* layer;
    QHBoxLayout* buttons[2];

    QTableWidget* start; //initial states
    QTableWidget* states; //grid

    // interface variables
    unsigned int length; // number of cells in a given row
    unsigned int dimension; // number of simulated rows
    unsigned int size = 600; //pixel size of the grid
    unsigned int rank; // current generation's rank, stocks the line we are currently simulating
    unsigned int rule; // current automaton's rule
    unsigned int speed; //speed at which the simulation goes

    // interface buttons
    QPushButton* simulation;
    QPushButton* randomButton;
    QPushButton* change;
    QPushButton* simulAuto;
    QPushButton* stopSimulAuto;
    QPushButton* randomRuleButton;
    QPushButton* empty;

public:
    explicit AutoCell(QWidget* parent = nullptr); //class constructor
    void save(); //function to save the current automaton's data

private slots:
    void synchronizeNumToNumBit(int i); //changes the binary rule number when the rule's integer number changes
    void synchronizeNumBitToNum(const QString& s); //changes the integer rule number when the rule's binary numbers change
    void cellActivation(const QModelIndex& index); //colors a cell when double clicked
    void simulate(); //launches simulation
    void randomFill(); //randomly fills the cells
    void changeSize(); //changes the number of cells the automaton simulates
    void simulationAuto(); //launches automatic simulation
    void stopSimulationAuto(); //stops automatic simulation
    void reset(); //stop the timer and clears all the cells
    void randomRule(); //chooses a random rule for the automaton
    void emptyGrid(); //clears the grid
};

#endif
