#include "autocell.h"
#include "xml_dom.h"

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

AutoCell::AutoCell(QWidget* parent): QWidget(parent), rank(0), rule(0), length(25), dimension(25), speed(50) {

    title = new QLabel("1 Dimension Automaton \n Simulates the evolution of cells following basic binary rules");
    title->setAlignment(Qt::AlignCenter);

    // Containers
    numc = new QVBoxLayout; // Spinbox container
    dimc = new QVBoxLayout; // layer for length label and field
    numeroc= new QHBoxLayout; // layer for the bits columns
    layer = new QVBoxLayout;
    layer->addWidget(title);

    // SpinBox for the integer rule
    num = new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(rule);

    //Spinbox for the automatic execution step
    step = new QSpinBox(this);
    step->setRange(1,6);
    step->setValue(3);

    // Label for the rule spinbox
    numl= new QLabel("Rule");

    //Label for the step spinbox
    stepl = new QLabel("Vitesse");

    numc->addWidget(numl); numc->addWidget(num);
    numc->addWidget(stepl); numc->addWidget(step);

    //validators handle the binary domains
    zeroOneValidator=new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    //timer for automatic simulation
    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(simulate()));


    // define labels and fiels for the automaton's 8 bit rule

   for(unsigned int i=0; i<8; i++){
        // fields
        numeroBit[i]=new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);

        //label definition
        numeroBitl[i]= new QLabel;

        //Vertical QBoxes to hold bits labels and fields
        bitc[i]= new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);


        numeroc->addLayout(bitc[i]);

    }

     for(unsigned int i=0; i<2; i++){
        // Label & value fields for the grid dimensions
        diml[i] = new QLabel;
        dim[i] = new QSpinBox;
        dim[i]->setRange(2,50);
        dim[i]->setValue(25);

        // add labels to layout
        dimc->addWidget(diml[i]);
        dimc->addWidget(dim[i]);
    }

    // add dimensions column
    parameters = new QHBoxLayout;
    parameters->addLayout(numc);
    parameters->addLayout(dimc);
    layer->addLayout(parameters);

    diml[0]->setText("Length");
    diml[1]->setText("Number of simulated rows");


    //8 bits labels
    numeroBitl[0]->setText("111");
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[7]->setText("000");

    // add it to layout
    layer->addLayout(numeroc);

    // create initial grid
    start=new QTableWidget(1,dim[0]->value(),this);
    unsigned int size=600;
    start->setFixedSize(size, size/dim[0]->value());
    start->horizontalHeader()->setVisible(false);
    start->verticalHeader()->setVisible(false);
    start->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    start->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // aesthetic functions
    start->setEditTriggers(QAbstractItemView::NoEditTriggers);
    start->setFocusPolicy(Qt::NoFocus);
    start->setSelectionMode(QAbstractItemView::NoSelection);


    layer->addWidget(start);

    // synchronize spinbox with bits
    connect(num,SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));

    // synchronize bits with spinbox
    for(unsigned int i=0; i<8; i++)
        connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum(QString)));

    // make initial cells double clickable
    connect(start,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(cellActivation(QModelIndex)));

    // add feature buttons
    change=new QPushButton("Change Dimensions");
    connect(change,SIGNAL(clicked()),this,SLOT(changeSize()));

    //Simulate step by step
    simulation=new QPushButton("Simulate Step by Step");
    connect(simulation,SIGNAL(clicked()),this,SLOT(simulate()));

    //Random fill
    randomButton=new QPushButton("Random fill");
    connect(randomButton,SIGNAL(clicked()),this,SLOT(randomFill()));

    //autosimulation
    simulAuto =new QPushButton("Automatic Simulation");
    connect(simulAuto,SIGNAL(clicked()),this,SLOT(simulationAuto()));

    //Stop auto simulation
    stopSimulAuto =new QPushButton("Stop Auto Simulation");
    connect(stopSimulAuto,SIGNAL(clicked()),this,SLOT(stopSimulationAuto()));

    //generates random automaton rule
    randomRuleButton = new QPushButton("Random Rule");
    connect(randomRuleButton,SIGNAL(clicked()),this,SLOT(randomRule()));

    //reset grid
    empty = new QPushButton("Reset Grid");
    connect(empty,SIGNAL(clicked()),this,SLOT(reset()));


    // grid definition
    states=new QTableWidget(dim[1]->value(),dim[0]->value(),this);
    states->setFixedSize(size,size);
    states->horizontalHeader()->setVisible(false);
    states->verticalHeader()->setVisible(false);
    states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setEditTriggers(QAbstractItemView::NoEditTriggers);
    states->setFocusPolicy(Qt::NoFocus);
    states->setSelectionMode(QAbstractItemView::NoSelection);

    for(unsigned int i=0; i<dim[0]->value(); i++){
        states->setColumnWidth(i, size);
        states->setRowHeight(i,size);
        for(unsigned int j=0; j<dim[1]->value(); j++){
            states->setItem(j,i,new QTableWidgetItem(""));
        }

     }

    buttons[0] = new QHBoxLayout; buttons[1] = new QHBoxLayout;
    buttons[0]->addWidget(simulation);
    buttons[0]->addWidget(simulAuto);
    buttons[0]->addWidget(stopSimulAuto);
    buttons[1]->addWidget(randomButton);
    buttons[1]->addWidget(randomRuleButton);
    buttons[1]->addWidget(empty);
    buttons[1]->addWidget(change);


    layer->addLayout(buttons[0]);
    layer->addLayout(buttons[1]);

    //add grid
    //Layout to store and center grid
    startC = new QHBoxLayout;
    startC->addStretch();
    startC->addWidget(states);
    startC->addStretch();
    layer->addLayout(startC);

    changeSize();

    setLayout(layer);
}

void AutoCell::synchronizeNumToNumBit(int j){
    std::string numbit=NumToNumBit(j);
    for(unsigned int i=0; i<8; i++)
        numeroBit[i]->setText(QString(numbit[i]));
    timer->stop();

}

void AutoCell::synchronizeNumBitToNum(const QString& s){
    for(unsigned int i=0; i<8; i++)
        if (numeroBit[i]->text()=="") return;
    std::string str;
    for(unsigned int i=0; i<8; i++)
        str+=numeroBit[i]->text().toStdString();
    int i=NumBitToNum(str);
    num->setValue(i);
    timer->stop();

}

void AutoCell::changeSize(){
    timer->stop();
    length = dim[0]->value();
    dimension = dim[1]->value();

    start->setColumnCount(length);

    for(unsigned int i=0; i< (length); i++){
        start->setItem(0,i,new QTableWidgetItem(""));
        start->setColumnWidth(i, size/length);
    }


    states->setColumnCount(length);
    states->setRowCount(dimension);

    for(unsigned int i=0; i<dimension; i++){
        for(unsigned int j=0; j<length; j++){
            if(!states->item(i,j)) states->setItem(i,j,new QTableWidgetItem(""));
        }
    }

    for(unsigned int i=0; i<length; i++)  states->setColumnWidth(i, size/length);

    for(unsigned int j=0; j<dimension; j++)  states->setRowHeight(j, size/dimension);


    emptyGrid();
}

void AutoCell::cellActivation(const QModelIndex& index){
    if(start->item(0, index.column())->text()==""){ //desactivé
        start->item(0,index.column())->setText("_");
        start->item(0,index.column())->setBackgroundColor("black");
        start->item(0,index.column())->setTextColor("black");
    }else{//activé
        start->item(0,index.column())->setText("");
        start->item(0,index.column())->setBackgroundColor("white");
        start->item(0,index.column())->setTextColor("white");
    }
}

void AutoCell::simulate(){
    if(rule != num->value()){
        emptyGrid();
        rule = num->value();
    }

    State e(length);
    if(rank>0){
        for(unsigned int i=0; i<length; i++){
            if(states->item((rank-1)%dimension,i)->text()!="") e.setCell(i,1);
        }
    }
    else{
        for(unsigned int i=0; i<length; i++){
            if(start->item(0,i)->text()!="") e.setCell(i,1);
        }
    }

    const Automaton& A= AutomatonManager::getAutomatonManager().getAutomaton(rule);
    Simulator S(A,e,dimension);
    S.next();
    const State& d=S.getLast();

    for(unsigned int j=0; j<length; j++){
        if(d.getCell(j)){
            states->item(rank%dimension,j)->setBackgroundColor(("black"));
            states->item(rank%dimension,j)->setText("_");
            states->item(rank%dimension,j)->setTextColor("black");
        }
        else{
           states->item(rank%dimension,j)->setBackgroundColor(("white"));
           states->item(rank%dimension,j)->setText("");
           states->item(rank%dimension,j)->setTextColor("white");
        }
    }
    rank++;
    //}

}

void AutoCell::randomFill(){
    for(unsigned int i=0;i<length;i++){
            if(rand()%2){
                start->item(0,i)->setText(" ");
                start->item(0,i)->setBackgroundColor("black");
                start->item(0,i)->setTextColor("black");
            }
            else{
                start->item(0,i)->setText("");
                start->item(0,i)->setBackgroundColor("white");
                start->item(0,i)->setTextColor("white");
            }
        }
    timer->stop();
    emptyGrid();
    }


void AutoCell::simulationAuto(){
    speed = (7 - step->value() )*100;
    timer->setInterval(speed);
    timer->start();
}

void AutoCell::stopSimulationAuto(){
    timer->stop();
}

 void AutoCell::emptyGrid(){
     rank=0;
    for(unsigned int i=0;i<dimension;i++){
        for(unsigned int j=0; j<length; j++){
            states->item(i,j)->setText("");
            states->item(i,j)->setBackgroundColor("white");
            states->item(i,j)->setTextColor("white");
        }
    }
}

void AutoCell::randomRule(){
     num->setValue(rand()%256);
}

void AutoCell::reset(){
    timer->stop();
    emptyGrid();
}

 void AutoCell::save(){
     QString c = QString::number(length);
     QString nbrE= QString::number(dimension);
     QString num= QString::number(rule);
     QString step= QString::number(7-(speed/100));
     Xml_Dom *Dom1 = new Xml_Dom();
     Dom1->writeDim1("AutoCell","lengthh1",num, c, nbrE,step);
}
