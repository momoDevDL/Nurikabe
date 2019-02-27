#ifndef __GLOBALRIVIERE_H
#define __GLOBALRIVIERE_H

#include "Riviere.h"
#include <vector>
#include <iostream>

class GlobalRiviere{

 private:
  std::vector<Riviere> GlobalRiv;

 public:
  
  GlobalRiviere();
  ~GlobalRiviere();
  std::vector<Riviere>& getGlobalRiv();
  void AddRiviere(Riviere &r);
  
};

#endif
