#ifndef __GLOBALILES_H
#define __GLOBALILES_H

#include "Iles.h"
#include <vector>
#include <iostream>

class GlobalIles{

 private:
  std::vector<Iles> GlobalIle;

 public:
  
  GlobalIles();
  ~GlobalIles();
  std::vector<Iles>& getGlobalIle();
  void AddIle(Iles& I);
  void printGlobalIles();
};

#endif
   
