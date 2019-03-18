#include"Iles.h"
#include<iostream>
Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),remaining(b->getCellNum() -1),indice(i){}

int Iles::getRemaining(){
  return remaining;
}

int Iles::getIndice(){
  return indice;
}

void Iles::setIndice(int i){
  indice = i ;
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


void Iles::print(){

  whiteCells.printListe();
  std::cout<< " -> reste : "<< remaining << " >-----< indice De creation : " << indice << std::endl;

}

void Iles::addBlockCellToIles(BlockCell &b, GlobalRiviere &GR){
  whiteCells.fusion(whiteCells.getHead(), &b, GR);
}

int Iles::getTailleIles()const{
  return whiteCells.getSize();
}
