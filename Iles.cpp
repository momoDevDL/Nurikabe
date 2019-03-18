#include"Iles.h"
#include"prog.h"

#include<iostream>

Iles::Iles():whiteCells(ListeCell(NULL)){}

Iles::Iles(BlockCell *b, int i):whiteCells(ListeCell(b)),remaining(b->getCellNum() -1),indice(i){}
/*Iles::~Iles(){
  delete whiteCells;
}*/
int Iles::getRemaining(){
  return remaining;
}

ListeCell* Iles::getWhiteCells(){
  return &whiteCells;  
}

int Iles::getIndice(){
  return indice;
}

void Iles::setIndice(int i){
  indice = i ;
}

void Iles::setRemaining(int r){
  remaining = r;
}

bool Iles::estPleine(){
  bool plein = false;
  if (remaining == 0){
    plein = true;
  }
  return plein;
}

void Iles::friendsIles(Grille &g){
  if (remaining > 0){
    int nbChoix = 0;
    Cell* buf = NULL;
    Cell* buf2 = NULL;
    BlockCell* tmp = whiteCells.getHead();
    
    while ((nbChoix < 3)&&(tmp->getNextBlock() != NULL)){
      
      if (!(((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 4))) {
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()));
	  
	}
	nbChoix++;
	
      } else if (!(((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 4))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()));
	  
	}
	nbChoix++;
      } else if (!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() < 4))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1));
	  
	}
	nbChoix++;
      } else if (!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() < 4))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1));
	  
	}
	nbChoix++;
      }
      tmp = tmp->getNextBlock();
    }
    if (nbChoix == 1){  // Première régle: si il n'y a qu'une case possible adjacente à l'Ile
      
      buf->setEtat(5); //  à Blanchir 
      
    } else if (nbChoix == 2){ // Deuxième régle: si il n'y a que deux case possible adjacente à l'Ile et qu'elles sont en diagonal l'une de l'autre;
      if (remaining == 1){
	
	if ((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() + 1))){
	  
	  if (g.getCell(buf2->getPosX(),(buf2->getPosY() + 1)).getEtat() == 1){
	    
	    g.getCell(buf2->getPosX() + 1,(buf2->getPosY())).setEtat(3);
	    
	  } else {
	    
	    g.getCell(buf2->getPosX(),(buf2->getPosY() + 1)).setEtat(3);
	    
	  }
	  
	} else if ((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() - 1))){
	  
	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	    
	    g.getCell(buf2->getPosX(),(buf2->getPosY() - 1)).setEtat(3);
	    
	  } else {
	    
	    g.getCell((buf2->getPosX() - 1),buf2->getPosY()).setEtat(3);
	    
	  }
	  
	} else if ((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() - 1))){
	  
	  if (g.getCell((buf2->getPosX() + 1),buf2->getPosY()).getEtat() == 1){
	    
	    g.getCell(buf2->getPosX(),(buf2->getPosY() - 1)).setEtat(3);
	    
	  } else {
	    
	    g.getCell((buf2->getPosX() + 1),buf2->getPosY()).setEtat(3);
	    
	  }
	  
	} else if ((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() + 1))){
	  
	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	    
	    g.getCell(buf2->getPosX(),(buf2->getPosY() + 1)).setEtat(3);
	    
	  } else {
	    
	    g.getCell((buf2->getPosX() - 1),buf2->getPosY()).setEtat(3);
	    
	  }
	}
      }
    }
  }
}

/*void Iles::Complet(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x, int y, int &indice){
  
  BlockCell *tmp = whiteCells.getHead();

  if (estPleine()){

    while ( tmp->getNextBlock() ){
      int X = tmp->getCellPointer()->getPosX();
      int Y = tmp->getCellPointer()->getPosY();
      
      if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
	noircir(g,GR,GI,X+1,Y,indice);
      }
      if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
	noircir(g,GR,GI,X-1,Y,indice);
      }
      if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
	noircir(g,GR,GI,X,Y+1,indice);

      }
      if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
	noircir(g,GR,GI,X,Y-1,indice);

      }
      
    }

    int X = tmp->getCellPointer()->getPosX();
    int Y = tmp->getCellPointer()->getPosY();
    
    if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
      noircir(g,GR,GI,X+1,Y,indice);
    }
    if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
      noircir(g,GR,GI,X-1,Y,indice);
    }
    if( !g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
	noircir(g,GR,GI,X,Y+1,indice);
	
    }
    if( !g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
      noircir(g,GR,GI,X,Y-1,indice);

    }
  }
  //delete tmp;*/
void Iles::print(){

  whiteCells.printListe();
  std::cout<< " -> reste : "<< remaining << " >-----< indice De creation : " << indice << std::endl;

}
