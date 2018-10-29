#ifndef XML_DOM
#define XML_DOM

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

#include <QtGui>
#include <QtXml>
#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QDomElement>
#include <QString>
#include <QCloseEvent>
#include "automaton.h"
#include "autocell.h"
#include "autocell2d.h"
#include "interface.h"


//structs to save automaton data
struct dataD1
{
public:
    unsigned int rule;
    unsigned int dimension;
    unsigned int length;
    unsigned int step;
};

struct dataGameLife{
public:
    unsigned int minA;
    unsigned int maxA;
    unsigned int minD;
    unsigned int maxD;
    unsigned int height;
    unsigned int length;
    unsigned int step;
};


struct dataForestFire{
public:
    unsigned int height;
    unsigned int length;
    unsigned int step;
};

//DOM=Document Object Model
//Xml_Dom handles the data reading and writing processes

class Xml_Dom : public QWidget
{
public:
    Xml_Dom();
    ~Xml_Dom();

public slots:

    // XML reading methods
    dataD1* readDim1();
    dataGameLife* readGameLife();
    dataForestFire* readFeu();

    // XML writing methods
    void writeDim1(const QString& n, const QString& t, const QString& num,const QString& c, const QString& nbrE,const QString& step);
    void writeGameLife(const QString& n, const QString& t, const QString& mi1, const QString& ma1,const QString& mi2, const QString& ma2, const QString& c, const QString& l,const QString& step);
    void writeFeu(const QString& n, const QString& t, const QString& c, const QString& l,const QString& step);
};

#endif
