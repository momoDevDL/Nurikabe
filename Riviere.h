#ifndef __RIVIERE_H
#define __RIVIERE_H
#include "ListeCell.h"

class Riviere{
 private :
  ListeCell riviere;
 public :
  Riviere();
  Riviere(BlockCell *b);
  //methods

  bool A_UnSeulReferant()const;

  BlockCell* getCellReferante()const;

  void addBlockCellToRiviere(BlockCell &b);



};
#endif

