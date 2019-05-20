#include"grille.h"
#include"cell.h"
#include<iostream>
#include"Iles.h"
#include"Riviere.h"
using namespace std;


//creation de deux grilles par defaut de dimension 5*5
//une grille de Cellule et une grille de BlockCell
Grille::Grille():dimensionX(5),dimensionY(5),tabCell(new Cell*[5]),tabBlockCell(new BlockCell*[5]){
  for(int i=0;i<5;i++){
    tabCell[i] = new Cell[5];
    tabBlockCell[i] = new BlockCell[5];
  }
}

Grille::Grille(int dimX,int dimY):dimensionX(dimX),dimensionY(dimY),tabCell(new Cell*[dimX]),tabBlockCell(new BlockCell*[dimX]){
  for(int i=0;i<dimX;i++){
    tabCell[i]=new Cell[dimY];
    tabBlockCell[i] = new BlockCell[dimY];
  }
}

//destructeur paramétré qui fait appel a vider()
Grille::~Grille(){
  vider();
}


//fonction qui permet de detruire les elements des 2 grilles
void Grille::vider(){
  int i=0;
 
 while(i<dimensionX){
    delete[] tabCell[i];
    delete[] tabBlockCell[i];
    i++;
  }
  delete[] tabCell;
  delete[] tabBlockCell;
}


//affectation de 2 grilles nécessaires pour la sauvegarde pendant la phase de Backtrack 
Grille& Grille::operator=(const Grille& g){
  if (this != &g){
   
    
    dimensionX = g.getDimensionX();
    dimensionY = g.getDimensionY();

       

      
    for(int i=0;i<dimensionX;i++){
      for(int j=0;j<dimensionY;j++){
      	
	tabBlockCell[i][j].setCellPointer(&tabCell[i][j]);
	if(g.getBlockCell(i,j).getNextBlock() != NULL){
	  tabBlockCell[i][j].setNextBlockCell(&tabBlockCell[g.getBlockCell(i,j).getNextBlock()->getCellPointer()->getPosX()][g.getBlockCell(i,j).getNextBlock()->getCellPointer()->getPosY()]);
	
	}else{
	  tabBlockCell[i][j].setNextBlockCell(NULL);
	}
      }
    }
    
    for(int i=0;i<dimensionX;i++){
      for(int j=0;j<dimensionY;j++){
	
	//cout<<i<<" , "<<j<<endl;
	
	tabCell[i][j] = g.getCell(i,j);
	//	cout<<"Referance avant le set a null  :\t "<<tabCell[i][j].getRef()<<endl;
	
	tabCell[i][j].setRef(NULL);
	if(g.getCell(i,j).getRef() != NULL){
	 
	  tabCell[i][j].setRef(&tabCell[g.getCell(i,j).getRef()->getPosX()][g.getCell(i,j).getRef()->getPosY()]);

	}
	
	//cout<<"Referance Apres le set a null et mise a jour : " << tabCell[i][j].getRef()<<endl;

	tabCell[i][j].setRiv(NULL);
	
	if(g.getCell(i,j).getRiv() != NULL){
	 
	  int X = g.getCell(i,j).getRiv()->getRiviere()->getHead()->getCellPointer()->getPosX();
	  int Y = g.getCell(i,j).getRiv()->getRiviere()->getHead()->getCellPointer()->getPosY();
	  int indice = g.getCell(i,j).getRiv()->getIndice();
	  tabCell[i][j].setRiv(new Riviere(&tabBlockCell[X][Y],indice));
	}

	tabCell[i][j].setIles(NULL);

	if(g.getCell(i,j).getIles() != NULL){
	  int X = g.getCell(i,j).getIles()->getWhiteCells()->getHead()->getCellPointer()->getPosX();
	  int Y = g.getCell(i,j).getIles()->getWhiteCells()->getHead()->getCellPointer()->getPosY();
	  int indice = g.getCell(i,j).getIles()->getIndice();
	  tabCell[i][j].setIles(new Iles(&tabBlockCell[X][Y],indice));
	 
	  tabCell[i][j].getIles()->setRemaining(tabCell[i][j].getCellNum() - tabCell[i][j].getIles()->getWhiteCells()->getSize());
    
	}
      }
    }
  }
  return *(this);
}


//Verifier si les coordonnees de cell ou blockCell qu'on veut acceder ne dépasse pas
//les dimensions de la grille 
bool Grille::CHECK_BOUND(int x, int y ,int dimX, int dimY)const{	
  if(x > dimX - 1 || x < 0 || y < 0 || y > dimY - 1){ 
    // cerr<<"une ou les  valeur(s) depasse(nt) la dimension de la grille"<<endl; 
    return true;							
  }
  return false;
}


//verifier si toutes les cellules sont noires ou blanches
bool Grille::rempli(){
  for(int i = 0 ; i < getDimensionX();i++){
    for(int j = 0 ; j < getDimensionY();j++){
      if(getCell(i,j).getEtat() == 4){
	return false;
      }
    }
  }
  return true;
}



int Grille::getDimensionX()const{return dimensionX;}

int Grille::getDimensionY()const{return dimensionY;}

//recupérer une cellule de la grille par reference pour pouvoir faire des operations dessus
Cell& Grille::getCell(int x,int y)const{
  if( CHECK_BOUND(x,y,dimensionX,dimensionY)){
    cout<<"this cell is not reachable"<<endl;
  }
  return tabCell[x][y];
}


//recuperation de Block Cell pour pouvoir le manipuler
BlockCell& Grille::getBlockCell(int x,int y)const{
  if(CHECK_BOUND(x,y,dimensionX,dimensionY)){
    cout<<"this Blockcell is not reachable"<<endl;
  }

  return tabBlockCell[x][y];
}


//modifier la cellule vers laquelle le block Cell pointe dans la grille
void Grille::setCellPointerInBlockCell(int x,int y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabBlockCell[x][y].setCellPointer( &tabCell[x][y] );
  }
  return;
}


//ajouter un numero a une cellule de la grille
void Grille::addVal(size_t val, int x,int y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabCell[x][y].setCellNum(val);
    tabCell[x][y].setEtat(1);
  }
  return;
}

//modifier l'etat d'une cellule 
void Grille::addEtat(size_t etat,int x,int y){
  if(!CHECK_BOUND(x,y,dimensionX,dimensionY)){
    tabCell[x][y].setEtat(etat);
  }
  return;
}


//affichage de la grille
void Grille::GrillePrint(){
  
  for(int k=0;k<dimensionX;k++){
    cout<<endl;
    //cout<<'|';
    for(int j=0;j<dimensionY;j++){
      tabCell[k][j].print();
      // cout<<'|';
    }
    
  }
  cout<<endl;
  return;
}
