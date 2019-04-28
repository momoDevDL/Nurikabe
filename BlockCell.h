#ifndef __BLOCKCELL_H
#define __BLOCKCELL_H
#include "cell.h"
class BlockCell{
 private:
  Cell* cellPointer;
  BlockCell* nextBlock;
 
 public:
  //constructeurs

  BlockCell();
  BlockCell(Cell* c);
  ~BlockCell();
  BlockCell& operator=(const BlockCell& bc);
  BlockCell* getNextBlock()const;
  Cell* getCellPointer()const;

  void setNextBlockCell(BlockCell*);
  
  void setCellPointer(Cell*);
  void setEtatCell(int etat);
  void setRefCell(Cell*);
  void setRivCell(Riviere*);
  void setIlesCell(Iles*);
  int getEtatCell()const;
  int getCellNum()const; 
  Cell* getRefCell();
  Riviere* getRivCell();
  Iles* getIlesCell();
  
  void printBlock()const;
  void printBlockListe()const;

};

#endif
