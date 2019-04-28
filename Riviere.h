#ifndef __RIVIERE_H
#define __RIVIERE_H


class GlobalRiviere;
class GlobalIles;
#include "ListeCell.h"
#include"grille.h"

class Riviere{
 private :
  ListeCell riviere; 
  int indiceDeCreation;
 public :
  Riviere();
  Riviere(BlockCell *b,int indice);
  //methods

  /*bool A_UnSeulReferant()const;

    Cell* getCellReferante()const;*/

  int getIndice()const;
  void setIndice(int);
  void setRiviere(ListeCell *l);


  void addBlockCellToRiviere(BlockCell *b, GlobalRiviere &GR,GlobalIles &GI);

  void supprimeRiv(GlobalRiviere &GR);

  int getTailleRiviere()const;

  void printRiv();

  ListeCell* getRiviere();
  


};
#endif

