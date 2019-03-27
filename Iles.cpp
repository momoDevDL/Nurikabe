#include"Iles.h"
#include"prog.h"

#include<iostream>

Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),remaining(b->getCellNum() -1),indice(i){}
/*Iles::~Iles(){
  delete whiteCells;
  }**/
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
  std::cout<<"#########################################"<<std::endl;
  std::cout<<whiteCells.getSize()<<std::endl;
  whiteCells.fusion(whiteCells.getHead(), &b, GR);
  std::cout<<whiteCells.getSize()<<std::endl;
  /* std::cout<<whiteCells.getHead()<<std::endl;*/
  setRemaining((whiteCells.getHead()->getCellNum())-(whiteCells.getSize()));
  std::cout<<whiteCells.getSize()<<std::endl;
  /* std::cout<<whiteCells.getHead()->getRemaining()<<std::endl;*/
  std::cout<<"#########################################"<<std::endl;
}

int Iles::getTailleIles()const{
  return whiteCells.getSize();
}
