#include"Iles.h"
#include"prog.h"
#include<iostream>

class GlobalIles;

Iles::Iles(){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),remaining(b->getCellNum() -1),indice(i){}


int Iles::getRemaining()const{
  return remaining;
}

int Iles::getIndice()const{
  return indice;
}

void Iles::setIndice(int i){
  indice = i ;
}

size_t Iles::getNumCell(){
  return   whiteCells.getHead()->getCellPointer()->getCellNum();
}

void Iles::setRemaining(int r){
  remaining = r;
}

bool Iles::estPleine(){
  bool plein = false;
  if (remaining == 0){
    plein = true;
  }
  return plein;
}

ListeCell* Iles::getWhiteCells(){
  return &whiteCells;
}

void Iles::setWhiteCells(ListeCell *l){
  whiteCells = *l;
}

void Iles::print(){

  whiteCells.printListe();
  std::cout<< " -> reste : "<< remaining << " >-----< indice De creation : " << indice << std::endl;

}

void Iles::addBlockCellToIles(BlockCell* b, GlobalRiviere &GR,GlobalIles &GI){
 
  this->print();
 
  whiteCells.fusion(whiteCells.getHead(),b, GR,GI);

  setRemaining((whiteCells.getHead()->getCellNum())-(whiteCells.getSize()));
  
  GI.getGlobalIle()[indice]->setRemaining((whiteCells.getHead()->getCellNum())-(whiteCells.getSize()));
  GI.getGlobalIle()[indice]->getWhiteCells()->setSize(whiteCells.getSize());


}

int Iles::getTailleIles()const{
  return whiteCells.getSize();
}
 
