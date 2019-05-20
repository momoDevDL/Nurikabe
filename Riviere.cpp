#include"Riviere.h"
#include "ListeCell.h"
#include "GlobalRiviere.h"
#include<iostream>

Riviere::Riviere(){}
//Creation d'une nouvelle Riviere en initialisant la liste de ses elements par le
//BlockCell correspansdant à la cellule qu'on vient de noicir 
Riviere::Riviere(BlockCell *b, int indice):riviere(ListeCell(b)),indiceDeCreation(indice){}

//recuperer l'ordre de la creation de la liste 
int Riviere::getIndice()const{ return indiceDeCreation; }


//modifier l'indice de creation de la riviere
void Riviere::setIndice(int i){ indiceDeCreation = i;}



/*void Riviere::supprimeRiv(GlobalRiviere &GR){
  
  GR.getGlobalRiv().erase(GR.getGlobalRiv().begin()+(getIndice()-1));
  
  for( size_t i = getIndice() ; i < GR.getGlobalRiv().size();i++){
    indiceDeCreation -- ;
    }
*/


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
*/

//Rajouter une cellule à une riviere 
void Riviere::addBlockCellToRiviere(BlockCell *b, GlobalRiviere &GR,GlobalIles &GI){
  
  riviere.fusion(riviere.getHead(), b, GR,GI);

  GR.getGlobalRiv()[indiceDeCreation]->getRiviere()->setSize(riviere.getSize());
  
}


int Riviere::getTailleRiviere()const{
  return riviere.getSize();
}

void Riviere::printRiv(){
  
  riviere.printListe();
  //  std::cout<< ">-----< indice De creation : " << indiceDeCreation << std::endl;
}

ListeCell* Riviere::getRiviere(){
  
  return &riviere;
}

//modification de la liste des elements d'une riviere
//en affectant à sa liste une nouvelle Liste 
void Riviere::setRiviere(ListeCell *l){

  riviere = *l;
}
