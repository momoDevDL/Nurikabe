#ifndef __PROG_H
#define __PROG_H

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

void noircirAndRegleRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR);

void blanchirAndRegleIles(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR);

void noircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intR);

void UnfriendedIles(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR);

void blanchir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indI);

void setPotentiel(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y);

void friendsIles(Grille &g,Iles &ile, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR);

void friendsRiviere(Grille &g,Riviere &riv, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR);

void unFriendsRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR);

void Complet(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x, int y,int &intI ,int &indice);

void CroixNoircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indiceIles,int &indiceRiviere);


#endif
