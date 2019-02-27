#include"Riviere.h"
#include "ListeCell.h"
#include "GlobalRiviere.h"
#include<iostream>

Riviere::Riviere():riviere(ListeCell(NULL)),indiceDeCreation(-1){}
Riviere::Riviere(BlockCell *b, int indice):riviere(ListeCell(b)),indiceDeCreation(indice){}


int Riviere::getIndice()const{ return indiceDeCreation; }

void Riviere::supprimeRiv(GlobalRiviere &GR){
  
  GR.getGlobalRiv().erase(GR.getGlobalRiv().begin() + (getIndice() -1));

  for( size_t i = getIndice() ; i < GR.getGlobalRiv().size();i++){
    indiceDeCreation -- ;
  }
  
}
