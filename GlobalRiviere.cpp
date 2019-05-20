#include"GlobalRiviere.h"

GlobalRiviere::GlobalRiviere():GlobalRiv(std::vector<Riviere*>()){} 

void GlobalRiviere::AddRiviere(Riviere *r){
  GlobalRiv.push_back(r);
}

const std::vector<Riviere*>&  GlobalRiviere::getGlobalRiv()const{
  return GlobalRiv;
}

GlobalRiviere::~GlobalRiviere(){
  std::vector<Riviere*>().swap(GlobalRiv);
}

GlobalRiviere& GlobalRiviere::operator=(const GlobalRiviere& R){
  if(this != &R){
    GlobalRiv.erase(GlobalRiv.begin(),GlobalRiv.end());
    
    for (size_t i = 0 ;i<R.getGlobalRiv().size();i++){
      
      AddRiviere(new Riviere);
      GlobalRiv[i]->setRiviere( R.getGlobalRiv()[i]->getRiviere());
   
      GlobalRiv[i]->setIndice(R.getGlobalRiv()[i]->getIndice());
    }
    std::cout<<GlobalRiv.size()<<std::endl;
    
 
    
  }
  return *this;
}

void GlobalRiviere::printGlobalRiviere(){
  size_t i =0;
  size_t max = 0;
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

bool GlobalRiviere::RiviereConnexe(int max){
  int taille = 0;
  for(size_t i = 0 ;  i < GlobalRiv.size() ; i++){
    taille = GlobalRiv[i]->getRiviere()->getSize() ;
   
    if (taille == max) return true; 
  }
  
  return false;
}
