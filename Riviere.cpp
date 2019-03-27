#include"Riviere.h"
#include "ListeCell.h"
#include "GlobalRiviere.h"
#include<iostream>

Riviere::Riviere():riviere(ListeCell(NULL)),indiceDeCreation(1){}
Riviere::Riviere(BlockCell *b, int indice):riviere(ListeCell(b)),indiceDeCreation(indice){}


int Riviere::getIndice()const{ return indiceDeCreation; }

void Riviere::supprimeRiv(GlobalRiviere &GR){
  
  GR.getGlobalRiv().erase(GR.getGlobalRiv().begin()+(getIndice()-1));
  
  /*  for( size_t i = getIndice() ; i < GR.getGlobalRiv().size();i++){
    indiceDeCreation -- ;
    }*/
  
}

/*bool Riviere::A_UnSeulReferant()const{
  bool unSeulRef = true;
  int nbRef = 0;
  BlockCell* buf = riviere.getHead();

  while (riviere.getSucc(buf) != NULL){
    if (buf->getRefCell == NULL){
      nbRef++;
    }
    buf = riviere.getSucc(buf);
  }
  if (nbRef != 1){
    unSeulRef = false;
  }
  return unSeulRef;
}

Cell* Riviere::getCellReferante()const{

  BlockCell* buf = riviere.getHead();
  if (this->A_UnSeulReferant()){
    while (buf->getRefCell !=){
      buf = riviere.getSucc(buf);
    }
    return buf->getCellPointer();     
  }
  }*/

void Riviere::addBlockCellToRiviere(BlockCell &b, GlobalRiviere &GR){
  riviere.fusion(riviere.getHead(), &b, GR);
}

int Riviere::getTailleRiviere()const{
  return riviere.getSize();
}

void Riviere::printRiv(){
  
  riviere.printListe();
  std::cout<< ">-----< indice De creation : " << indiceDeCreation << std::endl;
}

ListeCell* Riviere::getRiviere(){
  
  return &riviere;
}
