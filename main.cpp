#include"grille.h"
#include<iostream>
#include"ListeCell.h"
using namespace std;
int main(int argv,char** argc){
  
  Grille g;
  g.addVal(2,0,4);
  g.GrillePrint();
  g.addVal(6,0,2);
  g.addVal(3,2,3);
  g.GrillePrint();
  g.addEtat(1,1,2);
  g.addEtat(2,0,3);
  g.GrillePrint();
  (g.getCell(1,1)).print();

  BlockCell cell6(&(g.getCell(0,2)));
  BlockCell cell7(&(g.getCell(0,3)));
  // cell6.setEtatCell((g.getCell(0,4)).getEtat());
  ListeCell L1(&cell6);
  cout<<L1.getSize()<<endl;
  L1.addAfter(L1.getTail(),&cell7);
  L1.addAfter(L1.getTail(),&(g.getCell(1,3)));
  // cout<<L1.getSize()<<endl;
  L1.printListe();
  return 0;
}
