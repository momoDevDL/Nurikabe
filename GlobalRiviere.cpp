#include"GlobalRiviere.h"

GlobalRiviere::GlobalRiviere(){}
GlobalRiviere::~GlobalRiviere(){} 

void GlobalRiviere::AddRiviere(Riviere &r){
  GlobalRiv.push_back(r);
}

std::vector<Riviere>&  GlobalRiviere::getGlobalRiv(){
  return GlobalRiv;
}

void GlobalRiviere::printGlobalRiviere(){
  size_t i =0;
  
  while(i < GlobalRiv.size()){
    GlobalRiv[i].printRiv();
    i++;
  }
  
}
