#ifndef __ILES_H
#define __ILES_H

#include"grille.h"
#include"ListeCell.h"
class GlobalIles;
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

  void setIndice(int);

  void setRemaining(int r);

  ListeCell* getWhiteCells();
 
  bool estPleine();
  
  void print();

  void addBlockCellToIles(BlockCell &b, GlobalRiviere &GI);

  int getTailleIles()const;

};


#endif
