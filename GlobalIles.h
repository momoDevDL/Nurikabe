#ifndef __GLOBALILES_H
#define __GLOBALILES_H

#include "Iles.h"
#include <vector>
#include <iostream>

class GlobalIles{

 private:
  std::vector<Iles*> GlobalIle;

 public:
  
  GlobalIles();
  ~GlobalIles();
  const std::vector<Iles*>& getGlobalIle()const;
  GlobalIles& operator=(const GlobalIles& I);
  void AddIle(Iles* I);
  void printGlobalIles();
  bool ToutEstComplet();
  int SommeDiles();
};

#endif
   
