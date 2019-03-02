#include"cell.h"
#include<iostream>
using namespace std;
Cell::Cell():etat(0),cellNum(0){}
Cell::Cell(int e,int c):etat(e),cellNum(c){}

int Cell::getEtat()const{ return etat;}

int Cell::getCellNum()const{ return cellNum;}

int Cell::getPosX()const{return posX;}

int Cell::getPosY()const{return posY;}

Cell* Cell::getRef(){return ref;}

Riviere* Cell::getRiv(){return riv;}

Iles* Cell::getIles(){return iles;}


void Cell::setPosX(int pos){posX=pos;}

void Cell::setPosY(int pos){posY=pos;}

void Cell::setEtat(int e){ etat=e;}

void Cell::setCellNum(int cNum){cellNum=cNum;}

void Cell::setRef(Cell* c){ref = c;}

void Cell::setRiv(Riviere* r){riv = r;}


void Cell::setIles(Iles* i){iles = i;}


void Cell::print(){
  switch(etat){
  case 1:
    if(cellNum){
    cout<<"\033[30;47m "<<cellNum<<" \033[0m";
    }else{
      cout<<"\033[1;47m   \033[0m";
    }
    break;
  case 0:
    cout<<"\033[1;44m   \033[0m";
    break;
  case 2 :
    cout<<"\033[1;40m   \033[0m";
    break;
  case 3:
    cout<<"\033[1;42m   \033[0m";
    break;
  case 4:
    cout<<"\033[1;44m   \033[0m";
    break;
  }
}

bool Cell::conflit(){return etat==3;}
    
