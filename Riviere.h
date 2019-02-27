#ifndef __RIVIERE_H
#define __RIVIERE_H

class GlobalRiviere;
#include "ListeCell.h"

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

  int getIndice()const;

  void addBlockCellToRiviere(BlockCell &b);

  void supprimeRiv(GlobalRiviere &GR);


};
#endif

