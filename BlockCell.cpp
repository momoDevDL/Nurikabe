#include <iostream>
using namespace std;
#include"BlockCell.h"

BlockCell::BlockCell():cellPointer(NULL),nextBlock(NULL){}

BlockCell::BlockCell(Cell* c):cellPointer(c),nextBlock(NULL){}

BlockCell* BlockCell::getNextBlock()const{ return nextBlock;}
Cell* BlockCell::getCellPointer()const{ return cellPointer;}

void BlockCell::setNextBlockCell(BlockCell* BC){nextBlock=BC;}
void BlockCell::setCellPointer(Cell* cell){ cellPointer=cell;}

void BlockCell::setEtatCell(int etat){
  getCellPointer()->setEtat(etat);
}

void BlockCell::setRefCell(Cell* c){
  getCellPointer()->setRef(c);
}

void BlockCell::setRivCell(Riviere* r){
  getCellPointer()->setRiv(r);
}


void BlockCell::setIleCell(Ile* i){
  getCellPointer()->setIle(i);
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

Ile* BlockCell::getIleCell(){
  return getCellPointer()->getRiv();
}

void BlockCell::printBlock()const{
  cout<<" => etat de cell : " <<getEtatCell()<<"/==/ Num= "<<getCellNum()<<"\t";
  getCellPointer()->print();
}

void BlockCell::printBlockListe()const{
  getCellPointer()->print();
}
