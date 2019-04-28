#ifndef __GRILLE_H
#define __GRILLE_H
#include"cell.h"
#include"BlockCell.h"
#include<iostream>

class Grille{
 private:
  int dimensionX;
  int dimensionY;
  Cell ** tabCell;
  BlockCell ** tabBlockCell;

 public:
  //constructeurs
  Grille();
  Grille(int dX,int dY);
  Grille& operator=(const Grille& g);
  //destructeur
  ~Grille();
  //accesseur en lecture
  int getDimensionX()const;
  int getDimensionY()const;
  Cell& getCell(int,int)const;
  BlockCell& getBlockCell(int,int)const;
  void setCellPointerInBlockCell(int,int);
  void vider();
  //methodes
  void random_init(size_t nb_cellules_numerotee);
  void GrillePrint();
  void addVal(size_t val,int x,int y);
  void addEtat(size_t etat,int,int);
  bool CHECK_BOUND(int,int,int,int)const;
  bool rempli();
};
#endif
