#include "xml_dom.h"
#include <iostream>
using namespace std;

/* Welcome to our App
 * This app simulates cellular automata
 * Autocell App was realised within the LO21 course : Object-oriented programming and design
 * Laure LENGLART & Ayman LAMDASNI
 * June 2018
 */

Xml_Dom::Xml_Dom() : QWidget(){}

Xml_Dom::~Xml_Dom(){}

dataD1* Xml_Dom::readDim1(){

    dataD1* donnee;
    donnee = new dataD1;
    QDomDocument domDim1("mon_xml"); //creates DOM objet
    QFile xml_docDim1("test1dW.xml"); //file choice
    //tests if the file is correctly open for reading
    if(!xml_docDim1.open(QIODevice::ReadOnly))
        {QMessageBox::warning(this, "Error at XML open", "XML could not be open. Check the file name.");
         return donnee;
        }
    //tests if the XML attribution to the DOM object is done
    if (!domDim1.setContent(&xml_docDim1))
        {xml_docDim1.close();
         QMessageBox::warning(this, "Error at XML open", "The XML file could be attributed to the QDomDocument object.");
         return donnee;
        }

    xml_docDim1.close(); //closes XML file, everything is in the DOM

    //data recuperation
    QDomElement dom_element = domDim1.documentElement(); //Creates objects, gets everything in the XML
    //generates first tag name
    //takes first XML node, <name>
    QDomElement noeudDim1 = dom_element.firstChild().toElement();
    //browses all the nodes and displays their tag name
    while(!noeudDim1.isNull()){
        //next node
        noeudDim1= noeudDim1.nextSibling().toElement();
        //test
        bool ok;
        if(noeudDim1.tagName()=="type"){
        }
        if(noeudDim1.tagName()=="numero"){
            donnee->rule = noeudDim1.text().toUInt(&ok, 10);
        }
        if(noeudDim1.tagName()=="Nbr_Colonne"){
            donnee->dimension = noeudDim1.text().toUInt(&ok, 10);
        }
        if(noeudDim1.tagName()=="nbr_etat") {
            donnee->length = noeudDim1.text().toUInt(&ok, 10);
        }
        if(noeudDim1.tagName()=="step") {
            donnee->step = noeudDim1.text().toUInt(&ok, 10);
        }
    }
    return donnee;
}


dataGameLife* Xml_Dom::readGameLife(){
    dataGameLife* donnee;
    donnee = new dataGameLife;
    QDomDocument domJeuVie("mon_xml");  //creates DOM objet
    QFile xml_docJeuVie("test2dW.xml");  //file choice

    //tests if the file is correctly open for reading
    if(!xml_docJeuVie.open(QIODevice::ReadOnly))
        {QMessageBox::warning(this, "Error at XML open", "XML could not be open. Check the file name.");
         return donnee;
        }
    //tests if the XML attribution to the DOM object is done
    if (!domJeuVie.setContent(&xml_docJeuVie))
        {xml_docJeuVie.close();
         QMessageBox::warning(this, "Error at XML open", "The XML file could be attributed to the QDomDocument object.");
         return donnee;
        }
    xml_docJeuVie.close(); //closes XML file, everything is in the DOM

    //generates first tag name
    QDomElement dom_element = domJeuVie.documentElement(); //Creates objects, gets everything in the XML
    //takes first XML node, <name>
    QDomElement noeudJeuVie = dom_element.firstChild().toElement();
    while(!noeudJeuVie.isNull()){
        //next node
        noeudJeuVie= noeudJeuVie.nextSibling().toElement();
        bool ok;
        if(noeudJeuVie.tagName()=="type"){
           // QMessageBox::information(this, "attribut type", noeudJeuVie.tagName());
        }
        if(noeudJeuVie.tagName()=="Min_Viv_Rester"){
            donnee->minA = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="Max_Viv_Rester"){
            donnee->maxA = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="Min_Viv_Renaitre") {
            donnee->minD = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="Max_Viv_Renaitre") {
            donnee->maxD = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="Nbr_Ligne") {
            donnee->height = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="Nbr_Colonne") {
            donnee->length = noeudJeuVie.text().toUInt(&ok, 10);
        }
        if(noeudJeuVie.tagName()=="step") {
            donnee->step = noeudJeuVie.text().toUInt(&ok, 10);
        }
    }
    return donnee;
}


dataForestFire* Xml_Dom::readFeu(){
    dataForestFire* donnee;
    donnee = new dataForestFire;
    QDomDocument domFeu("mon_xml"); //creates DOM objet
    QFile xml_docFeu("testFW.xml"); //file choice
    //tests if the file is correctly open for reading
    if(!xml_docFeu.open(QIODevice::ReadOnly))
        {QMessageBox::warning(this,  "Error at XML open", "XML could not be open. Check the file name.");
         return donnee;
        }
    //tests if the XML attribution to the DOM object is done
    if (!domFeu.setContent(&xml_docFeu))
        {xml_docFeu.close();
         QMessageBox::warning(this, "Error at XML open", "The XML file could be attributed to the QDomDocument object.");
         return donnee;
        }
    xml_docFeu.close(); //closes XML file, everything is in the DOM

      //data recuperation
    QDomElement dom_element = domFeu.documentElement(); //Creates objects, gets everything in the XML
    //generates first tag name
    //takes first XML node, <name>
    QDomElement noeudFeu = dom_element.firstChild().toElement();
    while(!noeudFeu.isNull()){
        //next node
        noeudFeu= noeudFeu.nextSibling().toElement();
        bool ok;
        if(noeudFeu.tagName()=="type"){
        }
        if(noeudFeu.tagName()=="Nbr_Ligne"){
            donnee->height = noeudFeu.text().toUInt(&ok, 10);
        }
        if(noeudFeu.tagName()=="Nbr_Colonne"){
            donnee->length = noeudFeu.text().toUInt(&ok, 10);
        }
        if(noeudFeu.tagName()=="step"){
            donnee->step = noeudFeu.text().toUInt(&ok, 10);
        }
    }
    return donnee;
}

void Xml_Dom::writeDim1(const QString& n, const QString& t, const QString& num,const QString& c, const QString& nbrE,const QString& step){
    QDomDocument domDim1_2("mon_xml_1d"); //creates DOM objet

    //writes XML nodes in the DOM object
    QDomElement firstNode = domDim1_2.createElement("AutoCell_1D"); //principal node
    domDim1_2.appendChild(firstNode);

    QDomNode firstSubNode = domDim1_2.createElement( ("name"));//node name
    QDomText firstNodeText = domDim1_2.createTextNode(n); //creates text for noeud
    firstNode.appendChild(firstSubNode);//name AutoFire node child
    firstSubNode.appendChild(firstNodeText);//inserts text as node name

    QDomElement deuxSubNode = domDim1_2.createElement("type"); //node type
    QDomText deuxNodeText = domDim1_2.createTextNode(t);
    firstNode.appendChild(deuxSubNode);//type of Dim1 node child
    deuxSubNode.appendChild(deuxNodeText);

    QDomElement troisSubNode = domDim1_2.createElement("numero");//node number
    QDomText troisNodeText = domDim1_2.createTextNode(num);
    firstNode.appendChild(troisSubNode);//Dim1 node child number
    troisSubNode.appendChild(troisNodeText);

    QDomElement quatreSubNode = domDim1_2.createElement("Nbr_Colonne");//column node
    QDomText quatreNodeText = domDim1_2.createTextNode(c);
    firstNode.appendChild(quatreSubNode);//Nbr_Colonne child of Dim1 node
    quatreSubNode.appendChild(quatreNodeText);

    QDomElement cinqSubNode = domDim1_2.createElement("nbr_etat");//noeud_nbr_etat
    QDomText cinqNodeText = domDim1_2.createTextNode(nbrE);
    firstNode.appendChild(cinqSubNode);//nbr_etat enfant du noeud Dim1
    cinqSubNode.appendChild(cinqNodeText);

    QDomElement sixSubNode = domDim1_2.createElement("step");//noeud_pas
    QDomText sixNodeText = domDim1_2.createTextNode(step);
    firstNode.appendChild(sixSubNode);//nbr step enfant du noeud Dim1
    sixSubNode.appendChild(sixNodeText);

    QFile xml_docDim1_2("test1dW.xml"); //file choice
    //tests if the file is correctly open for writing
    if(!xml_docDim1_2.open(QIODevice::WriteOnly))
        {QMessageBox::warning(this, "Error at XML open", "XML could not be open. Check the file name.");
         return;
    }
    else {
        QTextStream textStream(&xml_docDim1_2);
        //doc.toString() transforms XML tree to text
        textStream << domDim1_2.toString();
        xml_docDim1_2.close();
    }
}

void Xml_Dom::writeGameLife(const QString& n, const QString& t, const QString& mi1, const QString& ma1,const QString& mi2, const QString& ma2, const QString& c, const QString& l,const QString& step){
    QDomDocument domJV2("mon_xml_JeuDeLaVie"); //creates DOM objet

    //writes XML nodes in the DOM object
    QDomElement firstNode = domJV2.createElement("gameLifeInstance"); //principal node
    domJV2.appendChild(firstNode);

    QDomNode firstSubNode = domJV2.createElement( ("name"));//node name
    QDomText firstNodeText = domJV2.createTextNode(n); //creates text for noeud
    firstNode.appendChild(firstSubNode);//name JeuVie node child
    firstSubNode.appendChild(firstNodeText);//inserts text as node name

    QDomElement deuxSubNode = domJV2.createElement("type"); //node type
    QDomText deuxNodeText = domJV2.createTextNode(t);
    firstNode.appendChild(deuxSubNode);//type of JeuVie node child
    deuxSubNode.appendChild(deuxNodeText);

    QDomElement troisSubNode = domJV2.createElement("Min_Viv_Rester");//noeud nbr_Ligne
    QDomText troisNodeText = domJV2.createTextNode(mi1);
    firstNode.appendChild(troisSubNode);//Min_Viv_Rester enfant du noeud JeuVie
    troisSubNode.appendChild(troisNodeText);

    QDomElement quatreSubNode = domJV2.createElement("Max_Viv_Rester");//noeud nbr_Ligne
    QDomText quatreNodeText = domJV2.createTextNode(ma1);
    firstNode.appendChild(quatreSubNode);//Max_Viv_Rester enfant du noeud JeuVie
    quatreSubNode.appendChild(quatreNodeText);

    QDomElement cinqSubNode = domJV2.createElement("Min_Viv_Renaitre");//noeud nbr_Ligne
    QDomText cinqNodeText = domJV2.createTextNode(mi2);
    firstNode.appendChild(cinqSubNode);//Min_Viv_Renaitre enfant du noeud JeuVie
    cinqSubNode.appendChild(cinqNodeText);

    QDomElement sixSubNode = domJV2.createElement("Max_Viv_Renaitre");//noeud nbr_Ligne
    QDomText sixNodeText = domJV2.createTextNode(ma2);
    firstNode.appendChild(sixSubNode);//Max_Viv_Renaitre enfant du noeud JeuVie
    sixSubNode.appendChild(sixNodeText);

    QDomElement septSubNode = domJV2.createElement("Nbr_Ligne");//noeud nbr_Ligne
    QDomText septNodeText = domJV2.createTextNode(l);
    firstNode.appendChild(septSubNode);//Nbr_Ligne enfant du noeud JeuVie
    septSubNode.appendChild(septNodeText);

    QDomElement huitSubNode = domJV2.createElement("Nbr_Colonne");//noeud_Colonne
    QDomText huitNodeText = domJV2.createTextNode(c);
    firstNode.appendChild(huitSubNode);//Nbr_Colonne enfant du noeud JeuVie
    huitSubNode.appendChild(huitNodeText);

    QDomElement neufSubNode = domJV2.createElement("step");//noeud_pas
    QDomText neufNodeText = domJV2.createTextNode(step);
    firstNode.appendChild(neufSubNode);//noeud step enfant du noeud JeuVie
    neufSubNode.appendChild(neufNodeText);

    QFile xml_docJV2("test2dW.xml"); //file choice
    //tests if the file is correctly open for writing
    if(!xml_docJV2.open(QIODevice::WriteOnly))
        {QMessageBox::warning(this, "Error at XML open", "XML could not be open. Check the file name.");
         return;
    }
    else {
        QTextStream textStream(&xml_docJV2);
        //doc.toString() transforms XML tree to text
        textStream << domJV2.toString();
        xml_docJV2.close();
    }
}

void Xml_Dom::writeFeu(const QString& n, const QString& t, const QString& c, const QString& l,const QString& step){
    QDomDocument domFeu2("mon_xml"); //creates DOM objet

    //writes XML nodes in the DOM object
    QDomElement firstNode = domFeu2.createElement("AutoFire"); //principal node
    domFeu2.appendChild(firstNode);

    QDomNode firstSubNode = domFeu2.createElement( ("name"));//noeud name
    QDomText firstNodeText = domFeu2.createTextNode(n); //creation text pour noeud
    firstNode.appendChild(firstSubNode);//name enfant du noeud AutoFire
    firstSubNode.appendChild(firstNodeText);//insertion du text du noeud name

    QDomElement deuxSubNode = domFeu2.createElement("type"); //noeud type
    QDomText deuxNodeText = domFeu2.createTextNode(t);
    firstNode.appendChild(deuxSubNode);//type enfant du noeud AutoFire
    deuxSubNode.appendChild(deuxNodeText);

    QDomElement troisSubNode = domFeu2.createElement("Nbr_Ligne");//noeud nbr_Ligne
    QDomText troisNodeText = domFeu2.createTextNode(l);
    firstNode.appendChild(troisSubNode);//Nbr_Ligne enfant du noeud AutoFire
    troisSubNode.appendChild(troisNodeText);

    QDomElement quatreSubNode = domFeu2.createElement("Nbr_Colonne");//noeud_Colonne
    QDomText quatreNodeText = domFeu2.createTextNode(c);
    firstNode.appendChild(quatreSubNode);//Nbr_Colonne enfant du noeud AutoFire
    quatreSubNode.appendChild(quatreNodeText);

    QDomElement cinqSubNode = domFeu2.createElement("step");//noeud_pas, speed en auto
    QDomText cinqNodeText = domFeu2.createTextNode(step);
    firstNode.appendChild(cinqSubNode);//noeud step enfant du noeud AutoFire
    cinqSubNode.appendChild(cinqNodeText);

    QFile xml_docFeu2("testFW.xml"); //file choice
    //tests if the file is correctly open for writing
    if(!xml_docFeu2.open(QIODevice::WriteOnly))
        {QMessageBox::warning(this, "Error at XML open", "XML could not be open. Check the file name.");
         return;
    }
    else {
        QTextStream textStream(&xml_docFeu2);
        //doc.toString() transforms XML tree to text
        textStream << domFeu2.toString();
        xml_docFeu2.close();
    }
}
