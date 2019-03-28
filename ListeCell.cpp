#include<iostream>
using namespace std;
#include"ListeCell.h"
#include"Riviere.h"
#include"GlobalRiviere.h"

ListeCell::ListeCell():head(NULL),size(0){}

ListeCell::ListeCell(BlockCell* bcell):head(bcell),size(1){}

void ListeCell::supprimer(BlockCell* b){
  if(b->getNextBlock() == NULL){
    delete b;
  }else{ 
    supprimer(b->getNextBlock());
  }
}

/*ListeCell::~ListeCell(){
  supprimer(head);
}*/
/*void ListeCell::setNextBlock(BlockCell* thisBlock,BlockCell* NextBlock){
  thisBlock->setNextBlockCell(NextBlock);
}*/

size_t ListeCell::getSize()const{ return size;}

bool ListeCell::est_Vide()const{return size==0;}

BlockCell* ListeCell::getHead()const{ return head;}

BlockCell* ListeCell::getSucc(BlockCell* bc)const{ return bc->getNextBlock();}

void ListeCell::fusion(BlockCell* bc,BlockCell* blockC,GlobalRiviere &gb){
  if(getSucc(blockC) == NULL){
    //-------------------------------------------
    if(blockC->getRefCell() == NULL){
      blockC->setRefCell(bc->getCellPointer());
      if (blockC->getRivCell() != NULL){
	Riviere* buf = blockC->getRivCell();   //Pour la fusion de riviere
	blockC->setRivCell(NULL);
	//	buf->supprimeRiv(gb);
	
      }
    }
    //-------------------------------------------
    if(getSucc(bc) == NULL){
      bc->setNextBlockCell(blockC);
      size++;
    } else {
      // cout<<endl;
      // cout<<"ON EST LA"<<endl;
      // cout<<endl;
      BlockCell* tmp = bc->getNextBlock();
      bc->setNextBlockCell(blockC);
      blockC->setNextBlockCell(tmp);
      size++;
     
    }
  } else {
    //-------------------------------------------
    
    if (blockC->getCellPointer()->getRiv() != NULL){
      Riviere* buf = blockC->getRivCell();   //Pour la fusion de riviere
      blockC->setRivCell(NULL);
      // buf->supprimeRiv(gb);
      
    }
    
    //-------------------------------------------
    int buf = 0;
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
      BlockCell* tmp = bc;
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
    }
  }
}


void ListeCell::printListe()const{
   std::cout<<"La liste de cellule est : [";
   BlockCell*tmp=getHead();
  while(getSucc(tmp)){
    cout<<"("<< tmp->getCellPointer()->getPosX()<<","<<tmp->getCellPointer()->getPosY()<<")";
    std::cout<<" | ";
    tmp=getSucc(tmp);
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
  

}

