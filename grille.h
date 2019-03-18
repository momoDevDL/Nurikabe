#ifndef __GRILLE_H
#define __GRILLE_H
#include"cell.h"
#include"BlockCell.h"
#include<iostream>

class Grille{
 private:
  size_t dimensionX;
  size_t dimensionY;
  Cell ** tabCell;
  BlockCell ** tabBlockCell;

 public:
  //constructeurs
  Grille();
  Grille(size_t dX,size_t dY);
  //destructeur
  ~Grille();
  //accesseur en lecture
  size_t getDimensionX()const;
  size_t getDimensionY()const;
  Cell& getCell(size_t,size_t)const;
  BlockCell& getBlockCell(size_t,size_t)const;
  void setCellPointerInBlockCell(size_t,size_t);
  
  
  //methodes
  void random_init(size_t nb_cellules_numerotee);
  void GrillePrint();
  void addVal(size_t val,size_t x,size_t y);
  void addEtat(size_t etat,size_t,size_t);
  bool CHECK_BOUND(size_t,size_t,size_t,size_t)const;
};

#endif
