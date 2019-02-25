#include"Riviere.h"
#include<iostream>

Riviere::Riviere():riviere(ListeCell(NULL)){}
Riviere::Riviere(BlockCell *b):riviere(ListeCell(b)){}


