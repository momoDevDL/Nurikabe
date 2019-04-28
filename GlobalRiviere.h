#ifndef __GLOBALRIVIERE_H
#define __GLOBALRIVIERE_H

#include "Riviere.h"
#include <vector>
#include <iostream>

class GlobalRiviere{

 private:
  std::vector<Riviere*> GlobalRiv;

 public:
  
  GlobalRiviere();
  ~GlobalRiviere();
  const std::vector<Riviere*>& getGlobalRiv()const;
  GlobalRiviere& operator=(const GlobalRiviere& R);
  void AddRiviere(Riviere *r);
  void printGlobalRiviere();
  bool RiviereConnexe(int max);
  
};


#endif
