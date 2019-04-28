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
/**----------------
   recuperer a partir de la map une valeur a partir de sa clé
   on s'en sert principalement pour recuperer les deux dimensions
   de la grille

 --------------**/

void getDataDimension(map<string,string>& data,string key,int &value){
  const char* k =  data[key].c_str();
  value = atoi(k);
}

/**-----------
   prend en entré une valeur ( dans ce cas les données de la cellule
   à initialiser depuis le fichier de config )apres sa recuperation depuis le map
   et faire un traitement sur cette val
   ---------**/
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
/**------------
   prend en param le map des donnees de config et la grille
   et recupere les donnees des cellules a initialiser
   faire un traitement et les rajouter a la grille
--------------* */
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


/**--------------------
   une des fonction principale de programme qui prend en param deux
   vector le premier regroupe tout les iles de la grille et le deuxieme
   tout les rivieres , la grille , coordonnées X et Y d'une cellule
   et l'indice qui indique l'ordre de creation d'une riviere
   noircit la cellule et soit fusionne avec la(es) riviere(es)
   adjacente(s) soit créé une nouvelle riviere
   ---------------**/

void noircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y, int &intR,bool &Fini){
  //cout<< "WAAAAAAAAAAAAAAAAHYAAAA2"<<endl;

  if( g.getCell(x,y).getEtat() != 2 && g.getCell(x,y).getEtat() != 1 ){
    Fini = false;
    g.getCell(x,y).setEtat(2);
    cout<<g.getCell(x,y).getEtat()<<endl;
    
    if ( !carreNoire(g,g.getCell(x,y))){
      //  cout<< "WAAAAAAAAAAAAAAAAHYAAAA3"<<endl;
      
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

       	if(buf != buf2){
	  if ( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){

	    //-------------------------------------------------------------
	    //  cout << "FUUUUUUUUUUUUUUUCK"<<endl;
	    // cout << buf->getPosX()<<","<<buf->getPosY()<<endl;

	    buf2->getRiv()->addBlockCellToRiviere(&g.getBlockCell( buf->getPosX(),buf->getPosY() ), GR,GI);
	    //cout << "FUUUUUUUUUUUUUUUCK2"<<endl;
	    buf2->getRiv()->printRiv();
	  }else{
	    // cout << "FUUUUUUUUUUUUUUUCK3"<<endl;
	    buf->getRiv()->addBlockCellToRiviere(&g.getBlockCell( buf2->getPosX(),buf2->getPosY() ), GR,GI);
	    //    cout << "FUUUUUUUUUUUUUUUCK4"<<endl;
	  }

	  fusion = true;
	  // g.getCell(x,y).getRef()->getRiv()->printRiv();
	}
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

	if(buf != buf2){
	  if( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){
	    //  cout<<"C'est la ou ça plante"<<endl;

	    //-------------------------------------------------------------

	    buf2->getRiv()->addBlockCellToRiviere(&g.getBlockCell( buf->getPosX(),buf->getPosY() ), GR,GI);

	  }else {

	    buf->getRiv()->addBlockCellToRiviere(&g.getBlockCell( buf2->getPosX(),buf2->getPosY() ), GR,GI);

	  }

	  fusion = true;
	  //  g.getCell(x,y).getRef()->getRiv()->printRiv();

	}
	}

      //-----------Troisieme-fusion---------------------------------------

      if ( (x < g.getDimensionX()-1) && (g.getCell(x+1,y).getEtat() == 2) ){

	//-----------Verification-de-la-riviere-la-plus-petite-----------

	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x+1,y);

	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	}
	cout<<buf2->getPosX()<<endl;
	cout<<buf2->getPosY()<<endl;

	while (buf->getRef() != NULL){
	  buf = buf->getRef();
	}

       	if(buf != buf2){

	if( (buf->getRiv() == NULL)  || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){

	    //cout<<"C'est la ou ça plante"<<endl;
	    //-------------------------------------------------------------

	    buf2->getRiv()->addBlockCellToRiviere(&g.getBlockCell(buf->getPosX(),buf->getPosY()), GR,GI);
	    //	cout<<"C'est la ou ça plante"<<endl;
	  } else {
	  //cout<<"C'est la ou ça plante"<<endl;
	    buf->getRiv()->addBlockCellToRiviere(&g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR,GI);

	  }

	  fusion = true;
	  //	  g.getCell(x,y).getRef()->getRiv()->printRiv();
	  //cout<<"C'est la ou ça plante"<<endl;
	}
      }

      //-----------Quatrieme-fusion---------------------------------------

      if ( (x > 0) && (g.getCell(x-1,y).getEtat() == 2) ){

	//-----------Verification-de-la-riviere-la-plus-petite-----------

	Cell* buf = &g.getCell(x,y);
	Cell* buf2 = &g.getCell(x-1,y);

	while (buf2->getRef() != NULL){
	  buf2 = buf2->getRef();
	  // cout<<"C'est la ou ça plante"<<endl;
	}
	//cout<<"C'est la ou ça plante"<<endl;
	while (buf->getRef() != NULL){

	  buf = buf->getRef();
	}

       	if(buf != buf2){

	  if ( (buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() >= buf->getRiv()->getTailleRiviere()) ){
	    //cout<<"C'est la ou ça plante"<<endl;

	    //-------------------------------------------------------------

	    buf2->getRiv()->addBlockCellToRiviere(&g.getBlockCell(buf->getPosX(),buf->getPosY()), GR,GI);

	  } else {
	    //cout<<"C'est la ou ça plante"<<endl;
	    buf->getRiv()->addBlockCellToRiviere(&g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR,GI);

	  }

	  fusion = true;
	  //  g.getCell(x,y).getRef()->getRiv()->printRiv();

	}
      }
      //----------------------------------------------------------------


      if(!fusion){

	Riviere* r = new Riviere(&g.getBlockCell(x,y),intR);
	g.getCell(x,y).setRiv(r);
	intR++;
	GR.AddRiviere(r);
	g.getCell(x,y).getRiv()->printRiv();
	}
    }else{
      g.getCell(x,y).setEtat(6);
    }
  }else{
    if (g.getCell(x,y).getEtat() == 1){
      g.getCell(x,y).setEtat(6);
    }
  }

  g.GrillePrint();
}

void UnfriendedIles(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR,bool &Fini){

  Cell* Ref = g.getCell(x,y).getRef();
  //cout<<"REF"<<endl;
  Cell* buf = &g.getCell(x,y);
  //c//out<<"buf"<<endl;

  while ( buf -> getRef() != NULL){
    buf = buf->getRef();
    //cout << "fucklol"<<endl;
  }
  // cout<<"ON EST ENTRe"<<endl;
  int indice = buf->getIles()->getIndice();
  cout<< indice<<endl;
  int X = g.getCell(x,y).getPosX();
  int Y = g.getCell(x,y).getPosY();
  
  //cout<<"=============("<<x<<","<<y<<")================"<<endl;
  if(!g.CHECK_BOUND(X+1,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y+1).getEtat() == 1){
    //cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    //cout<<" IL CHECK CE CONNARD 1"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+1,Y+1);
    while ( buf -> getRef() != NULL){
      // cout << "fuck256"<<endl;
      buf = buf->getRef();
    }
    
    if( ( Ref != g.getCell(X+1,Y+1).getRef()) && (Ref != NULL) && (Ref->getPosX() != X+1) && (Ref->getPosY() != Y+1)){
      //cout<<"=============("<<x<<","<<y<<")================"<<endl;
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
      }
    }else{
      //cout<<"=============("<<x<<","<<y<<")================"<<endl;
      if (buf->getIles() != NULL){
	//	cout<<"=============("<<x<<","<<y<<")================"<<endl;
	if(indice != buf->getIles()->getIndice()){
	  // cout<<"=============("<<x<<","<<y<<")================"<<endl;
	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
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
    // cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    // cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+1,Y-1);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      //cout << "fuckdvf"<<endl;
    }
    if(( Ref != g.getCell(X+1,Y-1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X+1)&&(Ref->getPosY() != Y-1)){
      //cout << "fuckdvf"<<endl;
      if (buf->getIles() != NULL){
	//cout << "fuckdvf"<<endl;
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
      }
    }else{
      // cout << "fuckdvf"<<endl;
      if (buf->getIles() != NULL){
	//cout << "fuckdvf"<<endl;
	if(indice != buf->getIles()->getIndice()){
	  // cout<< "L'indice est bien DIfferent "<<endl;
	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
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
      // cout << "fuckhfh"<<endl;
    }
    if(( Ref != g.getCell(X-1,Y-1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-1)&&(Ref->getPosY() != Y-1)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
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
      //cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X-1,Y+1).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-1)&&(Ref->getPosY() != Y+1)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){
	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
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
    //cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    // cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X+2,Y);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      // cout << "fuck"<<endl;
    }
    if((Ref != g.getCell(X+2,Y).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X+2)&&(Ref->getPosY() != Y)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){

	  noircirAndRegleRiviere(g,GR,GI,X+1,Y,intI,intR,Fini);
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
    //cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    //cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X-2,Y);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      //cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X-2,Y).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X-2)&&(Ref->getPosY() != Y)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){

	  noircirAndRegleRiviere(g,GR,GI,X-1,Y,intI,intR,Fini);
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
    // cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    //cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X,Y+2);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      //cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X,Y+2).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X)&&(Ref->getPosY() != Y+2)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){

	  noircirAndRegleRiviere(g,GR,GI,X,Y+1,intI,intR,Fini);
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
    // cout<<" IL CHECK CE CONNARD"<<x<<","<<y<<endl;
    //cout<<" IL CHECK CE CONNARD"<<X+2<<","<<Y<<endl;
    Cell* buf = &g.getCell(X,Y-2);
    while ( buf -> getRef() != NULL){
      buf = buf->getRef();
      //cout << "fuck"<<endl;
    }
    if(( Ref != g.getCell(X,Y-2).getRef())&&(Ref != NULL)&&(Ref->getPosX() != X)&&(Ref->getPosY() != Y-2)){
      if (buf->getIles() != NULL){
	noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
      }
    }else{
      if (buf->getIles() != NULL){
	if(indice != buf->getIles()->getIndice()){

	  noircirAndRegleRiviere(g,GR,GI,X,Y-1,intI,intR,Fini);
	}
      }
    }

  }
}




bool IleContientPlus(GlobalIles &GI){
  //cout<< "CELL BLANCE ISOLEEEEEEREEEEEEEEEEE"<<endl;
  for(size_t i =0; i < GI.getGlobalIle().size();i++){
    if(GI.getGlobalIle()[i]->getRemaining() < 0){
      return true;
    }

  }
  return false;
}


/**-------------------------
   deuxieme fonction principale de programme
   qui prend les memes parametres que noircir
   plus un indice de creation des iles
   et qui blanchit la cellule et fusionne avec une ile
   adjacente si elle existe

 **---------------------**/
void blanchir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI,int &intR,bool &Fini){
  // cout<<" AYOUB "<<endl;
  // cout<< x << ", " << y <<endl;

  // cout<< g.getCell(x,y).getEtat() <<endl;

  if(  g.getCell(x,y).getEtat() != 2 && !IleContientPlus(GI)){

    g.getCell(x,y).setEtat(1);
    // cout<<g.getCell(x,y).getEtat()<<endl;

    bool end = false;
    Cell* bufIles = NULL;
    Cell* bufNonIles1 = NULL;
    Cell* bufNonIles2 = NULL;
    Cell* bufNonIles3 = NULL;
    Cell* buf2 = NULL;

    //---------------------------------------------------------------------------------------------------------------
    if ((y-1 >= 0)&&(g.getCell(x,y-1).getEtat() == 1)){
      //cout<<"on verfiie la cell de y--1"<<endl;
      buf2 = &g.getCell(x,y-1);

      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }

      if (buf2->getIles() != NULL && (bufIles == NULL) && !GI.ToutEstComplet()){
	bufIles = buf2;
      }else if (buf2->getIles() == NULL && !GI.ToutEstComplet()){
	if (bufNonIles1 == NULL){
	  bufNonIles1 = buf2;
	} else if (bufNonIles2 == NULL){
	  bufNonIles2 = buf2;
	} else if (bufNonIles3 == NULL){
	  bufNonIles3 = buf2;
	} else {
	  end = true;
	}
      } else if (buf2->getIles() != NULL && (bufIles != NULL) && (buf2->getIles() != bufIles->getIles()) && !GI.ToutEstComplet()){
	g.getCell(x,y).setEtat(6);
	end = true;
      }
    }
    //------------------------------------------------------------------------------------------------------

    if ((y+1 <= g.getDimensionY()-1)&&(g.getCell(x,y+1).getEtat() == 1)){

      buf2 = &g.getCell(x,y+1);

      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }

      if (buf2->getIles() != NULL && (bufIles == NULL) && !GI.ToutEstComplet()){

	bufIles = buf2;

      }else if (buf2->getIles() == NULL && !GI.ToutEstComplet()){

	if (bufNonIles1 == NULL){
	  bufNonIles1 = buf2;
	} else if (bufNonIles2 == NULL){
	  bufNonIles2 = buf2;
	} else if (bufNonIles3 == NULL){
	  bufNonIles3 = buf2;
	} else {
	  end = true;
	}

      } else if (buf2->getIles() != NULL && (bufIles != NULL) && (buf2->getIles() != bufIles->getIles()) && !GI.ToutEstComplet()){

	g.getCell(x,y).setEtat(6);
	end = true;

      }
    }
    //------------------------------------------------------------------------------------------------------
    if ((x+1 <= g.getDimensionX()-1)&&(g.getCell(x+1,y).getEtat() == 1)){

      buf2 = &g.getCell(x+1,y);


      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
      if (buf2->getIles() != NULL && (bufIles == NULL) && !GI.ToutEstComplet()){

	bufIles = buf2;

      }else if (buf2->getIles() == NULL && !GI.ToutEstComplet()){

	if (bufNonIles1 == NULL){
	  bufNonIles1 = buf2;
	} else if (bufNonIles2 == NULL){
	  bufNonIles2 = buf2;
	} else if (bufNonIles3 == NULL){
	  bufNonIles3 = buf2;
	} else {
	  end = true;
	}

      } else if (buf2->getIles() != NULL && (bufIles != NULL) && (buf2->getIles() != bufIles->getIles()) && !GI.ToutEstComplet()){

	g.getCell(x,y).setEtat(6);
	end = true;

      }
    }

    //------------------------------------------------------------------------------------------------------

    if ((x-1 >= 0)&&(g.getCell(x-1,y).getEtat() == 1)){

      buf2 = &g.getCell(x-1,y);
      // g.getCell(x-1,y).getIles()->print();

      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }

      if (buf2->getIles() != NULL && (bufIles == NULL) && !GI.ToutEstComplet()){

	bufIles = buf2;

      }else if (buf2->getIles() == NULL && !GI.ToutEstComplet()){

	if (bufNonIles1 == NULL){
	  bufNonIles1 = buf2;
	} else if (bufNonIles2 == NULL){
	  bufNonIles2 = buf2;
	} else if (bufNonIles3 == NULL){
	  bufNonIles3 = buf2;
	} else {
	  end = true;
	}

      } else if (buf2->getIles() != NULL && (bufIles != NULL) && (buf2->getIles() != bufIles->getIles()) && !GI.ToutEstComplet()){

	g.getCell(x,y).setEtat(6);
	end = true;

      }
      //------------------------------------------------------------------------------------------------------
    }
    //  cout << buf2 << "/////////" << &g.getCell(x-1,y)<<endl;
    if ((!end)&&(bufIles != NULL)){
      //  cout<<"AVANT AJOUT DE LA CELL A L'ILE"<<endl;
      // GI.printGlobalIles();

      //  if(g.getBlockCell(x,y).getNextBlock() == NULL)
	//	cout<<"15265956541862"<<endl;
      BlockCell* bufbis = &g.getBlockCell(x,y);

      bufIles->getIles()->addBlockCellToIles(bufbis, GR,GI);
      //  cout<<"APRéS AJOUT DE LA CELL A L'ILE"<<endl;
      // GI.printGlobalIles();

      if (bufNonIles1 != NULL){
	blanchir(g,GR,GI,bufNonIles1->getPosX(),bufNonIles1->getPosY(),intI,intR,Fini);
      }
      if (bufNonIles2 != NULL){
	blanchir(g,GR,GI,bufNonIles2->getPosX(),bufNonIles2->getPosY(),intI,intR,Fini);
      }
      if (bufNonIles3 != NULL){
	blanchir(g,GR,GI,bufNonIles3->getPosX(),bufNonIles3->getPosY(),intI,intR,Fini);
      }
      //  cout<<"APRéS AJOUT DES CELLS QUI éTAIS BLANCHE MAIS PAS DES ILES A L'ILE"<<endl;
      //  GI.printGlobalIles();

    }
  }else{
    if(IleContientPlus(GI)){
      g.getCell(x,y).setEtat(6);
    }
  }
  g.GrillePrint();
}


/**--------------------------
   prend en parametres une grille , coordonees de l'ile
   et les deux vector GlobalIle et qui initialise les cellules
   potentiellement blanche dans la grille en mettant leurs
   etat a 4 qui est l'etat potentiel (couleur Bleu sur le terminal)
-----------------------**/
void setPotentiel(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y){
  int X = x;
  int Y = y;
  int num = g.getCell(x,y).getCellNum();
  int ntop = 0;
  int nbot = 0;
  int J = num - 1;

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

  J = num -1;

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

/**----------------------------

   etat particulier d'une cellule entouré par une croix de cellules qui ont
   le meme etat, dans ce cas on met la cellule en question dans la meme
   couleur.
 **----------------------**/

void CroixNoircir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &indiceIles,int &indiceRiviere,bool& Fini){
  int etatdeCellAdjacente;

  if(!g.CHECK_BOUND(x,y+1,g.getDimensionX(),g.getDimensionY())){
    etatdeCellAdjacente = g.getCell(x,y+1).getEtat();
  }


  if( etatdeCellAdjacente == 2 ){

    if(!g.CHECK_BOUND(x,y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(x,y-1).getEtat() == 2 ){

      if(!g.CHECK_BOUND(x-1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x-1,y).getEtat() == 2){

	if(!g.CHECK_BOUND(x+1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x+1,y).getEtat() == 2){

	  noircirAndRegleRiviere(g,GR,GI, x, y,indiceIles, indiceRiviere,Fini);
	}
      }
    }
  } else if ( etatdeCellAdjacente == 1 ){

    if(!g.CHECK_BOUND(x,y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(x,y-1).getEtat() == 1 ){

      if(!g.CHECK_BOUND(x-1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x-1,y).getEtat() == 1){

	if(!g.CHECK_BOUND(x+1,y,g.getDimensionX(),g.getDimensionY()) && g.getCell(x+1,y).getEtat() == 1){

	  blanchirAndRegleIles(g,GR,GI, x, y,indiceIles, indiceRiviere,Fini);
	}
      }
    }
  }
}

/**-------------------------
   verifier si pour une ile il reste seulement un trajet possible
   pour sortir et completer cette ile dans ce cas on blanchit
   les cellules sur ce trajet et on les rajoute a l'ile passée en parametre

 **-----------------------**/

void friendsIles(Grille &g, Iles &ile, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR,bool &Fini){
  // cout<<"ON ESt LA"<<endl;
  if (ile.getRemaining() > 0){
    //  cout << "Ile remaining : "<<ile.getRemaining()<<endl;
    //cout << " vrai et le remaining : " << ile.getWhiteCells()->getSize()<<endl;
    //ile.getWhiteCells()->printListe();
    int nbChoix = 0;
    Cell* buf = NULL;
    Cell* buf2 = NULL;
    BlockCell* tmp = ile.getWhiteCells()->getHead();
    bool fin = false;

    while ((nbChoix < 3)&&(!fin)){

      if (tmp->getNextBlock() == NULL){
	fin = true;
      }

      if ((tmp->getCellPointer()->getPosX() - 1 >= 0) && !( ((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() > 0) && ((g.getCell((tmp->getCellPointer()->getPosX() - 1),(tmp->getCellPointer()->getPosY()))).getEtat() < 3))) {

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
    // cout<<"Le nombre de choix est: "<<nbChoix<<endl;
    if (nbChoix == 1){  // Première régle: si il n'y a qu'une case possible adjacente à l'Ile
      //cout<<"Ouverture "<<endl;
      // cout<<buf->getPosX()<<","<<buf->getPosY()<<endl;

      blanchirAndRegleIles(g,GR,GI,buf->getPosX(),buf->getPosY(),intI,intR,Fini);
      // cout<<"Fermeture "<<endl;

    } else if (nbChoix == 2){ // Deuxième régle: si il n'y a que deux case possible adjacente à l'Ile et qu'elles sont en diagonal l'une de l'autre;
      //cout<<ile.getRemaining()<<"ATTENTION BUG IN COMING"<<endl;
      if (ile.getRemaining() == 1){

	if ((buf2->getPosX() + 1  <= g.getDimensionX()-1)&&(buf2->getPosY() + 1  <= g.getDimensionY()-1)&&((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() + 1)))){

	  if (g.getCell(buf2->getPosX(),(buf2->getPosY() + 1)).getEtat() == 1){

	    //    cout<<"A"<<endl;

	    noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()+1,buf2->getPosY(),intI,intR,Fini);

	  } else {

	    //cout<<"b"<<endl;

	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()+1,intI,intR,Fini);

	  }

	} else if ((buf2->getPosX() - 1 >= 0)&&(buf2->getPosY() - 1 >= 0)&&((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() - 1)))){

	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	    //cout<<"c"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()-1,intI,intR,Fini);

	  } else {
	    //cout<<"d"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()-1,buf2->getPosY(),intI,intR,Fini);

	  }

	} else if ((buf2->getPosX() + 1 <= g.getDimensionX()-1)&&(buf2->getPosY() - 1 >= 0)&&((buf->getPosX() == (buf2->getPosX() + 1)) && (buf->getPosY() == (buf2->getPosY() - 1)))){

	  if (g.getCell((buf2->getPosX() + 1),buf2->getPosY()).getEtat() == 1){
	    // cout<<"e"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()-1,intI,intR,Fini);

	  } else {
	    // cout<<"f"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()+1,buf2->getPosY(),intI,intR,Fini);

	  }

	} else if ((buf2->getPosX() - 1 >= 0)&&(buf2->getPosY() + 1 <= g.getDimensionY()-1)&&((buf->getPosX() == (buf2->getPosX() - 1)) && (buf->getPosY() == (buf2->getPosY() + 1)))){

	  if (g.getCell((buf2->getPosX() - 1),buf2->getPosY()).getEtat() == 1){
	    //cout<<"g"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX(),buf2->getPosY()+1,intI,intR,Fini);

	  } else {
	    // cout<<"h"<<endl;
	     noircirAndRegleRiviere(g,GR,GI,buf2->getPosX()-1,buf2->getPosY(),intI,intR,Fini);

	  }
	}
      }
    }
    //  cout<<"alalal"<<endl;
  }
}


/***-----------------------
    meme principe que FriendsIles mais pour les rivieres
    càd que pour que la riviere soit connexe il y a un seul trajet possible
    on noircit les cellules qui se trouve sur ce trajet et on les fusionne avec
    la riviere et eventuellement d'autre rivieres s'ils se croisent

 **-------------------------*/
void friendsRiviere(Grille &g,Riviere &riv, GlobalRiviere& GR,GlobalIles& GI, int& intI, int& intR,bool &Fini){

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
    // cout<< "AVANT ILE REM"<<endl;
    //cout<< buf->getPosX() <<", "<< buf->getPosY()<<endl;
    if(buf->getPosX()-1 >= 0){
      Cell* xUn = &g.getCell(buf->getPosX()-1,buf->getPosY());
      if (xUn->getRef() != NULL){
	xUn = xUn->getRef();
      }
      if (xUn->getIles() != NULL){
	friendsIles(g,*xUn->getIles(),GR,GI,intI,intR,Fini);
      }
    }

    if(buf->getPosX()+1 <= g.getDimensionX()-1){
      Cell* xDeux = &g.getCell(buf->getPosX()+1,buf->getPosY());
      if (xDeux->getRef() != NULL){
	xDeux = xDeux->getRef();
      }
      if (xDeux->getIles() != NULL){
	friendsIles(g,*xDeux->getIles(),GR,GI,intI,intR,Fini);
      }
    }

    if(buf->getPosY()-1 >= 0){
      Cell* xTrois = &g.getCell(buf->getPosX(),buf->getPosY()-1);
      if (xTrois->getRef() != NULL){
	xTrois = xTrois->getRef();
      }
      if (xTrois->getIles() != NULL){
	friendsIles(g,*xTrois->getIles(),GR,GI,intI,intR,Fini);
      }
    }

    if(buf->getPosY()+1 <= g.getDimensionY()-1){
      Cell* xQuatre = &g.getCell(buf->getPosX(),buf->getPosY()+1);
      if (xQuatre->getRef() != NULL){
	xQuatre = xQuatre->getRef();
      }
      if (xQuatre->getIles() != NULL){
	friendsIles(g,*xQuatre->getIles(),GR,GI,intI,intR,Fini);
      }
    }
    if ((buf->getEtat() != 1)&&(buf->getEtat() != 2)&&(buf->getEtat() != 5)){

      noircirAndRegleRiviere(g,GR,GI,buf->getPosX(),buf->getPosY(),intI,intR,Fini);

    }
  }
}

void unFriendsRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR,bool &Fini){
  if (g.getCell(x,y).getEtat() == 2){

    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y+1).getEtat() == 2)&&(g.getCell(x+1,y).getEtat() == 2)){

      blanchirAndRegleIles(g,GR,GI,x,y+1,intI,intR,Fini);
    }

    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x+1,y-1).getEtat() == 2)&&(g.getCell(x+1,y).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x,y-1,intI,intR,Fini);

    }

    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y+1).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y,intI,intR,Fini);

    }

    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y+1).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y,intI,intR,Fini);

    }

    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x-1,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x,y+1,intI,intR,Fini);

    }

    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x-1,y-1).getEtat() == 2)){

      blanchirAndRegleIles(g,GR,GI,x,y-1,intI,intR,Fini);

    }

    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x,y-1).getEtat() == 2)&&(g.getCell(x-1,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y,intI,intR,Fini);

    }

    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x,y-1).getEtat() == 2)&&(g.getCell(x+1,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y,intI,intR,Fini);

    }
    if((x-1 >= 0)&&(y-1 >= 0)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y-1,intI,intR,Fini);

    }
    if((x+1 <= g.getDimensionX()-1)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x+1,y).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y+1,intI,intR,Fini);

    }
    if((x-1 >= 0)&&(y+1 <= g.getDimensionY()-1)&&(g.getCell(x-1,y).getEtat() == 2)&&(g.getCell(x,y+1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x-1,y+1,intI,intR,Fini);

    }
    if((x+1 <= g.getDimensionX()-1)&&(y-1 >= 0)&&(g.getCell(x+1,y).getEtat() == 2)&&(g.getCell(x,y-1).getEtat() == 2)){
      blanchirAndRegleIles(g,GR,GI,x+1,y-1,intI,intR,Fini);

    }
  }
}

/*---------------------------------

  Fonction global qui fait appel a noircir et applique les regles
  sur les rivieres

 ----------------------------**/
void noircirAndRegleRiviere(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR,bool& Fini){
  //   cout<< "WAAAAAAAAAAAAAAAAHYAAAA66"<<endl;
  //  cout << g.getCell(x,y).getEtat() <<endl;
  //  cout<< "WAAAAAAAAAAAAAAAAHYAAAA66"<<endl;
  if (g.getCell(x,y).getEtat() != 2 && g.getCell(x,y).getEtat() != 1 && !IleContientPlus(GI) ){
    //cout<<"=============("<<x<<","<<y<<")================"<<endl;
    noircir(g,GR,GI,x,y,intR,Fini);
    //cout<< "WAAAAAAAAAAAAAAAAHYAAAA"<<endl;
    if ( g.getCell(x,y).getEtat() != 6){
      Cell* buf = &g.getCell(x,y);
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }
      //cout<<"l"<<x<<y<<endl;
      friendsRiviere( g, *buf->getRiv(), GR, GI, intI, intR,Fini);
      // cout<<"la"<<endl;
      unFriendsRiviere( g, GR, GI, x, y, intI, intR,Fini);
      //cout<<"laz"<<endl;
      // g.getBlockCell(x,y).printBlock();
      //g.GrillePrint();
    }else{

      //    cout<< "ERREUr Noire"<<endl;
    }
  }else{
    if(g.getCell(x,y).getEtat() == 1 || IleContientPlus(GI)){
      g.getCell(x,y).setEtat(6);
      //   cout<< "ERREUr NoiRe"<<endl;
    }
  }
}

/*---------------------------------

  Fonction global qui fait appel a blanchir et applique les regles
  sur les iles

 ----------------------------**/
void blanchirAndRegleIles(Grille &g, GlobalRiviere& GR,GlobalIles& GI,int x,int y, int& intI, int& intR,bool& Fini){
  //cout<<" avant Etat:  "<< g.getCell(x,y).getEtat()<<endl;
  if (g.getCell(x,y).getEtat() != 1  && g.getCell(x,y).getEtat() != 2 && !IleContientPlus(GI)){
    cout<<" avant blanchir "<<endl;
    blanchir(g,GR,GI,x,y,intI,intR,Fini);
    if(g.getCell(x,y).getEtat() != 6){
      cout<<" apres blanchir "<<endl;
      //cout<<g.getCell(x,y).getEtat()<<endl;
      if (g.getCell(x,y).getRef() == NULL){
	//	cout<<" probleme "<<endl;
      }
      //  g.GrillePrint();

      Cell* buf = &g.getCell(x,y);

      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }

      // cout<<x<<","<<y<<endl;
      if (buf->getIles() != NULL){
	//	cout<<"===========UNFRIENDED ILES========="<<endl;
	UnfriendedIles(g,GR,GI,x,y,intI,intR,Fini);
	//cout<<"================FRIENDED ILES==============="<<endl;
	friendsIles( g,*buf->getIles(), GR, GI, intI, intR,Fini);
	////	cout<<"=================COMPLET============="<<endl;
	//Complet(g,GR,GI,x,y,intI,intR,Fini);
	//GR.printGlobalRiviere();
	//	cout<<"toto"<<endl;
      }
      //  g.getBlockCell(x,y).printBlock();
      //cout<<"HALAL"<<endl;
    }
  }else{
    if(g.getCell(x,y).getEtat() == 2 || IleContientPlus(GI)){
      g.getCell(x,y).setEtat(6);
      //    cout<< "ERREUr Blanche"<<endl;
    }
  }
}


/*---------------------------
  dans le cas ou y a une iles complete cette fonction
  noircit les cells autour pour l'isolée
  ---------------------*/

void Complet(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x, int y,int &intI ,int &indice,bool &Fini){

  Cell* buf = &g.getCell(x,y);
  while ( buf->getRef() != NULL){
    buf = buf->getRef();
  }

  // cout<<"ON eTS DANS COMPLET"<<endl;
  // GR.printGlobalRiviere();

  BlockCell *tmp = buf->getIles()->getWhiteCells()->getHead();
  // cout<<" TOTO " <<endl;
  //cout<<"---------------"<<buf->getIles()->getRemaining()<<endl;
  if (buf->getIles()->estPleine()){
    //cout<<" HEAD " <<endl;

    while ( tmp->getNextBlock() != NULL ){
      int X = tmp->getCellPointer()->getPosX();
      int Y = tmp->getCellPointer()->getPosY();

      if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
	//	cout<<" DN1 " <<endl;
	//noircirAndRegleRiviere(g,GR,GI, X+1, Y,intI, indice,Fini);
	noircir(g,GR,GI, X+1, Y, indice,Fini);
	//cout<<" FN1 " <<endl;
      }
      if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
	//cout<<" DN2 " <<endl;
	//	noircirAndRegleRiviere(g,GR,GI, X-1, Y,intI, indice,Fini);
	noircir(g,GR,GI, X-1, Y, indice,Fini);
	//cout<<" FN2 " <<endl;
      }
      if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
	//cout<<" DN3 " <<endl;
	//noircirAndRegleRiviere(g,GR,GI, X, Y+1,intI, indice,Fini);
	noircir(g,GR,GI, X, Y+1, indice,Fini);
	//	cout<<" FN3 " <<endl;
      }
      if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
	//cout<<" DN4 " <<endl;
	//noircirAndRegleRiviere(g,GR,GI, X, Y-1,intI, indice,Fini);
	noircir(g,GR,GI, X, Y-1,indice,Fini);
	//cout<<" FN4 " <<endl;
      }
      tmp = tmp->getNextBlock();
      //cout<<" FN " <<endl;
    }
    //cout << "TOTO"<<endl;
    int X = tmp->getCellPointer()->getPosX();
    int Y = tmp->getCellPointer()->getPosY();

    if( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() != 1 && g.getCell(X+1,Y).getEtat() != 2 ){
      //noircirAndRegleRiviere(g,GR,GI, X+1, Y,intI, indice,Fini);
      noircir(g,GR,GI, X+1, Y,indice,Fini);
    }
    if( !g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X-1,Y).getEtat() != 1 && g.getCell(X-1,Y).getEtat() != 2 ){
      //      noircirAndRegleRiviere(g,GR,GI, X-1, Y,intI, indice,Fini);
      noircir(g,GR,GI, X-1, Y,indice,Fini);
    }
    if( !g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y+1).getEtat() != 1 && g.getCell(X,Y+1).getEtat() != 2 ){
      //      noircirAndRegleRiviere(g,GR,GI, X, Y+1,intI, indice,Fini);
      noircir(g,GR,GI, X, Y+1,indice,Fini);

    }
    if( !g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() != 1 && g.getCell(X,Y-1).getEtat() != 2 ){
      //      noircirAndRegleRiviere(g,GR,GI, X, Y-1,intI, indice,Fini);
      noircir(g,GR,GI, X, Y-1,indice,Fini);

    }
  }
  //delete tmp;*/
}

bool Resoudre(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int &indiceIles ,int &indiceRiviere){
  bool Fini = false;
  int x = 0;
  int y = 0;
  int dimX = g.getDimensionX();
  int dimY = g.getDimensionY();

  while( !GI.ToutEstComplet() && !Fini ){
    Fini = true;

    x = 0;
    y = 0;
    while(x < dimX && !GI.ToutEstComplet()){
      y=0;
      //cout<<"=============("<<x<<","<<y<<")================"<<endl;
      while (y < dimY && !GI.ToutEstComplet()){
	//cout<<"=============("<<x<<","<<y<<")================"<<endl;
	if(g.getCell(x,y).getEtat() == 3 && !GI.ToutEstComplet()){

	  noircirAndRegleRiviere(g,GR,GI,x,y,indiceIles,indiceRiviere,Fini);


	}else if(g.getCell(x,y).getEtat() == 5 && !GI.ToutEstComplet()){
	  blanchirAndRegleIles(g,GR,GI,x,y,indiceIles,indiceRiviere,Fini);

	}else if(g.getCell(x,y).getEtat() == 4 && !GI.ToutEstComplet()){
	  // cout<<"erfjrjevvvvvvvvvvvvvvvvvvvvvvvvvvvds"<<endl;
	  CroixNoircir(g,GR,GI,x,y,indiceIles,indiceRiviere,Fini);
	  // cout<<"erfjrjevvvvvvvvvvvvvvvvvvvvvvvvvvvds"<<endl;

	}else if(g.getCell(x,y).getEtat() == 1 && !GI.ToutEstComplet()){
	  //	  cout<<"=============("<<x<<","<<y<<")================"<<endl;
	  Cell* buf = &g.getCell(x,y);
	  while (buf->getRef() != NULL){
	    buf = buf->getRef();
	  }
	  if (buf->getIles() != NULL && !GI.ToutEstComplet()){
	    //    cout<<"ON EST AVANT"<<endl;
	    friendsIles( g,*buf->getIles(), GR, GI, indiceIles, indiceRiviere,Fini);
	    // cout<<"ON EST ENTRe 1"<<endl;
	    UnfriendedIles(g,GR,GI,x,y,indiceIles,indiceRiviere,Fini);
	    //cout<<"ON EST ENTRe 2"<<endl;
	    Complet(g,GR,GI,x,y,indiceIles,indiceRiviere,Fini);
	    //cout<<"ON EST APRES"<<endl;

	  }
	  g.GrillePrint();
	}else if(g.getCell(x,y).getEtat() == 2){
	  Cell* buf = &g.getCell(x,y);
	  while (buf->getRef() != NULL){
	    buf = buf->getRef();
	  }
	  if (buf->getRiv() != NULL){

	    friendsRiviere( g, *buf->getRiv(), GR, GI, indiceIles, indiceRiviere,Fini);
	    unFriendsRiviere( g, GR, GI, x, y, indiceIles, indiceRiviere,Fini);

	  }
	}
	y++;
      }
      x++;
    }
  }

  return  GI.ToutEstComplet();

}

bool carreNoire(Grille &g,const Cell &c ){
  int X = c.getPosX();
  int Y = c.getPosY();
  int dimX = g.getDimensionX();
  int dimY = g.getDimensionY();
  if(c.getEtat() == 2 ){
    //cout<<"DAAAAAAAAAAAAAAAAAAAAAAAAAMN"<<endl;
    if(!g.CHECK_BOUND(X+1,Y+1,dimX,dimY) && g.getCell(X+1,Y).getEtat() == 2 && g.getCell(X+1,Y+1).getEtat() == 2 && g.getCell(X,Y+1).getEtat() == 2){
      return true;

    }

    if( !g.CHECK_BOUND(X+1,Y-1,dimX,dimY) && g.getCell(X+1,Y).getEtat() == 2 && g.getCell(X+1,Y-1).getEtat() == 2 && g.getCell(X,Y-1).getEtat() == 2){
      return true;
    }

    
    if(!g.CHECK_BOUND(X-1,Y-1,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 2 && g.getCell(X-1,Y-1).getEtat() == 2 && g.getCell(X,Y-1).getEtat() == 2){
      return true ;
    }
    //cout<<"DAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMN2"<<endl;
  if(!g.CHECK_BOUND(X-1,Y+1,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 2 && g.getCell(X-1,Y+1).getEtat() == 2 && g.getCell(X,Y+1).getEtat() == 2){
      return true ;
    }
  }
  // cout<< "ON A QUITTE CARRE NOIRE AVEC FALSE"<<endl;
  return false;
}

bool carreBlanche(Grille &g,int i,int j){
  int X = i;
  int Y = j;
  int dimX = g.getDimensionX();
  int dimY = g.getDimensionY();
  if(g.getCell(i,j).getEtat() == 1 ){
    //  cout<<"===============("<<i<<','<<j<<")============================"<<endl;
    if(!g.CHECK_BOUND(X+1,Y+1,dimX,dimY) && !g.CHECK_BOUND(X+2,Y+1,dimX,dimY)  && g.getCell(X+1,Y).getEtat() == 1 && g.getCell(X+1,Y+1).getEtat() == 1 && g.getCell(X,Y+1).getEtat() == 1 && g.getCell(X+2,Y).getEtat() == 1 && g.getCell(X+2,Y+1).getEtat() == 1){
      return true;

    }

    if( !g.CHECK_BOUND(X+1,Y-1,dimX,dimY) && !g.CHECK_BOUND(X+2,Y-1,dimX,dimY) && g.getCell(X+1,Y).getEtat() == 1 && g.getCell(X+1,Y-1).getEtat() == 1 && g.getCell(X,Y-1).getEtat() == 1 && g.getCell(X+2,Y).getEtat() == 1 && g.getCell(X+2,Y-1).getEtat() == 1){
      return true;
    }

    
    if(!g.CHECK_BOUND(X-1,Y-1,dimX,dimY) && !g.CHECK_BOUND(X-2,Y-1,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 1 && g.getCell(X-1,Y-1).getEtat() == 1 && g.getCell(X,Y-1).getEtat() == 1 && g.getCell(X-2,Y).getEtat() == 1 && g.getCell(X-2,Y-1).getEtat() == 1){
      return true ;
    }

    if(!g.CHECK_BOUND(X-1,Y+1,dimX,dimY) &&  !g.CHECK_BOUND(X-2,Y+1,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 1 && g.getCell(X-1,Y+1).getEtat() == 1 && g.getCell(X,Y+1).getEtat() == 1 && g.getCell(X-2,Y).getEtat() == 1 && g.getCell(X-2,Y+1).getEtat() == 1){
      return true ;
    }

     if(!g.CHECK_BOUND(X+1,Y+1,dimX,dimY) && !g.CHECK_BOUND(X+1,Y+2,dimX,dimY)  && g.getCell(X+1,Y).getEtat() == 1 && g.getCell(X+1,Y+1).getEtat() == 1 && g.getCell(X,Y+1).getEtat() == 1 && g.getCell(X+1,Y+2).getEtat() == 1 && g.getCell(X,Y+2).getEtat() == 1){
      return true;

    }
     
     if( !g.CHECK_BOUND(X+1,Y-1,dimX,dimY) && !g.CHECK_BOUND(X+1,Y-2,dimX,dimY) && g.getCell(X+1,Y).getEtat() == 1 && g.getCell(X+1,Y-1).getEtat() == 1 && g.getCell(X,Y-1).getEtat() == 1 && g.getCell(X,Y-2).getEtat() == 1 && g.getCell(X+1,Y-2).getEtat() == 1){
      return true;
    }

     if(!g.CHECK_BOUND(X-1,Y-1,dimX,dimY) && !g.CHECK_BOUND(X-1,Y-2,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 1 && g.getCell(X-1,Y-1).getEtat() == 1 && g.getCell(X,Y-1).getEtat() == 1 && g.getCell(X-1,Y-2).getEtat() == 1 && g.getCell(X,Y-2).getEtat() == 1){
       return true ;
     }
     
     if(!g.CHECK_BOUND(X-1,Y+1,dimX,dimY) &&  !g.CHECK_BOUND(X-1,Y+2,dimX,dimY) && g.getCell(X-1,Y).getEtat() == 1 && g.getCell(X-1,Y+1).getEtat() == 1 && g.getCell(X,Y+1).getEtat() == 1 && g.getCell(X-1,Y+2).getEtat() == 1 && g.getCell(X,Y+2).getEtat() == 1){
       return true ;
     }
  }

  return false;
}


bool IleIsole(Grille &g,GlobalIles &GI){
  for(size_t i = 0; i<GI.getGlobalIle().size() ; i++){
    if(GI.getGlobalIle()[i]->getRemaining() > 0 ){
      //cout<<"=============//DANS ILe ISOLE//=================="<<endl;
      BlockCell * buf = GI.getGlobalIle()[i]->getWhiteCells()->getHead();
      int X = 0 ;
      int Y = 0;
      while( buf ){
	X = buf->getCellPointer()->getPosX();
	Y = buf->getCellPointer()->getPosY();
	
	if ( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X-1,Y).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() ==4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() == 4){
	  return false;
	}
	
	buf = buf->getNextBlock();
      }
      // cout<<"//===============//L'ile "<< i <<" //EST ISOLE=================="<<endl; 
      return true;
      
    }
  }
  return false;
  
}

bool CellNoireIsolebis(Grille &g,GlobalIles &GI,int i,int j){

  if( g.getCell(i,j).getEtat() == 2){
    int cmpt = 0;
    if( g.getCell(i,j).getRef() != NULL){
      Cell* tmp = &g.getCell(i,j);
      while(tmp->getRef() != NULL){
	tmp = tmp->getRef();
      }
      int X = tmp->getPosX();
      int Y = tmp->getPosY();
      BlockCell *buf = &g.getBlockCell(X,Y);

      
      while(buf){
	X = buf->getCellPointer()->getPosX();
	Y = buf->getCellPointer()->getPosY();
	if ( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat()==4 ){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X-1,Y).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() == 4){
	  return false;
	}

	buf = buf->getNextBlock();
	cmpt++;
      }
      
      if(cmpt < (  (g.getDimensionX()*g.getDimensionY() ) - GI.SommeDiles() ) || cmpt >  (  (g.getDimensionX()*g.getDimensionY() ) - GI.SommeDiles() ) ){
	return true;
      }else{
	return false;
      }
    
    }else{
      int X= 0 ;
      int Y = 0;
      BlockCell *buf = &g.getBlockCell(i,j);
      
      while(buf){
	X = buf->getCellPointer()->getPosX();
	Y = buf->getCellPointer()->getPosY();
	
	if ( !g.CHECK_BOUND(X+1,Y,g.getDimensionX(),g.getDimensionY()) && g.getCell(X+1,Y).getEtat()==4 ){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X-1,Y,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X-1,Y).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(X,Y+1).getEtat() == 4){
	  return false;
	}
	
	if(!g.CHECK_BOUND(X,Y-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(X,Y-1).getEtat() == 4){
	  return false;
	}

	buf = buf->getNextBlock();
	cmpt++;
      }
      
      if(cmpt < (  (g.getDimensionX()*g.getDimensionY() ) - GI.SommeDiles() ) || cmpt >  (  (g.getDimensionX()*g.getDimensionY() ) - GI.SommeDiles() ) ){
	return true;
      }else{
	return false;
      }
      
      
    }
  }
  return false;
}

bool CellBlancheIsolebis(Grille &g,int i,int j, int posXDePremierAppel,int posYDePremierAppel,vector<Cell*> tmp){

  if(g.getCell(i,j).getEtat() == 1 && g.getCell(i,j).getRef() == NULL && g.getCell(i,j).getIles() == NULL){
    
    if(!g.getCell(i,j).getDejaVu()){
    
      
      
      Cell* buf1 = NULL;
      Cell* buf2 = NULL;
      Cell* buf3 = NULL;
      Cell* buf4 = NULL;
      //  cout << "===================ON EST DANS CELLB ISOLE BIS "<< "("<<i<<","<<j<<")"<<" ==================1====================="<<endl;
      
      
      
      if ( !g.CHECK_BOUND(i+1,j,g.getDimensionX(),g.getDimensionY()) && (i+1 != posXDePremierAppel || j != posYDePremierAppel)  ){
	if( g.getCell(i+1,j).getEtat() == 1 ){
	  buf1 = &g.getCell( i+1,j);
	}else{
	  if(g.getCell(i+1,j).getEtat() != 2){
	    
	    return false;
	  }
	}
      }
      
      if ( !g.CHECK_BOUND(i-1,j,g.getDimensionX(),g.getDimensionY()) && (i-1 != posXDePremierAppel || j != posYDePremierAppel   )  ){
	if( g.getCell(i-1,j).getEtat() == 1 ){
	  buf2 = &g.getCell( i-1,j);
	}else{
	  if(g.getCell(i-1,j).getEtat() != 2){
	    return false;
	  }
	}
      }
      
      if ( !g.CHECK_BOUND(i,j+1,g.getDimensionX(),g.getDimensionY()) && (i != posXDePremierAppel || j+1 != posYDePremierAppel ) ){
	if( g.getCell(i,j+1).getEtat() == 1 ){
	  buf3 = &g.getCell(i,j+1);
	}else{
	  if(g.getCell(i,j+1).getEtat() != 2){
	    return false;
	  }
	}
      }
      
      if ( !g.CHECK_BOUND(i,j-1,g.getDimensionX(),g.getDimensionY()) && (i != posXDePremierAppel || j-1 != posYDePremierAppel ) ){
	if( g.getCell(i,j-1).getEtat() == 1 ){
	  buf4 = &g.getCell( i,j-1);
	}else{
	  if(g.getCell(i,j-1).getEtat() != 2){
	    return false;
	  }
	}
      }
      
      if( buf1 || buf2 || buf3 || buf4){
	
	g.getCell(i,j).setDejaVu(true);
	tmp.push_back(&g.getCell(i,j));

	if(buf1 && buf2 && buf3 && buf4){
	  return CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp)&& CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp); 
	}else{
	  
	  if(buf1){
	    if(buf2){
	      
	      if( buf3){
		return CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp);
	      }else{
		if(!buf4){
		  return  CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp);
		}else{
		  return CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
		}
	      }
	      
	    }else{
	      if(buf3){
		if(buf4){
		  return CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
		}else{
		  return  CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp);
		}
	      }else{
		if(buf4){
		  return   CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
		}else{
		  return  CellBlancheIsolebis(g,buf1->getPosX(),buf1->getPosY(),i,j,tmp);
		}
	      }
	      
	    }
	    
	  }
	  
	  //========================================================
	  if(buf2){
	    if(buf3){
	      if(buf4){
		return CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
	      }else{
		return  CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp) &&  CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp);
	      }
	    }else{
	      return    CellBlancheIsolebis(g,buf2->getPosX(),buf2->getPosY(),i,j,tmp);
	    }
	  }

	  if(buf3){
	    if(buf4){
	      return CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp) && CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
	    }else{
	      return CellBlancheIsolebis(g,buf3->getPosX(),buf3->getPosY(),i,j,tmp);
	    }
	  }
	
	  if(buf4){
	    return CellBlancheIsolebis(g,buf4->getPosX(),buf4->getPosY(),i,j,tmp);
	  }
	
	}
	
      }else{
	return true;
      }
    }
  }
  
  return false;  
}


bool CellNoireIsole(Grille &g,int i , int j){
  //cout <<i<< j <<endl;
  if(g.getCell(i,j).getEtat() == 2){
    if ( !g.CHECK_BOUND(i+1,j,g.getDimensionX(),g.getDimensionY()) && g.getCell(i+1,j).getEtat() != 1){
      return false;
    }

    if(!g.CHECK_BOUND(i-1,j,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i-1,j).getEtat() != 1){
      return false;
    }

    if(!g.CHECK_BOUND(i,j+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i,j+1).getEtat() != 1){
      return false;
    }

    if(!g.CHECK_BOUND(i,j-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(i,j-1).getEtat() != 1){
      return false;
    }
  
  return true;
  }
  return false;
}

bool CellBlancheIsole(Grille &g,int i , int j){
  // cout << "ON EST DANS CELLB ISOLE"<<endl;
  if(g.getCell(i,j).getRef() == NULL && g.getCell(i,j).getIles() == NULL){
    if ( !g.CHECK_BOUND(i+1,j,g.getDimensionX(),g.getDimensionY()) && g.getCell(i+1,j).getEtat() != 2){
      return false;
    }

    if(!g.CHECK_BOUND(i-1,j,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i-1,j).getEtat() != 2){
      return false;
    }

    if(!g.CHECK_BOUND(i,j+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i,j+1).getEtat() != 2){
      return false;
    }

    if(!g.CHECK_BOUND(i,j-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(i,j-1).getEtat() != 2){
      return false;
    }

    return true;

  }else{
    //    bool isole = true;
    if( g.getCell(i,j).getIles() != NULL &&  g.getCell(i,j).getIles()->getNumCell() != 1 && g.getCell(i,j).getIles()->getRemaining() > 0 ){


	if ( !g.CHECK_BOUND(i+1,j,g.getDimensionX(),g.getDimensionY()) && g.getCell(i+1,j).getEtat() != 2){
	  return false;
	 }

	if(!g.CHECK_BOUND(i-1,j,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i-1,j).getEtat() != 2){
	  return false;
	}

	if(!g.CHECK_BOUND(i,j+1,g.getDimensionX(),g.getDimensionY()) &&  g.getCell(i,j+1).getEtat() != 2){
	  return false;
	}

	if(!g.CHECK_BOUND(i,j-1,g.getDimensionX(),g.getDimensionY()) && g.getCell(i,j-1).getEtat() != 2){
	  return false;
	}

	return true;
    }
  }
  // cout<< "CELL BLANCE NON ISOLEEEEEEREEEEEEEEEEE"<<endl;
  return false;
}


bool Conflit(Grille &g,GlobalIles &GI){
  if(IleContientPlus(GI)) return true;
  if(IleIsole(g,GI)) return true;

  vector<Cell*> tmp;
  //) || CellBlancheIsolebis(g,i,j,tmp)
  for(int i = 0 ; i < g.getDimensionX();i++){
    for(int j = 0 ; j < g.getDimensionY();j++){
      // cout<<" dans Conflit"<<endl;
      if(g.getCell(i,j).getEtat() == 6 || carreNoire(g,g.getCell(i,j)) || CellNoireIsole(g,i,j) || CellNoireIsolebis(g,GI,i,j) || CellBlancheIsole(g,i,j) || CellBlancheIsolebis(g,i,j,i,j,tmp )) {
	return true;
      }
      vector<Cell*>().swap(tmp);
    }
  }
  

  return false;
}


Cell& choixCell(Grille &g){
Cell res;
  //cout << " ON EST DANS LE CHOIX De CELL "<<endl;
  int i = 0 ;
  while(i < g.getDimensionX()  ){
    // cout << i << endl;
    //cout << "ON est en plein recherche"<<endl;
    for(int j = 0 ; j < g.getDimensionY() ;j++){
      // cout<< i <<" ," <<j <<endl;
      if(g.getCell(i,j).getEtat() == 4){
	return g.getCell(i,j);
      }
    }
    i++;
  }
  //  cout<<"fin de choix de cell"<<endl;
  /* while(res->getEtat() != 4){
     res = &g.getCell( rand() % (g.getDimensionX()-1) , rand() % (g.getDimensionY() -1));

     }*/
  
  return res;
}

void transformer(GlobalIles &GI,GlobalRiviere &GR,Grille &g){
  for(size_t i = 0 ; i < GI.getGlobalIle().size(); i++){
    BlockCell *tmp =  GI.getGlobalIle()[i]->getWhiteCells()->getHead();
    GI.getGlobalIle()[i]->getWhiteCells()->setHead(&g.getBlockCell(tmp->getCellPointer()->getPosX(),tmp->getCellPointer()->getPosY()));

  }

 for(size_t i = 0 ; i < GR.getGlobalRiv().size(); i++){
    BlockCell *tmp1 =  GR.getGlobalRiv()[i]->getRiviere()->getHead();
    GR.getGlobalRiv()[i]->getRiviere()->setHead(&g.getBlockCell(tmp1->getCellPointer()->getPosX(),tmp1->getCellPointer()->getPosY()));
  }
}

bool backTrack(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int &indiceIles ,int &indiceRiviere,Grille& res,GlobalRiviere &GRres,GlobalIles &GIres){
  Grille sauvG(g.getDimensionX(),g.getDimensionY()) ;;
  GlobalIles sauvGI;
  GlobalRiviere sauvGR;
  int sauvI ;
  int sauvR ;
  Cell cell ;
  bool Fini;
  bool bt;
  g.GrillePrint();
  if( GI.ToutEstComplet()  && GR.RiviereConnexe((g.getDimensionX()*g.getDimensionY()) - GI.SommeDiles())){
    
    res = g;
    GRres = GR;
    
    GIres = GI;
    
    transformer(GIres,GRres,res);
    return true;

  }else{

    //--------------
    if(g.rempli()){
      
      return false;
      
    }else{

      sauvG = g;
      sauvI = indiceIles;
      sauvR = indiceRiviere;
      sauvGR = GR;
      sauvGI = GI;
      transformer(sauvGI,sauvGR,sauvG);
      //------------
      //cell = choixCell(g,GR,GI,indiceIles,indiceRiviere,g.getDimensionX(),g.getDimensionY());
      cell = choixCell(g);
      blanchirAndRegleIles(g,GR,GI,cell.getPosX(),cell.getPosY(),indiceIles,indiceRiviere,Fini);
      //blanchir(g,GR,GI,cell.getPosX(),cell.getPosY(),indiceIles,indiceRiviere,Fini);
      g.GrillePrint();
      if(Conflit(g,GI)){
	///--------------

	noircirAndRegleRiviere(sauvG,sauvGR,sauvGI,cell.getPosX(),cell.getPosY(),sauvI,sauvR,Fini);
	//noircir(sauvG,sauvGR,sauvGI,cell.getPosX(),cell.getPosY(),sauvR,Fini);
	sauvG.GrillePrint();
	if( Conflit(sauvG,sauvGI) ) {
	  return false;
	}else{

	  bt = backTrack(sauvG,sauvGR,sauvGI,sauvI,sauvR,res,GRres,GIres);
	  if(bt){
	    return true;
	  }else{
	    return false;
	  }

	}
      }else{
	bt = backTrack(g,GR,GI,indiceIles,indiceRiviere,res,GRres,GIres);

	if(!bt){
	  
	  noircirAndRegleRiviere(sauvG,sauvGR,sauvGI,cell.getPosX(),cell.getPosY(),sauvI,sauvR,Fini);
	  //noircir(sauvG,sauvGR,sauvGI,cell.getPosX(),cell.getPosY(),sauvR,Fini);
	  sauvG.GrillePrint();
	  if(Conflit(sauvG,sauvGI)){
	    return false;
	    
	  }else{
	    bt = backTrack(sauvG,sauvGR,sauvGI,sauvI,sauvR,res,GRres,GIres);
	   if(bt){
	     return true;
	   }else{
	     return false;
	   }
	   
	  }
	}else{
	  return  true;
	}
      }
    }
  }
}



void initGrille(map<string,string>& data){
  int dimX;
  int dimY;
  int indiceRiviere = 0;
  int indiceIles = 0;
  GlobalRiviere GR;
  GlobalIles GI;

  getDataDimension(data,"dimensionX",dimX);
  getDataDimension(data,"dimensionY",dimY);

  Grille g(dimX,dimY);
  //ajout des cellules ( Iles) a la grille depuis data

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
	GI.AddIle(obj);
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
  bool resolu = Resoudre(g,GR,GI,indiceIles,indiceRiviere);
  bool Continuer = 0;
  cout<<" REsolu ===> "<< resolu << "==> La grille n'as pas pu etre résolu avec que les regles"<<endl;
  cout<<" Veuillez alors choisir de continuer la résolution avec le Backtrack ou quitter :"<<endl;
  cout<<" ---------> Continuer (tapez 1)"<<endl;
  cout<<" ---------> Quitter (tapez 0)"<<endl;
  cin>>Continuer;
  
  
  if(!resolu && Continuer){
    Grille res(g.getDimensionX(),g.getDimensionY());
    GlobalRiviere GRres;
    GlobalIles GIres;
    if(backTrack(g,GR,GI,indiceIles,indiceRiviere,res,GRres,GIres)){
      
      cout << "============= AFFICHAGE DE CONTENU DE GLOBAL ILE ====================" <<endl;
      GIres.printGlobalIles();
      cout << "============= AFFICHAGE DE CONTENU DE GLOBAL RIVIERE ====================" <<endl;
      GRres.printGlobalRiviere();
      res.GrillePrint();
      
    }else{
      cout<<"CETTE GRILLE N'A PAS DE SOlution " << endl;
    }
    
  }else{
    cout << "============= AFFICHAGE DE CONTENU DE GLOBAL ILE ====================" <<endl;
    GI.printGlobalIles();
    cout << "============= AFFICHAGE DE CONTENU DE GLOBAL RIVIERE ====================" <<endl;
    GR.printGlobalRiviere();
    g.GrillePrint();


  }
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
    data.clear();
  }else{

    for(int i=1;i<argc;i++){
      for(int j=0;j<5;j++){

	if(argv[i][0]=='-'){
	  if(argv[i] == tabOption[j].getraccourci())
	    launchOption(tabOption,tabOption[j],i,argv,data);

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
  data.clear();
}
