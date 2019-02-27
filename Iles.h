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

  int getRemaining();

  int getIndice();

  void setRemaining(int r);

  void estPresqueComplet1();

  void estPresqueComplet2();

};


#endif
