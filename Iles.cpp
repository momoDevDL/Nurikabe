#include"Iles.h"
#include<iostream>
Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b):whiteCells(ListeCell(b)){}
