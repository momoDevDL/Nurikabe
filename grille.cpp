#include"grille.h"
#include"cell.h"
#include<iostream>
using namespace std;
#define CHECK_BOUND(i,j,x,y)			\
  if(i>x || j > y){ \
  cerr<<"une ou les  valeur(s) depasse(nt) la dimension de la grille"<<endl; \
  }

Grille::Grille():dimensionX(5),dimensionY(5),tabCell(new Cell*[5]),tabBlockCell(new BlockCell*[5]){
    for(size_t i=0;i<5;i++){
    tabCell[i] = new Cell[5];
    tabBlockCell[i] = new BlockCell[5];
  }
}


Grille::Grille(size_t dimX,size_t dimY):dimensionX(dimX),dimensionY(dimY),tabCell(new Cell*[dimX]),tabBlockCell(new BlockCell*[dimX]){
  for(size_t i=0;i<dimX;++i){
    tabCell[i]=new Cell[dimY];
    tabBlockCell[i] = new BlockCell[dimY];
  }
}

Grille::~Grille(){
  size_t i=0;
  while(i<dimensionX){
    delete [] tabCell[i];
    delete [] tabBlockCell[i];
    i++;
  }
  delete tabCell;
  delete tabBlockCell;
}

 size_t Grille::getDimensionX()const{return dimensionX;}

 size_t Grille::getDimensionY()const{return dimensionY;}

 Cell& Grille::getCell(size_t x,size_t y)const{
   CHECK_BOUND(x,y,dimensionX,dimensionY);
  return tabCell[x][y];
}

BlockCell& Grille::getBlockCell(size_t x,size_t y)const{
   CHECK_BOUND(x,y,dimensionX,dimensionY);
  return tabBlockCell[x][y];
}

void Grille::setCellPointerInBlockCell(size_t i,size_t j){
  CHECK_BOUND(i,j,dimensionX,dimensionY);
  tabBlockCell[i][j].setCellPointer( &tabCell[i][j] );
}

void Grille::addVal(int val, size_t x,size_t y){
  CHECK_BOUND(x,y,dimensionX,dimensionY);
  tabCell[x][y].setCellNum(val);
  tabCell[x][y].setEtat(1);
  
}
void Grille::addEtat(int etat,size_t x,size_t y){
 CHECK_BOUND(x,y,dimensionX,dimensionY);
 tabCell[x][y].setEtat(etat);

}

void Grille::GrillePrint(){
  
  for(size_t k=0;k<dimensionX;k++){
    cout<<endl;
    cout<<'|';
    for(size_t j=0;j<dimensionY;j++){
      tabCell[k][j].print();
      cout<<'|';
    }
   
  }
  cout<<endl;
}
