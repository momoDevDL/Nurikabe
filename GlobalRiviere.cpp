#include"GlobalRiviere.h"

GlobalRiviere::GlobalRiviere(){}
GlobalRiviere::~GlobalRiviere(){} 

void GlobalRiviere::AddRiviere(Riviere *r){
  GlobalRiv.push_back(r);
}

std::vector<Riviere*>&  GlobalRiviere::getGlobalRiv(){
  return GlobalRiv;
}

void GlobalRiviere::printGlobalRiviere(){
  size_t i =0;
  int max = 0;
  int  cmpt = 0;
  while(i < GlobalRiv.size()){
    if(max < GlobalRiv[i]->getRiviere()->getSize()){
      max = GlobalRiv[i]->getRiviere()->getSize();
      cmpt = i;
    }
    i++;
  }

  GlobalRiv[cmpt]->printRiv();
  
}
