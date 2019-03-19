#include"grille.h"
#include<iostream>
#include"ListeCell.h"
#include"option.h"
#include"prog.h"
#include<map>
#include<cstdlib>
#include<cstdio>
#include "GlobalRiviere.h"
#include "GlobalIles.h"

using namespace std;


void getDataDimension(map<string,string>& data,string key,int &value){
  const char* k =  data[key].c_str();
  value = atoi(k);
}

void CellValuesTreatment(string &val,int &x,int &y,int &etat,int &num){
  val = val.substr(1);
  size_t res = val.find_first_of(',');
  x = atoi((val.substr(0,res)).c_str());
  val = val.substr(res+1);
  res = val.find_first_of(',');
  y = atoi((val.substr(0,res)).c_str());
  val = val.substr(res+1);
  res = val.find_first_of(',');
  num = atoi((val.substr(0,res)).c_str());
  etat = 1;
}

void addCells(map<string,string> &data,Grille &g){
  int posX;
  int posY;
  int etat;
  int num;
 
  map<string,string>::iterator itr;
  itr = data.find("nbrDeCell");
  int i = atoi(itr->second.c_str());
 
  while(i>0){
    char n[20]="";
    sprintf(n,"%d",i);
    itr = data.find("C"+(string)n);
    if(itr!=data.end()){
      CellValuesTreatment(itr->second,posX,posY,etat,num);
      g.addVal(num,posX,posY);
    }
    data.erase(itr);
    i--;
  }
}



void noircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y, int &intR){

  if( g.getCell(x,y).getEtat() != 2){
    
    g.getCell(x,y).setEtat(2);
    
    
    bool fusion = false;
    
    //-----------Premiere-fusion---------------------------------------
    
    if ( (y > 0 ) && (g.getCell(x,y-1).getEtat() == 2) ){


      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x,y-1);

      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
    
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      
      }
      
      if ( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){
	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell( buf->getPosX(),buf->getPosY() ), GR);
	
      }else{
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell( buf2->getPosX(),buf2->getPosY() ), GR);
	
      }
      
      fusion = true;
      g.getCell(x,y).getRef()->getRiv()->printRiv();
    }
    
    //-----------Deuxieme-fusion---------------------------------------
    
    if ( (y < g.getDimensionY()-1) && (g.getCell(x,y+1).getEtat() == 2) ){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
      
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x,y+1);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
      
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }

      
      if( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){

	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell( buf->getPosX(),buf->getPosY() ), GR);
	
      }else {
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell( buf2->getPosX(),buf2->getPosY() ), GR);
	
      }
      
      fusion = true;
      g.getCell(x,y).getRef()->getRiv()->printRiv();

    }

    //-----------Troisieme-fusion---------------------------------------

    if ( (x < g.getDimensionX()-1) && (g.getCell(x+1,y).getEtat() == 2) ){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
      
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x+1,y);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
      
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }

      if( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){

	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	
      } else {
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);
	
      }
      
      fusion = true;
      g.getCell(x,y).getRef()->getRiv()->printRiv();
      
    }
    

    //-----------Quatrieme-fusion---------------------------------------

    if ( (x > 0) && (g.getCell(x-1,y).getEtat() == 2) ){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
     
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x-1,y);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();

      }

      while (buf->getRef() != NULL){

	buf = buf->getRef();
      }


      
      if ( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){

	
	//-------------------------------------------------------------

	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);

      } else {

	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);

      }

      fusion = true;
      g.getCell(x,y).getRef()->getRiv()->printRiv();
      
    }
    //----------------------------------------------------------------
   

    if(!fusion){
      
      Riviere* r = new Riviere(&g.getBlockCell(x,y),intR);
      g.getCell(x,y).setRiv(r);
      intR++;
      GR.AddRiviere(*r);
      g.getCell(x,y).getRiv()->printRiv();
    }

  }
  
}
 
void UnfriendedIles(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR){

  Cell* Ref = g.getCell(x,y).getRef();
  cout<<"REF"<<endl;
  Cell* buf = &g.getCell(x,y);
  cout<<"buf"<<endl;
 
  while ( buf -> getRef() != NULL){
    buf = buf->getRef();
    cout << "fucklol"<<endl;
  }
  cout<<"ON EST ENTRe"<<endl;
  int indice = buf->getIles()->getIndice();
  
  int X = g.getCell(x,y).getPosX();
  int Y = g.getCell(x,y).getPosY();


  if(!g.CHECK_BOUND(X+1,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y+1).getEtat() == 1){ cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+1,Y+1);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck256"<<endl;
    }
    if(( Ref != g.getCell(X+1,Y+1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X+1)&&(Ref->getPosY() != Y+1)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
	}
      }
    }
  }

  if(!g.CHECK_BOUND(X+1,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y-1).getEtat() == 1){
    /* cout<<"ON EST ENTRe 5"<<endl;
       if( Ref != g.getCell(X+1,Y-1).getRef()){
       cout<<"ON EST ENTRe 1"<<endl;
       noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
       noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
       }else{
       cout<<"ON EST ENTRe 7"<<endl;
       if(indice != g.getCell(X+1,Y-1).getIles()->getIndice()){
       cout<<"ON EST ENTRe 8"<<endl;

       noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);

       noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);

       }
       }*/
    cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+1,Y-1);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuckdvf"<<endl;
    }
    if(( Ref != g.getCell(X+1,Y-1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X+1)&&(Ref->getPosY() != Y-1)){
      cout << "fuckdvf"<<endl;
      if (buf->getIles() != NULL){
	cout << "fuckdvf"<<endl;
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
      }
    }else{
      cout << "fuckdvf"<<endl;
      if (buf->getIles() != NULL){
	cout << "fuckdvf"<<endl;
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
	}
      }
    }
  }

  if(!g.CHECK_BOUND(X-1,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y-1).getEtat() == 1){
    
    /*  if( Ref != g.getCell(X-1,Y-1).getRef()){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}else{
	if(indice != g.getCell(X-1,Y-1).getIles()->getIndice()){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}
	}*/

    Cell* buf = &g.getCell(X-1,Y-1);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuckhfh"<<endl;
    }
    if(( Ref != g.getCell(X-1,Y-1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-1)&&(Ref->getPosY() != Y-1)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}
      }
    }
    	
  }

  if(!g.CHECK_BOUND(X-1,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y+1).getEtat() == 1 ){

    /*  if( Ref != g.getCell(X-1,Y+1).getRef()){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}else{
	if(indice != g.getCell(X-1,Y+1).getIles()->getIndice()){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}
	}*/
    //cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    //cout<<" IL CHECK CE CONNARD"<<X-1<<","<<Y-1<<endl;
    Cell* buf = &g.getCell(X-1,Y+1);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X-1,Y+1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-1)&&(Ref->getPosY() != Y+1)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}
      }
    }
    	
  }

  
  //===============DEbut de traitement des zones horiz et vertic =================//
  

  if(!g.CHECK_BOUND(X+2,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+2,Y).getEtat() == 1){
    
    /* if(Ref != g.getCell(X+2,Y).getRef()){
       noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
       }else{
       if(indice != g.getCell(X+2,Y).getIles()->getIndice()){
       noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
       }
       }*/
    cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+2,Y);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck"<<endl;
    }
    if((Ref != g.getCell(X+2,Y).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X+2)&&(Ref->getPosY() != Y)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  
	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR);
	}
      }
    }
  }
 
  if(!g.CHECK_BOUND(X-2,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-2,Y).getEtat() == 1 ){
 
    /*if(Ref != g.getCell(X-2,Y).getRef()){
      noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
      }else{
 
      if(indice != g.getCell(X-2,Y).getIles()->getIndice()){
      noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
      }
      }*/
    cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X-2,Y);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X-2,Y).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-2)&&(Ref->getPosY() != Y)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  
	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR);
	}
      }
    }
    
  }
 
  if(!g.CHECK_BOUND(X,Y+2,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y+2).getEtat() == 1 ){
 
    /* if(Ref != g.getCell(X,Y+2).getRef()){
       noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
       }else{

       if(indice != g.getCell(X,Y+2).getIles()->getIndice()){
       noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
       }
       }*/
     cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
     cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X,Y+2);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X,Y+2).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X)&&(Ref->getPosY() != Y+2)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  
	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR);
	}
      }
    }
   
  }

  if(!g.CHECK_BOUND(X,Y-2,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-2).getEtat() == 1){

    /*if(Ref != g.getCell(X,Y-2).getRef()){
      noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
      }else{
      if(indice != g.getCell(X,Y-2).getIles()->getIndice()){
      noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
      }
      }*/
     cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
     cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X,Y-2);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X,Y-2).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X)&&(Ref->getPosY() != Y-2)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  
	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR);
	}
      }
    }
   
  }
}
  


void blanchir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR){

  g.getCell(x,y).setEtat(1);

  bool fusion = false;
  bool endWhile = false;
  
  
  while (!endWhile){
    //---------------------------------------------------------------------------------------------------------------
    if ((y-1 > 0)&&(g.getCell(x,y-1).getEtat() == 1)){
      if (!fusion){
	
	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x,y-1);
	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	}
	if (buf2->getIles() != NULL){
	  
	  buf2->getIles()->addBlockCellToIles(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	  fusion = true;
	}

      } else if((fusion) && (g.getCell(x,y-1).getIles() == NULL)){

	blanchirAndRegleIles(g,GR,GI,x,y-1,intI,intR);
	endWhile = true;
	
	
      } else {

	g.getCell(x,y).setEtat(6);
	endWhile = true;
	
      }
      
    } 
    //------------------------------------------------------------------------------------------------------
    if ((y+1 < g.getDimensionY()-1)&&(g.getCell(x,y+1).getEtat() == 1)){
     
      if (!fusion){
	
	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x,y+1);
      
	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	}
	
	if (buf2->getIles() != NULL){
	
	  buf2->getIles()->addBlockCellToIles(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	  fusion = true;
	  
	}
      } else if((fusion) && (g.getCell(x,y-1).getIles() == NULL)){

	blanchirAndRegleIles(g,GR,GI,x,y+1,intI,intR);
	endWhile = true;

	
      } else {

	g.getCell(x,y).setEtat(6);
	endWhile = true;

	
      }
    }
    //------------------------------------------------------------------------------------------------------
    if ((x+1 < g.getDimensionX()-1)&&(g.getCell(x+1,y).getEtat() == 1)){
      
      if (!fusion){
	
	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x+1,y);
      
	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	}
	
	if (buf2->getIles() != NULL){
	  
	  buf2->getIles()->addBlockCellToIles(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	  fusion = true;
	 
	}
	else if((fusion) && (g.getCell(x,y-1).getIles() == NULL)){

	  blanchirAndRegleIles(g,GR,GI,x+1,y,intI,intR);
	  endWhile = true;
	 
	} else {

	  g.getCell(x,y).setEtat(6);
	  endWhile = true;
	  
	
	}
      }
    }
    //------------------------------------------------------------------------------------------------------
      
    if ((x-1 > 0)&&(g.getCell(x-1,y).getEtat() == 1)){
      
      if (!fusion){
	
	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x-1,y);
	
	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	}

	if (buf2->getIles() != NULL){
	  
	  buf2->getIles()->addBlockCellToIles(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	  fusion = true;
	  
	}
      } else if((fusion) && (g.getCell(x,y-1).getIles() == NULL)){
	
	blanchirAndRegleIles(g,GR,GI,x-1,y,intI,intR);
	endWhile = true;
	
      } else {
	g.getCell(x,y).setEtat(6);
	endWhile = true;
	
	
      }
    }
    
    if (!endWhile){
      
      endWhile = true;
    }

    
    //------------------------------------------------------------------------------------------------------
  }
  //------------------------------------------------------------------------------------------------------
}


  
void setPotentiel(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y){
  int X = x;
  int Y = y;
  int num = g.getCell(x,y).getCellNum();
  int ntop = 0;
  int nbot = 0;
  int j = num - 1 ;
  int J = j;

  while ( J > 0){
    int tmp = ntop ;
    // cout << "J = "<< J << " >----< " << tmp << endl; 
    while (tmp >=0 ){
      if( X-J >= 0){
	if( Y+tmp < g.getDimensionY() && Y-tmp >=0){
	  if(g.getCell(X-J,Y+tmp).getEtat() != 1 && g.getCell(X-J,Y-tmp).getEtat() != 1){
	    g.addEtat(4,X-J,Y+tmp);
	    g.addEtat(4,X-J,Y-tmp);
	  }else{
	    if(g.getCell(X-J,Y+tmp).getEtat() == 1 && g.getCell(X-J,Y-tmp).getEtat() != 1){
	      g.addEtat(4,X-J,Y-tmp); 
	    }
	    if(g.getCell(X-J,Y-tmp).getEtat() == 1 && g.getCell(X-J,Y+tmp).getEtat() != 1){
	      g.addEtat(4,X-J,Y+tmp);
	    }
	  }
	}else{
	  
	  if( Y+tmp >= g.getDimensionY() && Y-tmp>=0){
	    if(g.getCell(X-J,Y-tmp).getEtat() != 1){
	      g.addEtat(4,X-J,Y-tmp);
	    }
	  }
	  
	  if( Y-tmp < 0 && Y+tmp < g.getDimensionY()){
	    if(g.getCell(X-J,Y+tmp).getEtat() != 1){
	      g.addEtat(4,X-J,Y+tmp);
	    }
	  }	    
	}
      }
      tmp--;
    }
    ntop++;
    J--;
  }
  
  J = j;
  
  while ( J >= 0){
    int tmp1 = nbot ;
    // cout << "J = "<< J << " >----< " << tmp1 << endl; 
    while (tmp1 >=0 ){
      if( X+J < g.getDimensionX()){
	if( Y+tmp1 < g.getDimensionY() && Y-tmp1 >=0){
	  if(g.getCell(X+J,Y+tmp1).getEtat() != 1 && g.getCell(X+J,Y-tmp1).getEtat() != 1){
	    g.addEtat(4,X+J,Y+tmp1);
	    g.addEtat(4,X+J,Y-tmp1);
	  }else{
	    if(g.getCell(X+J,Y+tmp1).getEtat() == 1 && g.getCell(X+J,Y-tmp1).getEtat() != 1){
	      g.addEtat(4,X+J,Y-tmp1); 
	    }
	    if(g.getCell(X+J,Y-tmp1).getEtat() == 1 && g.getCell(X+J,Y+tmp1).getEtat() != 1){
	      g.addEtat(4,X+J,Y+tmp1);
	    }
	  }
	}else{
	  
	  if( Y+tmp1 >= g.getDimensionY() && Y-tmp1>=0){
	    if(g.getCell(X+J,Y-tmp1).getEtat() != 1){
	      g.addEtat(4,X+J,Y-tmp1);
	    }
	  }
	  
	  if( Y-tmp1 < 0 && Y+tmp1 < g.getDimensionY()){
	    if(g.getCell(X+J,Y+tmp1).getEtat() != 1){
	      g.addEtat(4,X+J,Y+tmp1);
	    }
	  }	    
	}
      }
      tmp1--;
    }
    nbot++;
    J--;
  }
}


void CroixNoircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indiceIles,int &indiceRiviere){
  int etatdeCellAdjacente;
  
  if(!g.CHECK_BOUND(x,y+1,g.getDimensionX(),g.getDimensionY())){
    etatdeCellAdjacente = g.getCell(x,y+1).getEtat();
  }
  
  
  if( etatdeCellAdjacente == 2 ){

    if(!g.CHECK_BOUND(x,y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(x,y-1).getEtat() == 2 ){

      if(!g.CHECK_BOUND(x-1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x-1,y).getEtat() == 2){

	if(!g.CHECK_BOUND(x+1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x+1,y).getEtat() == 2){

	  noircirAndRegleRiviere(g,GR,GI, x, y,indiceIles, indiceRiviere);
	}
      }
    }
  } else if ( etatdeCellAdjacente == 1 ){

    if(!g.CHECK_BOUND(x,y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(x,y-1).getEtat() == 1 ){
      
      if(!g.CHECK_BOUND(x-1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x-1,y).getEtat() == 1){
	
	if(!g.CHECK_BOUND(x+1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x+1,y).getEtat() == 1){

	  blanchirAndRegleIles(g,GR,GI, x, y,indiceIles, indiceRiviere);
	}
      }
    }
  }
}
	  


void friendsIles(Grille &g, Iles &ile, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR){
  
  if (ile.getRemaining() > 0){
    
    int nbChoix = 0;
    Cell* buf = NULL;
    Cell* buf2 = NULL;
    BlockCell* tmp = ile.getWhiteCells()->getHead();
    bool fin = false;
    
    while ((nbChoix < 3)&&(!fin)){

      if (tmp->getNextBlock() == NULL){
	fin = true;
      }
     
      if ((tmp->getCellPointer()->getPosX() - 1 >= 0)&&!(((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 3))) {
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()));
	  
	}
	nbChoix++;
	
      }
      if ((tmp->getCellPointer()->getPosX() + 1 <= g.getDimensionX()-1)&&!(((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 3))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()));
	  
	}
	nbChoix++;
      }
      if ((tmp->getCellPointer()->getPosY() - 1 >= 0)&&!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() < 3))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1));
	  
	}
	nbChoix++;
      }
      if ((tmp->getCellPointer()->getPosY() + 1 <= g.getDimensionY()-1)&&!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() < 3))){
	
	if (buf != NULL){
	  
	  buf2 = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1));
	  
	} else {
	  
	  buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1));
	  
	}
	nbChoix++;
      }
      tmp = tmp->getNextBlock();
      
    }
    cout<<"Le nombre de choix est: "<<nbChoix<<endl;
    if (nbChoix == 1){  // Première régle: si il n'y a qu'une case possible adjacente à l'Ile
      cout<<"Ouverture "<<endl;
      cout<<buf->getPosX()<<","<<buf->getPosY()<<endl;
      
      blanchirAndRegleIles(g,GR,GI,buf->getPosX(),buf->getPosY(),intI,intR);
      cout<<"Fermeture "<<endl;
      
    } else if (nbChoix == 2){ // Deuxième régle: si il n'y a que deux case possible adjacente à l'Ile et qu'elles sont en diagonal l'une de l'autre;
      cout<<ile.getRemaining()<<"ATTENTION BUG IN COMING"<<endl;
      if (ile.getRemaining() == 1){
	
	if ((buf2->getPosX() + 1  <= g.getDimensionX()-1)&&(buf2->getPosY() + 1  <= g.getDimensionY()-1)&&((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() + 1)))){
	  
	  if (g.getCell(buf2->getPosX(),(buf2->getPosY() + 1)).getEtat() == 1){

	    cout<<"A"<<endl;

	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()+1,buf2->getPosY(),intI,intR);
	    
	  } else {

	     cout<<"b"<<endl;

	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()+1,intI,intR);
	    
	  }
	  
	} else if ((buf2->getPosX() - 1 >= 0)&&(buf2->getPosY() - 1 >= 0)&&((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() - 1)))){
	  
	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	     cout<<"c"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()-1,intI,intR);
	    
	  } else {
	     cout<<"d"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()-1,buf2->getPosY(),intI,intR);
	    
	  }
	  
	} else if ((buf2->getPosX() + 1 <= g.getDimensionX()-1)&&(buf2->getPosY() - 1 >= 0)&&((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() - 1)))){
	  
	  if (g.getCell((buf2->getPosX() + 1),buf2->getPosY()).getEtat() == 1){
	     cout<<"e"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()-1,intI,intR);
	    
	  } else {
	     cout<<"f"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()+1,buf2->getPosY(),intI,intR);
	    
	  }
	  
	} else if ((buf2->getPosX() - 1 >= 0)&&(buf2->getPosY() + 1 <= g.getDimensionY()-1)&&((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() + 1)))){
	  
	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	     cout<<"g"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()+1,intI,intR);
	    
	  } else {
	     cout<<"h"<<endl;
	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()-1,buf2->getPosY(),intI,intR);
	    
	  }
	}
      }
    }
    cout<<"alalal"<<endl;
  }
}

void friendsRiviere(Grille &g,Riviere &riv, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR){
 
  int nbChoix = 0;
  Cell* buf = NULL;
  BlockCell* tmp = riv.getRiviere()->getHead();
  bool fin = false;
 
  while ((nbChoix < 2)&&(!fin)){

    if (tmp->getNextBlock() == NULL){
      fin = true;
	
    }
    
    if ((tmp->getCellPointer()->getPosX() - 1 >= 0)&&!(((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 3))) {
	
      buf = &g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()));
      nbChoix++;
      
    }
    if ((tmp->getCellPointer()->getPosX() + 1 <= g.getDimensionX()-1)&&!(((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 3))){
  
      buf = &g.getCell((tmp->getCellPointer()->getPosX() + 1),(tmp->getCellPointer()->getPosY()));
      nbChoix++;
    }
    if ((tmp->getCellPointer()->getPosY() - 1 >= 0)&&!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1))).getEtat() < 3))){
	
      buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() - 1));
      nbChoix++;
     
    }
    if ((tmp->getCellPointer()->getPosY() + 1 <= g.getDimensionY()-1)&&!(((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1))).getEtat() < 3))){
	
      buf = &g.getCell((tmp->getCellPointer()->getPosX()),(tmp->getCellPointer()->getPosY() + 1));
      nbChoix++;
     
    }
    tmp = tmp->getNextBlock();
  }
  if (nbChoix == 1){  // Première régle: si il n'y a qu'une case possible adjacente à l'Ile
    
    if(buf->getPosX()-1 >= 0){
      Cell* xUn = &g.getCell(buf->getPosX()-1,buf->getPosY());
      if (xUn->getRef() != NULL){
	xUn = xUn->getRef();
      }
      if (xUn->getIles() != NULL){
	friendsIles(g,*xUn->getIles(),GR,GI,intI,intR);
      }
    }

    if(buf->getPosX()+1 <= g.getDimensionX()-1){
      Cell* xDeux = &g.getCell(buf->getPosX()+1,buf->getPosY());
      if (xDeux->getRef() != NULL){
	xDeux = xDeux->getRef();
      }
      if (xDeux->getIles() != NULL){
	friendsIles(g,*xDeux->getIles(),GR,GI,intI,intR);
      }
    }

    if(buf->getPosY()-1 >= 0){
      Cell* xTrois = &g.getCell(buf->getPosX(),buf->getPosY()-1);
      if (xTrois->getRef() != NULL){
	xTrois = xTrois->getRef();
      }
      if (xTrois->getIles() != NULL){
	friendsIles(g,*xTrois->getIles(),GR,GI,intI,intR);
      }
    }

    if(buf->getPosY()+1 <= g.getDimensionY()-1){
      Cell* xQuatre = &g.getCell(buf->getPosX(),buf->getPosY()+1);
      if (xQuatre->getRef() != NULL){
	xQuatre = xQuatre->getRef();
      }
      if (xQuatre->getIles() != NULL){
	friendsIles(g,*xQuatre->getIles(),GR,GI,intI,intR);
      }
    }
    if ((buf->getEtat() != 1)||(buf->getEtat() != 2)||(buf->getEtat() != 5)){
       
      noircirAndRegleRiviere(g,GR,GI,buf->getPosX(),buf->getPosY(),intI,intR);
       
    }
  }
}

void unFriendsRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR){
  if (g.getCell(x,y).getEtat() == 2){
   
    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y+1).getEtat() == 2)&&(g.getCell(x+1,y).getEtat() == 2)){

	blanchirAndRegleIles(g,GR,GI,x,y+1,intI,intR);
    }
   
    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x+1,y-1).getEtat() == 2)&&(g.getCell(x+1,y).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x,y-1,intI,intR);
      
    }
    
    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y+1).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y,intI,intR);
     
    }
    
    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y+1).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y,intI,intR);
      
    }
    
    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x-1,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x,y+1,intI,intR);
     
    }
    
    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x-1,y-1).getEtat() == 2)){
      
      blanchirAndRegleIles(g,GR,GI,x,y-1,intI,intR);
      
    }
    
    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x,y-1).getEtat() == 2)&&(g.getCell(x-1,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y,intI,intR);
      
    }
    
    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x,y-1).getEtat() == 2)&&(g.getCell(x+1,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y,intI,intR);
      
    }
    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y-1,intI,intR);
      
    }
    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y+1,intI,intR);
      
    }
    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y+1,intI,intR);
      
    }
    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x+1,y).getEtat() == 2)&&(g.getCell(x,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y-1,intI,intR);
      
    }
  }
}
void noircirAndRegleRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR){
  if (g.getCell(x,y).getEtat() != 2){
    noircir(g,GR,GI,x,y,intR);
    
    Cell* buf = &g.getCell(x,y);
    while (buf->getRef() != NULL){
    buf = buf->getRef();
    }
    cout<<"l"<<x<<y<<endl;
    friendsRiviere( g, *buf->getRiv(), GR, GI, intI, intR);
    cout<<"la"<<endl;
    unFriendsRiviere( g, GR, GI, x, y, intI, intR);
    cout<<"laz"<<endl;
    g.getBlockCell(x,y).printBlock();
    g.GrillePrint();
  }
}


void blanchirAndRegleIles(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR){
  if (g.getCell(x,y).getEtat() != 1){
    blanchir(g,GR,GI,x,y,intI,intR);
    g.GrillePrint();
  
    Cell* buf = &g.getCell(x,y);
    
    while (buf->getRef() != NULL){
      buf = buf->getRef();
    }
    
    cout<<x<<","<<y<<endl;
    if (buf->getIles() != NULL){
      cout<<"toto"<<endl;
      UnfriendedIles(g,GR,GI,x,y,intI,intR);
      cout<<"toto"<<endl;
      friendsIles( g,*buf->getIles(), GR, GI, intI, intR);
      cout<<x<<" , "<<y<<endl;
      Complet(g,GR,GI,x,y,intI,intR);
      cout<<"toto"<<endl;
    }
    g.getBlockCell(x,y).printBlock();
    cout<<"HALAL"<<endl;
  }
}

void Complet(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x, int y,int &intI ,int &indice){

  Cell* buf = &g.getCell(x,y);
  while ( buf->getRef() != NULL){
    buf = buf->getRef();
  }
  
  BlockCell *tmp = buf->getIles()->getWhiteCells()->getHead();
  cout<<" TOTO " <<endl;
  
  if (buf->getIles()->estPleine()){
    cout<<" HEAD " <<endl;
    
    while ( tmp->getNextBlock() != NULL ){
      int X = tmp->getCellPointer()->getPosX();
      int Y = tmp->getCellPointer()->getPosY();
      
      if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
	cout<<" DN1 " <<endl;
	noircirAndRegleRiviere(g,GR,GI, X+1, Y,intI, indice);
	cout<<" FN1 " <<endl;
      }
      if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
	cout<<" DN2 " <<endl;
	noircirAndRegleRiviere(g,GR,GI, X-1, Y,intI, indice);
	cout<<" FN2 " <<endl;
      }
      if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
	cout<<" DN3 " <<endl;
	noircirAndRegleRiviere(g,GR,GI, X, Y+1,intI, indice);
	cout<<" FN3 " <<endl;
      }
      if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
	cout<<" DN4 " <<endl;
	noircirAndRegleRiviere(g,GR,GI, X, Y-1,intI, indice);
	cout<<" FN4 " <<endl;
      }
      tmp = tmp->getNextBlock();
      cout<<" FN " <<endl;
    }
    cout << "TOTO"<<endl;
    int X = tmp->getCellPointer()->getPosX();
    int Y = tmp->getCellPointer()->getPosY();
    
    if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
      noircirAndRegleRiviere(g,GR,GI, X+1, Y,intI, indice);
    }
    if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
      noircirAndRegleRiviere(g,GR,GI, X-1, Y,intI, indice);
    }
    if( !g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
      noircirAndRegleRiviere(g,GR,GI, X, Y+1,intI, indice);
	
    }
    if( !g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
      noircirAndRegleRiviere(g,GR,GI, X, Y-1,intI, indice);

    }
  }
  //delete tmp;*/
}

void initGrille(map<string,string>& data){
  int dimX;
  int dimY;
  int indiceRiviere = 1;
  int indiceIles = 0;
  GlobalRiviere GR;
  GlobalIles GI;
 
  getDataDimension(data,"dimensionX",dimX);
  getDataDimension(data,"dimensionY",dimY);
 
  Grille g(dimX,dimY);

  addCells(data,g);
 
  g.GrillePrint();
 
  //---------------------------------------
  //Debut initialisation
  //---------------------------------------
  cout << "============= DEBUT D'INIT DES POTENIELS =================="<<endl;
  int x = 0;
  int y = 0;
  while (x < dimX){
    y = 0;
    while (y < dimY){
      g.getCell(x,y).setPosX(x);
      g.getCell(x,y).setPosY(y);
      g.setCellPointerInBlockCell(x,y);
      if (g.getCell(x,y).getEtat() == 0){
	g.getCell(x,y).setEtat(3);
      } else if (g.getCell(x,y).getEtat() == 1){
	Iles *obj = new Iles(&g.getBlockCell(x,y),indiceIles);
	g.getCell(x,y).setIles(obj);
	indiceIles++;
	GI.AddIle(*obj);
	setPotentiel(g,GR,GI,x,y);
	g.GrillePrint();
      }
      y++;
    }
    x++;
  }
  g.GrillePrint();
 

  x = 0;
  y = 0;
  //--------------------------------------
  //Fin initialisation
  //--------------------------------------
  cout << " ================== AFFICHAGE DE LA GRILLE DES BLOCKCELLS ================" <<endl;
  while(true){
    x = 0;
    y = 0;
    while(x < dimX){
      y=0;
      while (y < dimY){
	if(g.getCell(x,y).getEtat() == 3){
	  noircirAndRegleRiviere(g,GR,GI,x,y,indiceIles,indiceRiviere);
	
	}else if(g.getCell(x,y).getEtat() == 5){
	  blanchirAndRegleIles(g,GR,GI,x,y,indiceIles,indiceRiviere);
	}else if(g.getCell(x,y).getEtat() == 4){
	  CroixNoircir(g,GR,GI,x,y,indiceIles,indiceRiviere);
	}else if(g.getCell(x,y).getEtat() == 1){
	  
	  Cell* buf = &g.getCell(x,y);
	  while (buf->getRef() != NULL){
	    buf = buf->getRef();
	  }
	  if (buf->getIles() != NULL){
	    cout<<"ON EST AVANT"<<endl;
	    friendsIles( g,*buf->getIles(), GR, GI, indiceIles, indiceRiviere);
	    cout<<"ON EST ENTRe 1"<<endl;
	    UnfriendedIles(g,GR,GI,x,y,indiceIles,indiceRiviere);
	    cout<<"ON EST ENTRe 2"<<endl;
	    Complet(g,GR,GI,x,y,indiceIles,indiceRiviere);
	    cout<<"ON EST APRES"<<endl;
	  }
	  g.GrillePrint();
	}else if(g.getCell(x,y).getEtat() == 2){
	  Cell* buf = &g.getCell(x,y);
	  while (buf->getRef() != NULL){
	    buf = buf->getRef();
	  }
	  if (buf->getRiv() != NULL){
	    
	    friendsRiviere( g, *buf->getRiv(), GR, GI, indiceIles, indiceRiviere);    
	    unFriendsRiviere( g, GR, GI, x, y, indiceIles, indiceRiviere);
	  }
	}
	y++;
      }
      x++;
    }
  }
   
   
  cout << " ============= AFFICHAGE DE LA GRILLE APRES L'INIT DES ZONES POTENTIELS =========== "<<endl;
  g.GrillePrint();


  cout << "============= AFFICHAGE DE CONTENU DE GLOBAL ILE ====================" <<endl;
  GI.printGlobalIles();


  cout << "============= AFFICHAGE DE CONTENU DE GLOBAL RIVIERE ====================" <<endl;
  GR.printGlobalRiviere();
  g.GrillePrint();

}



void MyProgram(int argc,char** argv){
  map<string,string> data;
  Option tabOption[5]={Option(Option::HELP,Option::AUCUN,"-h","==>L'aide de Jeu et affichage des options"),
		       Option(Option::DIMENSION,Option::AUCUN,"-d","==>determiner les dimensions dimension de la grille"),
		       Option(Option::CONFIG,Option::STRING,"-cfg","==>Configurer les cellules en passant un ficher de config"),
		       Option(Option::VERSION,Option::AUCUN,"-v","==>Version de programme"),
  		       Option(Option::AUTHORS,Option::AUCUN,"-a","==>auteurs de Programme")};
  if(argc==1){
    data.insert(std::pair<string,string>("dimensionX","15"));
    data.insert(std::pair<string,string>("dimensionY","15"));
    data.insert(std::pair<string,string>("nbrDeCell","3"));
    data.insert(std::pair<string,string>("C1","(0,2,5,1)"));
    data.insert(std::pair<string,string>("C2","(0,6,2,1)"));
    data.insert(std::pair<string,string>("C3","(2,2,1,1)"));
    initGrille(data);
    data.erase(data.begin(),data.end());
  }else{
    for(int i=1;i<argc;i++){
      for(int j=0;j<5;j++){
	
	if(argv[i][0]=='-'){
	  if(argv[i] == tabOption[j].getraccourci()){
	    launchOption(tabOption,tabOption[j],i,argv,data);
	  }
	}else{
	  
	  string s = ID2String(tabOption[j].getId());
	  
	  if(argv[i] == s ){
	    launchOption(tabOption,tabOption[j],i,argv,data);
	  }
	  
	}
	
      }
      
    } 
  }
  if(!data.empty()){
    initGrille(data);    
  }
}
 
 
