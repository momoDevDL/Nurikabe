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
  // Iles& operator=(Iles &i);
    
  int getRemaining()const;

  int getIndice()const;

  void setIndice(int);

  void setRemaining(int r);

  ListeCell* getWhiteCells();
  
  void setWhiteCells(ListeCell *l);
  
  size_t getNumCell();
  
  bool estPleine();
  
  void print();

  void addBlockCellToIles(BlockCell *b, GlobalRiviere &GR, GlobalIles &GI);

  int getTailleIles()const;

};


#endif
