#ifndef __ILES_H
#define __ILES_H

#include"ListeCell.h"
class Iles {
 private :
  ListeCell whiteCells;
  int remaining;
  int indice;

 public :
  Iles();
  Iles(BlockCell* b, int i);
};


#endif
