#include"grille.h"
#include"cell.h"
#include<iostream>
using namespace std;

bool CHECK_BOUND(size_t x, size_t y ,size_t dimX, size_t dimY){	
  if(x > dimX || y > dimY){ 
    cerr<<"une ou les  valeur(s) depasse(nt) la dimension de la grille"<<endl; 
    return true;							
  }
  return false;
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
  if( !CHECK_BOUND(x,y,dimensionX,dimensionY)){
    return tabCell[x][y];
  }
}

BlockCell& Grille::getBlockCell(size_t x,size_t y)const{
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    return tabBlockCell[x][y];
  }
}

void Grille::setCellPointerInBlockCell(size_t x,size_t y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabBlockCell[x][y].setCellPointer( &tabCell[x][y] );
  }
}

void Grille::addVal(int val, size_t x,size_t y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabCell[x][y].setCellNum(val);
    tabCell[x][y].setEtat(1);
  }
}
void Grille::addEtat(int etat,size_t x,size_t y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabCell[x][y].setEtat(etat);
  }
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
