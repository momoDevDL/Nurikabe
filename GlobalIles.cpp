#include"GlobalIles.h"

GlobalIles::GlobalIles(){}
GlobalIles::~GlobalIles(){} 

void GlobalIles::AddIle(Iles &I){
  I.setIndice((int)GlobalIle.size());
  GlobalIle.push_back(I);

  //  std::cout << GlobalIle.size() << std::endl;

}

std::vector<Iles>&  GlobalIles::getGlobalIle(){
  return GlobalIle;
}

void GlobalIles::printGlobalIles(){

  size_t i =0;
    while(i< GlobalIle.size()){
      GlobalIle[i].print();
      i++;
    }
}
 
