#include"Iles.h"
#include"prog.h"
#include<iostream>

class GlobalIles;

Iles::Iles(){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),remaining(b->getCellNum() -1),indice(i){}
/*Iles::~Iles(){
  delete whiteCells;
  }**/

/*Iles& Iles::operator=( Iles& i){
  if(this != &i){
    //std::cout<<"XR"<<std::endl;
    whiteCells = *(i.getWhiteCells());
    // std::cout<<"X1R"<<std::endl;
    remaining = i.getRemaining();
    indice = i.getIndice();//
    //this->print();
  }
  return *this;
}
*/

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
  //  std::cout<<"#########################################"<<std::endl;
  this->print();
  std::cout<<whiteCells.getSize()<<std::endl;
  whiteCells.fusion(whiteCells.getHead(),b, GR,GI);
  std::cout<<whiteCells.getSize()<<std::endl;
  /* std::cout<<whiteCells.getHead()<<std::endl;*/
  setRemaining((whiteCells.getHead()->getCellNum())-(whiteCells.getSize()));
  GI.getGlobalIle()[indice]->setRemaining((whiteCells.getHead()->getCellNum())-(whiteCells.getSize()));
  GI.getGlobalIle()[indice]->getWhiteCells()->setSize(whiteCells.getSize());
  std::cout<<"WHITECELLS SIZE =======> "<<whiteCells.getSize()<<std::endl;
  std::cout<<"WHITECELLS RemaINING =======> "<<getRemaining()<<std::endl;
  //GI.printGlobalIles();
  /* std::cout<<whiteCells.getHead()->getRemaining()<<std::endl;*/
  // std::cout<<"#########################################"<<std::endl;
}

int Iles::getTailleIles()const{
  return whiteCells.getSize();
}
 
