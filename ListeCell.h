#ifndef __LISTECELL_H
#define __LISTECELL_H
#include<iostream>
#include "BlockCell.h"
class GlobalRiviere;
class GlobalIles;

class ListeCell{
 
 private:
  BlockCell* head;
  size_t size;
  
 public:
  //Constructeurs
  ListeCell();
  ListeCell(BlockCell* _head);
  //destructeurs
  ~ListeCell();
  //accesseurs
  size_t  getSize()const;
  void setSize(size_t);
  ListeCell& operator=(const ListeCell &L);
  BlockCell* getHead()const;
  void setHead(BlockCell* b);
  BlockCell* getSucc(BlockCell*)const;
  //Methodes
  void add(Cell* c);
  void fusion(BlockCell* bc,BlockCell* cell,GlobalRiviere &gb,GlobalIles &GI);
  bool est_Vide()const;
  void printListe()const;
  void supprimer();
};

#endif
