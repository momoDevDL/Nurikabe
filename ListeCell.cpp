#include<iostream>
using namespace std;
#include"ListeCell.h"

ListeCell::ListeCell():head(NULL),tail(NULL),size(0){}

ListeCell::ListeCell(BlockCell* Bcell):head(Bcell),tail(Bcell),size(1){}

/*void ListeCell::setNextBlock(BlockCell* thisBlock,BlockCell* NextBlock){
  thisBlock->setNextBlockCell(NextBlock);
}*/

size_t ListeCell::getSize()const{ return size;}
void ListeCell::setTail(BlockCell* BC){ tail=BC;}

bool ListeCell::est_Vide()const{return size==0;}

BlockCell* ListeCell::getTail()const{ return tail;}
BlockCell* ListeCell::getHead()const{ return head;}

BlockCell* ListeCell::getSucc(BlockCell* BC)const{ return BC->getNextBlock();}

void ListeCell::addAfter(BlockCell* BC,BlockCell* blockC){
  //BlockCell* blockC=new BlockCell(cell);
  if(getSucc(BC)==NULL){
    BC->setNextBlockCell(blockC);
    size++;
    setTail(blockC);
  }else{
    BlockCell* tmp= BC->getNextBlock();
    BC->setNextBlockCell(blockC);
    blockC->setNextBlockCell(tmp);
    size++;
    delete tmp;
  }
}

void ListeCell::printListe()const{
  BlockCell* tmp=getHead();
  int i=0;
  while(getSucc(tmp)){
    tmp->printBlock();
    tmp=getSucc(tmp);
    i++;
  }
  tmp->printBlock();
  cout<<i<<endl;
}

