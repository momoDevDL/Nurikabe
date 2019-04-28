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
    //std::cout<<"GlobalIles SIZE == > "<<GlobalIle.size()<<std::endl;
    // GlobalIle = I.getGlobalIle();
    for (size_t i = 0 ;i<R.getGlobalRiv().size();i++){
      //  std::cout<<i<<std::endl;
      AddRiviere(new Riviere);
      GlobalRiv[i]->setRiviere( R.getGlobalRiv()[i]->getRiviere());
      // std::cout<<"AFTER ADD"<<std::endl;
      GlobalRiv[i]->setIndice(R.getGlobalRiv()[i]->getIndice());
    }
    std::cout<<GlobalRiv.size()<<std::endl;
    
    /* std::cout<<GlobalIle.size()<<std::endl;
       for (int i = 0 ;i<(int)I.getGlobalIle().size();i++){
      std::cout<<GlobalIle[i]<<"//"<<I.getGlobalIle()[i]<<std::endl;
    }*/
    /*  for (int i = 0 ;i<GlobalIle.size();i++){
      // std::cout<<"TOP"<<std::endl;
      *(GlobalIle[i]) = *(I.getGlobalIle()[i]);
       GlobalIle[i]->print();
       I.getGlobalIle()[i]->print();
      
       }*/
    
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
    // std::cout<< taille<<std::endl;
    if (taille == max) return true; 
  }
  
  return false;
}
