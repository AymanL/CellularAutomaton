#include "autocell2d.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

gameLife::gameLife(QWidget* parent): QWidget(parent){

    title = new QLabel("Game of Life Simulator \n Simulates Conway's game of life by default, the parameters can be changed \n Double click a cell in the grid to make it alive (you can also use the random fill button to go faster), \n when satisfied with the result, press the \" Step by Step Simulation \" or the \" Automatic Simulation \" button ");
    title->setAlignment(Qt::AlignCenter);

    numAlivel[0] = new QLabel("Minimum number of alive neighbors \n to stay alive (at least 0)");
    numAlivel[1] = new QLabel("Maximum number of alive neighbors \n to stay alive (at most 4)");
    numDeadl[0] = new QLabel("Minimum number of alive neighbors \n to born (at least 0)");
    numDeadl[1] = new QLabel("Maximum number of alive neighbors \n to born (at most 4)");
    neighbors[0] = new QIntValidator(0,4,this);
    neighbors[1] = new QIntValidator(0,4,this);
    parameters = new QHBoxLayout;
    dimc = new QVBoxLayout;
    stepc= new QVBoxLayout;

    //timer for the automatic simulation step
    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(simulate2D()));

    //Spinbox for special settings
    configSpe = new QComboBox;
    configSpe->addItem(tr("Right -> Left Symetry"));
    configSpe->addItem(tr("Left -> Right Symetry"));

    //Label for special configurations combobox
    configSpel = new QLabel("Special settings");

    configSpec= new QVBoxLayout; //layout holding the step and the special confs

    //Spinbox for the automatic execution step
    step = new QSpinBox(this);
    step->setRange(1,6);
    step->setValue(3);

    stepc= new QVBoxLayout;

    //Label for the step spinbox
    stepl = new QLabel("Speed");

    configSpec->addWidget(configSpel); configSpec->addWidget(configSpe);
    configSpec->addWidget(stepl); configSpec->addWidget(step);
    stepc->addWidget(stepl); stepc->addWidget(step);


    for(unsigned int i=0;i<2;i++){

        numViv[i] = new QLineEdit;
        numViv[i]->setMaxLength(1);
        numViv[i]->setValidator(neighbors[i]);

        numDead[i] = new QLineEdit;
        numDead[i]->setMaxLength(1);
        numDead[i]->setValidator(neighbors[i]);

        diml[i] = new QLabel;
        dim[i] = new QSpinBox;
        dim[i]->setRange(2,255);
        dim[i]->setValue(50);

        numMinMax[i] = new QVBoxLayout;
        numMinMax[i]->addWidget(numAlivel[i]);
        numMinMax[i]->addWidget(numViv[i]);
        numMinMax[i]->addWidget(numDeadl[i]);
        numMinMax[i]->addWidget(numDead[i]);

        dimc->addWidget(diml[i]); dimc->addWidget(dim[i]);

        parameters->addLayout(numMinMax[i]);
    }

    parameters->addLayout(dimc);
    parameters->addLayout(configSpec);

    numViv[0]->setText("2"); numViv[1]->setText("3");
    numDead[0]->setText("3"); numDead[1]->setText("3");
    diml[0]->setText("Columns"); diml[1]->setText("Rows");

    // domain verification
    connect(numViv[0],SIGNAL(textChanged(QString)),this,SLOT(domainVerifMinAlive(QString)));
    connect(numViv[1],SIGNAL(textChanged(QString)),this,SLOT(domainVerifMaxAlive(QString)));
    connect(numDead[0],SIGNAL(textChanged(QString)),this,SLOT(domainVerifMinDead(QString)));
    connect(numDead[1],SIGNAL(textChanged(QString)),this,SLOT(domainVerifMaxDead(QString)));


    // create initial grid
    start=new QTableWidget(dim[0]->value(),dim[1]->value(),this);
    start->setFixedSize(size,size);
    start->horizontalHeader()->setVisible(false);
    start->verticalHeader()->setVisible(false);
    start->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start->setEditTriggers(QAbstractItemView::NoEditTriggers);
    start->setFocusPolicy(Qt::NoFocus);
    start->setSelectionMode(QAbstractItemView::NoSelection);

    changeSize();


    // add feature buttons
    change=new QPushButton("Change Size");
    connect(change,SIGNAL(clicked()),this,SLOT(changeSize()));

    // make initial cells double clickable
    layer = new QVBoxLayout;
    connect(start,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(cellActivation(QModelIndex)));

    //Simulate step by step
    simulation=new QPushButton("Step by Step Simulation");
    connect(simulation,SIGNAL(clicked()),this,SLOT(simulate2D()));

    //Random fill
    randomButton=new QPushButton("Random fill");
    connect(randomButton,SIGNAL(clicked()),this,SLOT(randomFill()));

    //autosimulation
    simulAuto =new QPushButton("Automatic Simulation");
    connect(simulAuto,SIGNAL(clicked()),this,SLOT(simulationAuto()));

    //Stop auto simulation
    stopSimulAuto =new QPushButton("Stop Auto Simulation");
    connect(stopSimulAuto,SIGNAL(clicked()),this,SLOT(stopSimulationAuto()));

    //reset grid
    empty = new QPushButton("Reset Grid");
    connect(empty,SIGNAL(clicked()),this,SLOT(reset()));

    //applies special settings
    configSpeB = new QPushButton("Use Special Settings");
    connect(configSpeB,SIGNAL(clicked()),this,SLOT(configSpeciale()));


    //buttons layout
    buttons[0] = new QHBoxLayout; buttons[1] = new QHBoxLayout;
    buttons[0]->addWidget(simulation);
    buttons[0]->addWidget(simulAuto);
    buttons[0]->addWidget(stopSimulAuto);
    buttons[1]->addWidget(randomButton);
    buttons[1]->addWidget(empty);
    buttons[1]->addWidget(change);
    buttons[1]->addWidget(configSpeB);

    //window box holding the title, the buttons and the grid
    layer->addWidget(title);
    layer->addLayout(parameters);
    layer->addLayout(buttons[0]);
    layer->addLayout(buttons[1]);

    //Layout to store and center grid
    startC = new QHBoxLayout;
    startC->addStretch();
    startC->addWidget(start);
    startC->addStretch();
    layer->addLayout(startC);


    setLayout(layer);

}

 void gameLife::simulate2D(){

    State e(height,length);
    e.setLargeur(height);
    e.setLongueur(length);
     for(unsigned int i=0; i<length; i++){
        for(unsigned int j=0; j<height;j++){
            if((start->item(i,j)->text())!="") e.setCell(j,i,true);
        }
    }
    minA=numViv[0]->text().toInt();
    maxA=numViv[1]->text().toInt();
    minD=numDead[0]->text().toInt();
    maxD=numDead[1]->text().toInt();

    const Automaton& A= AutomatonManager::getAutomatonManager().getAutomaton(minA,maxA,minD,maxD);

    Simulator S(A,e);
    S.next();

    const State& d=S.getLast();
     for(unsigned int i=0; i<height; i++){
        for(unsigned int j=0; j<length; j++){
            if(d.getCell(i,j)){
                start->item(j,i)->setBackgroundColor(("black"));
                start->item(j,i)->setText(" ");
            }else{
               start->item(j,i)->setBackgroundColor(("white"));
               start->item(j,i)->setText("");
            }
        }
    }

}

void gameLife::cellActivation(const QModelIndex& index){
    if(start->item(index.row(), index.column())->text()==""){ //dead cell
        start->item(index.row(),index.column())->setText(" ");
        start->item(index.row(),index.column())->setBackgroundColor("black");
        start->item(index.row(),index.column())->setTextColor("black");
    }else{//alive cell
        start->item(index.row(),index.column())->setText("");
        start->item(index.row(),index.column())->setBackgroundColor("white");
        start->item(index.row(),index.column())->setTextColor("white");
    }

}

void gameLife::domainVerifMinAlive(const QString& s){
        if(s > numViv[1]->text())
            numViv[0]->setText(
                        QString(numViv[1]->text())
                    );
        timer->stop();

}

void gameLife::domainVerifMaxAlive(const QString& s){
        if(s < numViv[0]->text())
            numViv[1]->setText(
                        QString(numViv[0]->text())
                    );
                timer->stop();
}

void gameLife::domainVerifMinDead(const QString& s){
        if(s > numDead[1]->text())
            numDead[0]->setText(
                        QString(numDead[1]->text())
                    );
        timer->stop();
}

void gameLife::domainVerifMaxDead(const QString& s){
        if(s < numDead[0]->text())
            numDead[1]->setText(
                        QString(numDead[0]->text())
                    );
                timer->stop();
}

void gameLife::randomFill(){
    for(unsigned int i=0;i<length;i++){
        for(unsigned int j=0; j<height; j++){
            if(rand()%2){
                start->item(i,j)->setText(" ");
                start->item(i,j)->setBackgroundColor("black");
                start->item(i,j)->setTextColor("black");
            }
            else{
                start->item(i,j)->setText("");
                start->item(i,j)->setBackgroundColor("white");
                start->item(i,j)->setTextColor("white");
            }
        }
    }
        timer->stop();
}


void gameLife::changeSize(){
    timer->stop();
    length = dim[0]->value();
    height = dim[1]->value();
    start->setColumnCount(height);
    start->setRowCount(length);


    for(unsigned int i=0; i<dim[1]->value(); i++) start->setColumnWidth(i, size/height);
    for(unsigned int i=0; i<dim[0]->value(); i++) start->setRowHeight(i, size/length);

    for(unsigned int i=0; i<dim[0]->value(); i++){
        for(unsigned int j=0; j<dim[1]->value(); j++){
            if(!start->item(i,j)) start->setItem(i,j,new QTableWidgetItem(""));
        }
    }
    emptyGrid();

}

void gameLife::simulationAuto(){
    speed = (7 - step->value() )*100;
    timer->setInterval(speed);
    timer->start();
}

void gameLife::stopSimulationAuto(){
    timer->stop();
}

void gameLife::emptyGrid(){
   for(unsigned int i=0;i<length;i++){
       for(unsigned int j=0; j<height; j++){
           start->item(i,j)->setText("");
           start->item(i,j)->setBackgroundColor("white");
           start->item(i,j)->setTextColor("white");
       }
   }
}

void gameLife::reset(){
    timer->stop();
    emptyGrid();
}

void gameLife::symetryRightLeft(){
    timer->stop();
    for(unsigned int i=0; i< height/2;i++){
        for(unsigned int j=0; j<length;j++){
            if(start->item(j,i)->text()!=""){
                start->item(j,height - i - 1)->setText("_");
                start->item(j,height - i - 1)->setBackgroundColor("black");
                start->item(j,height - i - 1)->setTextColor("black");

            }
            else{
                start->item(j,height - i - 1)->setText("");
                start->item(j,height - i - 1)->setBackgroundColor("white");
                start->item(j,height - i - 1)->setTextColor("white");
            }
        }
    }
}

void gameLife::symetryLeftRight(){
    timer->stop();
    for(unsigned int i=height/2; i< height;i++){
        for(unsigned int j=0; j<length;j++){
            if(start->item(j,i)->text()!=""){
                start->item(j,height - i - 1)->setText("_");
                start->item(j,height - i - 1)->setBackgroundColor("black");
                start->item(j,height - i - 1)->setTextColor("black");

            }
            else{
                start->item(j,height - i - 1)->setText("");
                start->item(j,height - i - 1)->setBackgroundColor("white");
                start->item(j,height - i - 1)->setTextColor("white");
            }
        }
    }
}



void gameLife::configSpeciale(){
    if(configSpe->currentIndex()==0) symetryRightLeft();
    if(configSpe->currentIndex()==1) symetryLeftRight();
}

void gameLife::save(){
    QString mi1 = QString::number(numViv[0]->text().toInt());
    QString ma1 = QString::number(numViv[1]->text().toInt());
    QString mi2 = QString::number(numDead[0]->text().toInt());
    QString ma2 = QString::number(numDead[1]->text().toInt());
    QString step = QString::number(7-(speed/100));
    QString c = QString::number(height);
    QString l= QString::number(length);
    Xml_Dom *Dom2 = new Xml_Dom();
    Dom2->writeGameLife("gameLifeInstance", "JeuVie", mi1, ma1,mi2, ma2, c, l, step);
}
