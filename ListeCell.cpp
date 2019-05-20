
//----------------------Headers-------------------
#include<iostream>
#include"ListeCell.h"                   
#include"Riviere.h"
#include"GlobalRiviere.h"
#include"GlobalIles.h"
using namespace std;

//------------------------------------------------

//Constructeurs par défaut 
ListeCell::ListeCell():head(new BlockCell),size(1){}

//Constructeurs paramétré
ListeCell::ListeCell(BlockCell* bcell):head(bcell){
  size = 1 ;
  BlockCell *tmp = head;
  while(tmp->getNextBlock()){
    size++;
    tmp = tmp->getNextBlock();
  }
}

//parcourir la liste et supprimer les membres de la liste 
void ListeCell::supprimer(){
  BlockCell *tmp = head;
  while(tmp){
    tmp = tmp->getNextBlock();
    delete head;
    head = tmp;
  }
  size = 0;
}

//destructeur de liste
ListeCell::~ListeCell(){
  supprimer();
}

//surcharge de l'operateur d'affectation
ListeCell& ListeCell::operator=(const ListeCell& L){
  if (this != &L){
   
    size = L.getSize();
    
    
    BlockCell *tmp = L.getHead();
    head->setCellPointer(L.getHead()->getCellPointer());
    while(tmp->getNextBlock()){
      
      tmp = tmp->getNextBlock();
      add(tmp->getCellPointer());
    }
    
 
   
  }
  return *this;
}

//rajout d'un nouveau block de cellule a la fin de la liste qui contient comme valeur une cellule
//passé en parametre
void ListeCell::add(Cell* c){

  BlockCell *added = new BlockCell(c);
  BlockCell *tmp = head;

  while(tmp->getNextBlock()){
    tmp = tmp->getNextBlock();
  }
  tmp->setNextBlockCell(added);
  
}



size_t ListeCell::getSize()const{ return size;}

void ListeCell::setSize(size_t s){ size = s;} 

bool ListeCell::est_Vide()const{return size==0;}

BlockCell* ListeCell::getHead()const{ return head;}

void ListeCell::setHead(BlockCell* b){ head = b;}


//renvoie le membre de la liste suivant en passant une position en parametre
BlockCell* ListeCell::getSucc(BlockCell* bc)const{ return bc->getNextBlock();}


//la fusion de deux listes en traitant les differents cas de fusion
// - L1 : un element L2: un element
// - L1 : un element L2:  liste d'element
// - L1 : liste  d'element L2: liste d'element
//en passant aussi par parametre les deux structures globales pour rajouter le resultat de
// la fusion 
void ListeCell::fusion(BlockCell* bc,BlockCell* blockC,GlobalRiviere &gb,GlobalIles &GI){

  if(getSucc(blockC) == NULL){

    //-------------------------------------------
    if(blockC->getRefCell() == NULL){
      blockC->setRefCell(bc->getCellPointer());

      if (blockC->getRivCell() != NULL){

	//	Riviere* buf = blockC->getRivCell();   //Pour la fusion de riviere
	blockC->setRivCell(NULL);

	
      }
    }
    //-------------------------------------------
    if(getSucc(bc) == NULL){
      bc->setNextBlockCell(blockC);
      size++;
    } else {

      BlockCell* tmp = bc->getNextBlock();
      bc->setNextBlockCell(blockC);
      blockC->setNextBlockCell(tmp);
      size++;
     
    }
  } else {
    //-------------------------------------------
     
    if (blockC->getCellPointer()->getRiv() != NULL){
      
      //Riviere* buf = blockC->getRivCell();   //Pour la fusion de riviere
      blockC->setRivCell(NULL);
      
      
    }
    
    //-------------------------------------------
    int buf = 1;
    blockC->setRefCell(bc->getCellPointer());
 
    if (getSucc(bc) != NULL) {
      BlockCell* tmp = bc->getNextBlock();
      BlockCell* tmp1 = blockC->getNextBlock();
      tmp1->setRefCell(bc->getCellPointer());
      buf++;
      while (getSucc(tmp1) != NULL){
	tmp1 = tmp1->getNextBlock();
	tmp1->setRefCell(bc->getCellPointer());
	buf++;
      }
      tmp1->setNextBlockCell(tmp);
      bc->setNextBlockCell(blockC);
      size = size + buf;
    } else {
      
      BlockCell* tmp1 = blockC;
     
      tmp1->setRefCell(bc->getCellPointer());
      buf++;
      while (getSucc(tmp1) != NULL){
	tmp1 = tmp1->getNextBlock();
	tmp1->setRefCell(bc->getCellPointer());
	buf++;
      }
    
      tmp1->setNextBlockCell(NULL);
      bc->setNextBlockCell(blockC);
      size = size + buf;
    }
  }
}

//fonction d'affichage qui affiche les elements d'une liste donnée,
//les coordonnées de ces elements et leur addresse memoire

void ListeCell::printListe()const{
  std::cout<<"La liste de cellule de taille "<< size<< "est : [";
  BlockCell*tmp= head;
  
  while(tmp->getNextBlock()){
    cout<<"("<< tmp->getCellPointer()->getPosX()<<","<<tmp->getCellPointer()->getPosY()<<")";
    std::cout<<" | ";
    tmp= tmp->getNextBlock();
  }
  cout<<"("<< tmp->getCellPointer()->getPosX()<<","<<tmp->getCellPointer()->getPosY()<<")";
  std::cout<<"]"<<endl;
  
  std::cout<<"La liste de cellule est : [";
  tmp=getHead();
  while(getSucc(tmp)){
    tmp->printBlockListe();
    std::cout<<" | ";
    tmp=getSucc(tmp);
  }
  
  tmp->printBlockListe();
  std::cout<<"]"<<endl;

  // affichage de l'adresse memoire de chaque cellule dans la liste
  
  std::cout<<"La liste de cellule est : [";
  tmp=getHead();
  while(getSucc(tmp)){
    std::cout<<&(*(tmp));
    std::cout<<" | ";
    tmp=getSucc(tmp);
  }
  
  std::cout<<&(*(tmp));
  std::cout<<"]"<<endl;
  

}

