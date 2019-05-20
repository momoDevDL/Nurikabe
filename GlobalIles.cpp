#include"GlobalIles.h"

GlobalIles::GlobalIles():GlobalIle(std::vector<Iles*>()){}
GlobalIles::~GlobalIles(){
  std::vector<Iles*>().swap(GlobalIle);
} 

void GlobalIles::AddIle(Iles *I){
  I->setIndice((int)GlobalIle.size());
  GlobalIle.push_back(I);

 

}

int GlobalIles::SommeDiles(){
  int som = 0;
  for(size_t i = 0 ;  i < GlobalIle.size() ; i++){
    som += GlobalIle[i]->getNumCell() ;
  }
  
  return som ;
}

GlobalIles& GlobalIles::operator=(const GlobalIles& I){
  if(this != &I){
    GlobalIle.erase(GlobalIle.begin(),GlobalIle.end());
   
   
    for (size_t i = 0 ;i<I.getGlobalIle().size();i++){
      
      AddIle(new Iles);
      GlobalIle[i]->setWhiteCells( I.getGlobalIle()[i]->getWhiteCells());
      GlobalIle[i]->setRemaining(I.getGlobalIle()[i]->getRemaining());
      GlobalIle[i]->setIndice(I.getGlobalIle()[i]->getIndice());
     
    }
   
    
  
    
  }
  return *this;
}


const std::vector<Iles*>&  GlobalIles::getGlobalIle()const{
  return GlobalIle ;
}

void GlobalIles::printGlobalIles(){

  size_t i =0;
    while(i< GlobalIle.size()){
      GlobalIle[i]->print();
      i++;
    }
}
 
bool GlobalIles::ToutEstComplet(){

  
  size_t i =0;
    while(i< GlobalIle.size() && GlobalIle[i]->estPleine() == true){
      i++;
    }
    return i == GlobalIle.size();
}
