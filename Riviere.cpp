#include"Riviere.h"
#include "ListeCell.h"
#include<iostream>

Riviere::Riviere():riviere(ListeCell(NULL)),indiceDeCreation(-1){}
Riviere::Riviere(BlockCell *b, int indice):riviere(ListeCell(b)),indiceDeCreation(indice){}


