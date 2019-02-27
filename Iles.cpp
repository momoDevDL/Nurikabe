#include"Iles.h"
#include<iostream>
Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),indice(i),remaining(b->getCellNum()){}

int Iles::getRemaining(){
  return remaining;
}

int Iles::getIndice(){
  return indice;
}

void Iles::setRemaining(int r){
  remaining = r;
}

void Iles::estPresqueComplet1(){
}

void Iles::estPresqueComplet2(){
}
