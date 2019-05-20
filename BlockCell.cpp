#include <iostream>
using namespace std;
#include"BlockCell.h"

BlockCell::BlockCell():cellPointer(NULL),nextBlock(NULL){}

BlockCell::BlockCell(Cell* c):cellPointer(c),nextBlock(NULL){}
BlockCell& BlockCell::operator=(const BlockCell& bc){
  if(this != &bc){
    
    cellPointer = bc.getCellPointer();
    nextBlock = bc.getNextBlock();

  }

  return *this;
}

BlockCell::~BlockCell(){
  // cellPointer = NULL;
  //delete cellPointer;
}

BlockCell* BlockCell::getNextBlock()const{ return nextBlock;}
Cell* BlockCell::getCellPointer()const{ return cellPointer;}


void BlockCell::setNextBlockCell(BlockCell* BC){nextBlock=BC;}
void BlockCell::setCellPointer(Cell* c){
 
  cellPointer = c;

}

void BlockCell::setEtatCell(int etat){
  getCellPointer()->setEtat(etat);
}

void BlockCell::setRefCell(Cell* c){
  getCellPointer()->setRef(c);
}

void BlockCell::setRivCell(Riviere* r){
  getCellPointer()->setRiv(r);
}


void BlockCell::setIlesCell(Iles* i){
  getCellPointer()->setIles(i); 
}
  
int BlockCell::getEtatCell()const{
  return getCellPointer()->getEtat();
}

int BlockCell::getCellNum()const{
  return getCellPointer()->getCellNum();
}

Cell* BlockCell::getRefCell(){
  return getCellPointer()->getRef();
}

Riviere* BlockCell::getRivCell(){
  return getCellPointer()->getRiv();
}

Iles* BlockCell::getIlesCell(){
  return getCellPointer()->getIles();
}

void BlockCell::printBlock()const{
  if(getEtatCell() != 4){
    cout<<" => etat de cell : " <<getEtatCell()<<"/==/ Num= "<<getCellNum()<<"\t";
    getCellPointer()->print();
    cout << "( "<<getCellPointer()->getPosX() << " , "<< getCellPointer()->getPosY() <<" ) ";
    cout<<endl;
  }
}

void BlockCell::printBlockListe()const{
  getCellPointer()->print();
}
