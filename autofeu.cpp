#include "autofeu.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */


forestFire::forestFire(QWidget* parent): QWidget(parent){
    title = new QLabel("Forest Fire Simulation \n Simulates the propagation of a fire in a forest, randomly fill the grid then double click a cell to light fire \n When ready, click the simulation button");
    title->setAlignment(Qt::AlignCenter);
    parameters = new QHBoxLayout;


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


    //timer for the automatic simulation step
    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(simulateFire()));


    dimc = new QVBoxLayout;
    for(unsigned int i=0;i<2;i++){
        diml[i] = new QLabel;
        dim[i] = new QSpinBox;
        dim[i]->setRange(2,255);
        dim[i]->setValue(50);
        dimc->addWidget(diml[i]); dimc->addWidget(dim[i]);
    }

    diml[0]->setText("Rows"); diml[1]->setText("Columns");

    parameters->addLayout(dimc);
    parameters->addLayout(configSpec);



    //forest grid
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
    change=new QPushButton("Change dimensions");
    connect(change,SIGNAL(clicked()),this,SLOT(changeSize()));

    connect(start,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(cellActivation(QModelIndex)));

    //step by step simulation
    simulation=new QPushButton("Step by Step Fire");
    connect(simulation,SIGNAL(clicked()),this,SLOT(simulateFire()));

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


    layer = new QVBoxLayout;
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

 void forestFire::simulateFire(){
    State e(height,length);

    for(unsigned int i=0; i<length; i++){
        for(unsigned int j=0; j<height;j++){
            if(start->item(i,j)->text()=="w"){ e.setCell(j,i,0);}
            if(start->item(i,j)->text()=="g"){ e.setCell(j,i,1);}
            if(start->item(i,j)->text()=="r"){ e.setCell(j,i,2);}
            if(start->item(i,j)->text()=="grey"){ e.setCell(j,i,3);}
        }
    }

    const Automaton& A= AutomatonManager::getAutomatonManager().getFireAutomaton();
    Simulator S(A,e);
    S.next();

    const State& d=S.getLast();
    for(unsigned int i=0; i<height; i++){
        for(unsigned int j=0; j<length; j++){
            if(d.getCell(i,j)==0){
                start->item(j,i)->setBackgroundColor(("white"));
                start->item(j,i)->setText("w");
                start->item(j,i)->setTextColor("white");
            }
            if(d.getCell(i,j)==1){
                start->item(j,i)->setBackgroundColor(("green"));
                start->item(j,i)->setText("g");
                start->item(j,i)->setTextColor("green");
            }
            if(d.getCell(i,j)==2){
                start->item(j,i)->setBackgroundColor(("red"));
                start->item(j,i)->setText("r");
                start->item(j,i)->setTextColor("red");
            }
            if(d.getCell(i,j)==3){
               start->item(j,i)->setBackgroundColor(("grey"));
               start->item(j,i)->setText("grey");
               start->item(j,i)->setTextColor("grey");
            }
        }
    }
 }

void forestFire::cellActivation(const QModelIndex& index){
    if(start->item(index.row(), index.column())->text()=="g"){ //arbre
        start->item(index.row(),index.column())->setText("r");
        start->item(index.row(),index.column())->setBackgroundColor("red");
        start->item(index.row(),index.column())->setTextColor("red");
    }else{
        start->item(index.row(),index.column())->setText("w");
        start->item(index.row(),index.column())->setBackgroundColor("white");
        start->item(index.row(),index.column())->setTextColor("white");
    }
        timer->stop();
}

void forestFire::randomFill(){
    for(unsigned int i=0;i<length;i++){
        for(unsigned int j=0; j<height; j++){
            if(rand()%11  < 6){
                start->item(i,j)->setText("g");
                start->item(i,j)->setBackgroundColor("green");
                start->item(i,j)->setTextColor("green");
            }
            else{
                start->item(i,j)->setText("w");
                start->item(i,j)->setBackgroundColor("white");
                start->item(i,j)->setTextColor("white");
            }
        }
    }
        timer->stop();
}


void forestFire::changeSize(){
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

void forestFire::simulationAuto(){
    speed = (7 - step->value() )*100;
    timer->setInterval(speed);
    timer->start();
}


void forestFire::stopSimulationAuto(){
    timer->stop();
}

void forestFire::emptyGrid(){
   for(unsigned int i=0;i<length;i++){
       for(unsigned int j=0; j<height; j++){
           start->item(i,j)->setText("");
           start->item(i,j)->setBackgroundColor("white");
           start->item(i,j)->setTextColor("white");
       }
   }
}

void forestFire::reset(){
    timer->stop();
    emptyGrid();
}


void forestFire::save(){
    QString c = QString::number(height);
    QString l= QString::number(length);
    QString step= QString::number(7-(speed/100));
    Xml_Dom *Dom3 = new Xml_Dom();
    Dom3->writeFeu("AutoFire", "forestFireInstance", c, l, step);
}

void forestFire::symetryLeftRight(){
    timer->stop();
    for(unsigned int i=0; i< height/2;i++){
        for(unsigned int j=0; j<length;j++){
            if(start->item(j,i)->text()=="w"){
                start->item(j,height - i - 1)->setText("w");
                start->item(j,height - i - 1)->setBackgroundColor("white");
                start->item(j,height - i - 1)->setTextColor("white");

            }
            if(start->item(j,i)->text()=="g"){
                start->item(j,height - i - 1)->setText("g");
                start->item(j,height - i - 1)->setBackgroundColor("green");
                start->item(j,height - i - 1)->setTextColor("green");

            }
            if(start->item(j,i)->text()=="r"){
                start->item(j,height - i - 1)->setText("r");
                start->item(j,height - i - 1)->setBackgroundColor("red");
                start->item(j,height - i - 1)->setTextColor("red");

            }
            if(start->item(j,i)->text()=="grey"){
                start->item(j,height - i - 1)->setText("grey");
                start->item(j,height - i - 1)->setBackgroundColor("grey");
                start->item(j,height - i - 1)->setTextColor("grey");

            }
        }
    }
}

void forestFire::symetryRightLeft(){
    timer->stop();
    for(unsigned int i=height/2; i< height;i++){
        for(unsigned int j=0; j<length;j++){
            if(start->item(j,i)->text()=="w"){
                start->item(j,height - i - 1)->setText("w");
                start->item(j,height - i - 1)->setBackgroundColor("white");
                start->item(j,height - i - 1)->setTextColor("white");

            }
            if(start->item(j,i)->text()=="g"){
                start->item(j,height - i - 1)->setText("g");
                start->item(j,height - i - 1)->setBackgroundColor("green");
                start->item(j,height - i - 1)->setTextColor("green");

            }
            if(start->item(j,i)->text()=="r"){
                start->item(j,height - i - 1)->setText("r");
                start->item(j,height - i - 1)->setBackgroundColor("red");
                start->item(j,height - i - 1)->setTextColor("red");

            }
            if(start->item(j,i)->text()=="grey"){
                start->item(j,height - i - 1)->setText("grey");
                start->item(j,height - i - 1)->setBackgroundColor("grey");
                start->item(j,height - i - 1)->setTextColor("grey");

            }
        }
    }
}

void forestFire::configSpeciale(){
    if(configSpe->currentIndex()==0) symetryRightLeft();
    if(configSpe->currentIndex()==1) symetryLeftRight();
}
