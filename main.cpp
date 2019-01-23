#include"grille.h"
#include<iostream>

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
  return 0;
}
