#ifndef __RIVIERE_H
#define __RIVIERE_H

#include"ListeCell.h"

class Riviere{
 private :
  ListeCell riviere;
  int indiceDeCreation;
 public :
  Riviere();
  Riviere(BlockCell *b,int indice);
  //methods

  bool A_UnSeulReferant()const;

  BlockCell* getCellReferante()const;

  void addBlockCellToRiviere(BlockCell &b);



};
#endif

