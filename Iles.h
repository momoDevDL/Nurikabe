#ifndef __ILES_H
#define __ILES_H

#include"ListeCell.h"
class Iles {
 private :
  ListeCell whiteCells;
  int remaining;

 public :
  Iles();
  Iles(BlockCell* b);
};


#endif
