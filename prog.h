#include"grille.h"
#include<iostream>
#include"ListeCell.h"
#include"option.h"
#include<map>
#include<string>
#include "GlobalRiviere.h"
#include "GlobalIles.h"


void getDataDimension(std::map<std::string,std::string>& data,std::string key,int &value);

void CellValuesTreatment(std::string &val,int &x,int &y,int &etat,int &num);

void addCells(std::map<std::string,std::string> &data,Grille &g);

void initGrille(std::map<std::string,std::string>& data);


void MyProgram(int argc,char** argv);

void noircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y);

void setPotentiel(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y);

void applicationRegle(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y);
