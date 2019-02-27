#include"Iles.h"
#include<iostream>
Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),indice(i){}
