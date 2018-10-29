#include "interface.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

MainWindow::MainWindow()
{
    home = new QWidget;
    pageAutoCell = new QWidget;
    pageAutoLife = new QWidget;
    pageAutoFireForest = new QWidget;

    stack = new QStackedWidget;

    stack->addWidget(home);
    stack->addWidget(pageAutoCell);
    stack->addWidget(pageAutoLife);
    stack->addWidget(pageAutoFireForest);

    setCentralWidget(stack);

    buildHome();

    buildAuto1D();

    buildAutoLife();

    buildAutoFireForest();


}


void MainWindow::buildHome(){
    //button to go to 1 Dimension automaton page
    buttonAuto1D = new QPushButton("1 Dimension Automaton");
    connect(buttonAuto1D, SIGNAL(clicked()), this, SLOT(openDialogue1()));

    //button to go to Game of Life automaton page
    buttonAutoLife = new QPushButton("Automaton jeu de la vie");
    connect(buttonAutoLife, SIGNAL(clicked()), this, SLOT(openDialogue2()));

    //button to go to Forest Fire automaton page
    buttonAutoFire = new QPushButton("Automaton fire de forêt");
    connect(buttonAutoFire, SIGNAL(clicked()), this, SLOT(openDialogue3()));

    //layout to horizontally display buttons
    buttons=new QHBoxLayout;
    buttons->addWidget(buttonAuto1D);
    buttons->addWidget(buttonAutoLife);
    buttons->addWidget(buttonAutoFire);


    QVBoxLayout *LayoutAccueil = new QVBoxLayout;
    QVBoxLayout *presentation = new QVBoxLayout;
    LayoutAccueil->addLayout(presentation);

    //Presentation Layout

    QLabel *premier = new QLabel("<b><center><H1> Welcome to our App </H1> </center></b>", this);
    QLabel *deuxieme = new QLabel("<center> This app simulates cellular automata </center> ", this);
    QLabel *troisieme = new QLabel("Autocell App was realised within the LO21 course : Object-oriented programming and design ", this);

    presentation->addWidget(premier);
    presentation->addWidget(deuxieme);
    presentation->addWidget(troisieme);

    presentation->addLayout(buttons);

    home->setLayout(LayoutAccueil);
}

void MainWindow::buildAuto1D(){

    titleComboBoxAuto1D = new QLabel("Change Automaton");
    comboBoxAuto1D = new QComboBox;
    comboBoxAuto1D->addItem(tr("Home"));
    comboBoxAuto1D->addItem(tr("One Dimension Automaton"));
    comboBoxAuto1D->addItem(tr("Game of Life"));
    comboBoxAuto1D->addItem(tr("Forest Fire"));
    comboBoxAuto1D->setCurrentIndex(1);
    connect(comboBoxAuto1D, SIGNAL(activated(int)),stack, SLOT(setCurrentIndex(int)));

    autoCell1D = new AutoCell;

    layoutAutoCell = new QVBoxLayout;

    layoutAutoCell->addWidget(titleComboBoxAuto1D);
    layoutAutoCell->addWidget(comboBoxAuto1D);
    layoutAutoCell->addWidget(autoCell1D);

    pageAutoCell->setLayout(layoutAutoCell);
}

void MainWindow::buildAutoLife(){

    titleComboBoxAutoLife = new QLabel("Change Automaton");

    comboBoxAutoLife = new QComboBox;
    comboBoxAutoLife->addItem(tr("Home"));
    comboBoxAutoLife->addItem(tr("One Dimension Automaton"));
    comboBoxAutoLife->addItem(tr("Game of Life"));
    comboBoxAutoLife->addItem(tr("Forest Fire"));
    comboBoxAutoLife->setCurrentIndex(2);
    connect(comboBoxAutoLife, SIGNAL(activated(int)),stack, SLOT(setCurrentIndex(int)));

    autoLife = new gameLife;

    layoutAutoLife = new QVBoxLayout;

    layoutAutoLife->addWidget(titleComboBoxAutoLife);
    layoutAutoLife->addWidget(comboBoxAutoLife);
    layoutAutoLife->addWidget(autoLife);

    pageAutoLife->setLayout(layoutAutoLife);
}

void MainWindow::buildAutoFireForest(){

    titleComboBoxAutoFire = new QLabel("Change Automaton");

    comboBoxAutoFire = new QComboBox;
    comboBoxAutoFire->addItem(tr("Home"));
    comboBoxAutoFire->addItem(tr("One Dimension Automaton"));
    comboBoxAutoFire->addItem(tr("Game of Life"));
    comboBoxAutoFire->addItem(tr("Forest Fire"));
    comboBoxAutoFire->setCurrentIndex(3);
    connect(comboBoxAutoFire, SIGNAL(activated(int)),stack, SLOT(setCurrentIndex(int)));

    autoFireForest = new forestFire;

    layoutAutoFireForest = new QVBoxLayout;

    layoutAutoFireForest->addWidget(titleComboBoxAutoFire);
    layoutAutoFireForest->addWidget(comboBoxAutoFire);
    layoutAutoFireForest->addWidget(autoFireForest);

    pageAutoFireForest->setLayout(layoutAutoFireForest);
}


void MainWindow::openDialogue1(){
    int reponse = QMessageBox::question(this, "Get previous automaton", "Do you want to load the previously used automaton?", QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        //launches the app with the save
        this->showPage1Sauv();
    }
    else if (reponse == QMessageBox::No){
        this->showPage1();
    }
}

void MainWindow::showPage1()
{
    stack->setCurrentIndex(1);
    stack->setCurrentWidget(pageAutoCell);
}

void MainWindow::showPage1Sauv(){
    Xml_Dom *Dom1d = new Xml_Dom();
    dataD1* d1;
    d1 = Dom1d->readDim1();
    autoCell1D->rule = d1->rule;
    autoCell1D->dimension = d1->dimension;
    autoCell1D->length = d1->length;
    autoCell1D->num->setValue(d1->rule); //rule
    autoCell1D->dim[0]->setValue(d1->dimension); //dimension, number of rows
    autoCell1D->dim[1]->setValue(d1->length); //length, number of columns
    autoCell1D->changeSize(); //opens with the right dimensions
    stack->setCurrentIndex(1);
    stack->setCurrentWidget(pageAutoCell);
}

void MainWindow::openDialogue2(){
    int reponse = QMessageBox::question(this,"Get previous automaton", "Do you want to load the previously used automaton?", QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        //launches the app with the save
        this->showPage2Sauv();
    }
    else if (reponse == QMessageBox::No){
        this->showPage2();
    }
}

void MainWindow::showPage2()
{
    stack->setCurrentIndex(2);
    stack->setCurrentWidget(pageAutoLife);
}

void MainWindow::showPage2Sauv(){
    Xml_Dom *Dom2d = new Xml_Dom();
    dataGameLife* d2;
    d2 = Dom2d->readGameLife();
    autoLife->minA = d2->minA;
    autoLife->maxA = d2->maxA;
    autoLife->minD = d2->minD;
    autoLife->maxD = d2->maxD;
    autoLife->height = d2->height;
    autoLife->length = d2->length;
    autoLife->speed = d2->step;
    autoLife->numViv[0]->setText(QString::number(d2->minA));
    autoLife->numViv[1]->setText(QString::number(d2->maxA));
    autoLife->numDead[0]->setText(QString::number(d2->minD));
    autoLife->numDead[1]->setText(QString::number(d2->maxD));
    autoLife->dim[0]->setValue(d2->height);
    autoLife->dim[1]->setValue(d2->length);
    autoLife->step->setValue(d2->step);
    autoLife->changeSize();//opens with the right dimensions
    stack->setCurrentIndex(2);
    stack->setCurrentWidget(pageAutoLife);
}

void MainWindow::openDialogue3(){
    int reponse = QMessageBox::question(this, "Get previous automaton", "Do you want to load the previously used automaton?", QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        //launches the app with the save
        this->showPage3Sauv();
    }
    else if (reponse == QMessageBox::No){
        this->showPage3();
    }
}

void MainWindow::showPage3()
{
    stack->setCurrentIndex(3);
    stack->setCurrentWidget(pageAutoFireForest);
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(stack->currentIndex() == 1){ autoCell1D->save(); }
    if(stack->currentIndex() == 2){ autoLife->save(); }
    if(stack->currentIndex() == 3){ autoFireForest->save(); }
    event->accept();
}

void MainWindow::showPage3Sauv(){
    Xml_Dom *Dom3d = new Xml_Dom();
    dataForestFire* d3;
    d3 = Dom3d->readFeu();
    autoFireForest->height=d3->height;
    autoFireForest->length=d3->length;
    autoFireForest->dim[0]->setValue(d3->height);
    autoFireForest->dim[1]->setValue(d3->length);
    autoFireForest->speed= d3->step;
    autoFireForest->step->setValue(d3->step);
    autoFireForest->changeSize();//opens with the right dimensions
    stack->setCurrentIndex(3);
    stack->setCurrentWidget(pageAutoFireForest);
}



