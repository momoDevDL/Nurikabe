#include"GlobalRiviere.h"

GlobalRiviere::GlobalRiviere(){}
GlobalRiviere::~GlobalRiviere(){} 

void GlobalRiviere::AddRiviere(Riviere &r){
  GlobalRiv.push_back(r);
}

std::vector<Riviere>&  GlobalRiviere::getGlobalRiv(){
  return GlobalRiv;
}