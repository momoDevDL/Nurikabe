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
 
  void friendsIles(Grille &g);
  
  bool estPleine();
  
  void Complet(Grille &g,GlobalRiviere &gr,GlobalIles &gi,int x ,int y,int& indice);
  
  void print();

};


#endif
