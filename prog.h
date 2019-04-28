/**/
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

bool carreNoire(Grille &g,const Cell &c );

void MyProgram(int argc,char** argv);

void noircirAndRegleRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR,bool &Fini);

void blanchirAndRegleIles(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR,bool &Fini);

void noircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intR,bool &Fini);

void UnfriendedIles(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR,bool &Fini);

void blanchir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indI,bool &Fini);

void setPotentiel(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y);

void friendsIles(Grille &g,Iles &ile, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR, bool &Fini);

void friendsRiviere(Grille &g,Riviere &riv, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR, bool &Fini);

void unFriendsRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR, bool &Fini);

void Complet(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x, int y,int &intI ,int &indice,bool &Fini);

void CroixNoircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indiceIles,int &indiceRiviere);

bool IleContientPlus(GlobalIles &GI);
bool CellBlancheIsolebis(Grille &g,int i,int j, int posXDePremierAppel,int posYDePremierAppel,int,int,int,int,std::vector<Cell*>);
#endif
