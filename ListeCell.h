#ifndef __LISTECELL_H
#define __LISTECELL_H
#include<iostream>
#include "BlockCell.h"
class GlobalRiviere;

class ListeCell{
  
 private:
  BlockCell* head;
  size_t size;
  
 public:
  ListeCell();
  ListeCell(BlockCell* _head);
  // ~ListeCell();
  size_t  getSize()const;
  
  BlockCell* getHead()const;
  
  //Methodes
  BlockCell* getSucc(BlockCell*)const;
  void addAfter(BlockCell* cell);
  void fusion(BlockCell* bc,BlockCell* cell,GlobalRiviere &gb);
  bool est_Vide()const;
  void printListe()const;
  void supprimer(BlockCell* b);
};

#endif
