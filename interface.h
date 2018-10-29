#ifndef INTERFACE_H
#define INTERFACE_H

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include<QStackedWidget>
#include<QPushButton>
#include<QFont>
#include<QMdiArea>
#include<QComboBox>
#include<autocell.h>
#include<Simulator.h>
#include<State.h>
#include<automaton.h>
#include<autocell.h>
#include<autocell2d.h>
#include<autofeu.h>

#include <QtWidgets>

class AutoCell;
class gameLife;
class forestFire;


//main window interface
class MainWindow : public QMainWindow
{
     Q_OBJECT
    public:

    MainWindow();

    //interface variable holders and labels
    QLabel* titleComboBoxAuto1D;
    QLabel* titleComboBoxAutoLife;
    QLabel* titleComboBoxAutoFire;
    QWidget* home;
    QWidget* pageAutoCell;
    QWidget* pageAutoLife;
    QWidget* pageAutoFireForest;
    QStackedWidget* stack;

    //automata widgets
    AutoCell* autoCell1D;
    gameLife* autoLife;
    forestFire* autoFireForest;

    QComboBox* comboBoxAuto1D;
    QComboBox* comboBoxAutoLife;
    QComboBox* comboBoxAutoFire;

    //interface buttons
    QPushButton* buttonAuto1D;
    QPushButton* buttonAutoLife;
    QPushButton* buttonAutoFire;

    //layout
    QVBoxLayout* layoutAutoCell;
    QVBoxLayout* layoutAutoLife;
    QVBoxLayout* layoutAutoFireForest;
    QHBoxLayout* buttons;
    QVBoxLayout *layout;


protected:

    void closeEvent(QCloseEvent *event) override; //redefines what happens when we close the app
    void buildHome();
    void buildAuto1D();
    void buildAutoLife();
    void buildAutoFireForest();

public slots:

    void showPage1(); //shows the one dimension automata page
    void showPage2(); //shows the game of life automata page
    void showPage3(); //shows the forest fire automata page

    //dialogue boxes to choose between loading the saved automaton or not
    void openDialogue1();
    void openDialogue2();
    void openDialogue3();

    //shows the interface of the desired automaton
    void showPage1Sauv(); //one dimension
    void showPage2Sauv(); //game of life
    void showPage3Sauv(); //forest fire

    private:
    QPushButton *m_buttonDialogue1;
    QPushButton *m_buttonDialogue2;
    QPushButton *m_buttonDialogue3;
    };




#endif
