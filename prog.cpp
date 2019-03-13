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
  
  if(g.getCell(x,y).getEtat() == 3){
    
    g.getCell(x,y).setEtat(2);
    //  g.getCell(x,y).setRiv(new Riviere(&g.getBlockCell(x,y),1));
    

    bool fusion = false;

    //-----------Premiere-fusion---------------------------------------
    
    if ((y > 0)&&(g.getCell(x,y-1).getEtat() == 2)){

      /* if (g.getCell(x,y-1).getRef() == NULL){

	g.getCell(x,y-1).getRiv()->addBlockCellToRiviere(g.getBlockCell(x,y), GR);
	cout << "ON EST LA"<< endl;
      } else {

	Cell* buf = g.getCell(x,y-1).getRef();
	
	while (buf->getRef() != NULL){
	  buf = buf->getRef();
	}
	
        buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(x,y), GR);
	buf = NULL;
	
      }

      fusion = true;
      // if( g.getCell(x,y).getRef() != NULL){
      g.getCell(x,y).getRef()->getRiv()->printRiv();
	// cout << "ON EST LA"<< endl;
	// }
      cout << "ON EST LA"<< endl;*/
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x,y-1);

      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
    
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      
      }
      
      if ((buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() > buf->getRiv()->getTailleRiviere())){
	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	
      } else {
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);
	
      }
      
      fusion = true;
      //  g.getCell(x,y).getRef()->getRiv()->printRiv();
    }
    
    //-----------Deuxieme-fusion---------------------------------------
    
    if ((y < g.getDimensionY()-1)&&(g.getCell(x,y+1).getEtat() == 2)){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
      
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x,y+1);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
      
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }
      
      if ((buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() > buf->getRiv()->getTailleRiviere())){
	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	
      } else {
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);
	
      }
      
      fusion = true;
      //  g.getCell(x,y).getRef()->getRiv()->printRiv();

    }

    //-----------Troisieme-fusion---------------------------------------

    if ((x < g.getDimensionX()-1)&&(g.getCell(x+1,y).getEtat() == 2)){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
      
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x+1,y);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();
      }
      
      while (buf->getRef() != NULL){
	buf = buf->getRef();
      }
      
       if((buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() > buf->getRiv()->getTailleRiviere())){
	
	//-------------------------------------------------------------
	
	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);
	
      } else {
	
	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);
	
      }
      
      fusion = true;
      // g.getCell(x,y).getRef()->getRiv()->printRiv();
      
    }

    //-----------Quatrieme-fusion---------------------------------------

    if ((x > 0)&&(g.getCell(x-1,y).getEtat() == 2)){

      //-----------Verification-de-la-riviere-la-plus-petite-----------
     
      Cell* buf = &g.getCell(x,y);
      Cell* buf2 = &g.getCell(x-1,y);
      
      while (buf2->getRef() != NULL){
	buf2 = buf2->getRef();

      }

      while (buf->getRef() != NULL){

	buf = buf->getRef();
      }


      
      if ((buf->getRiv() == NULL) || (buf2->getRiv()->getTailleRiviere() > buf->getRiv()->getTailleRiviere())){
	
	//-------------------------------------------------------------

	buf2->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf->getPosX(),buf->getPosY()), GR);

      } else {

	buf->getRiv()->addBlockCellToRiviere(g.getBlockCell(buf2->getPosX(),buf2->getPosY()), GR);

      }

      fusion = true;
      //  g.getCell(x,y).getRef()->getRiv()->printRiv();
      
    }
    //----------------------------------------------------------------
   

    if(!fusion){
      
      Riviere* riv = new Riviere(&g.getBlockCell(x,y),intR);
      g.getCell(x,y).setRiv(riv);
      intR++;
      GR.AddRiviere(*riv);
      // g.getCell(x,y).getRiv()->printRiv();
    }
    
  }
  
  
}

void blanchir(Grille &g,GlobalRiviere &GR,GlobalIles &GI,int x,int y,int &intI){

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



void applicationRegle(Grille& g,GlobalRiviere& GR,GlobalIles& GI,int x,int y){}


void initGrille(map<string,string>& data){
 int dimX;
 int dimY;
 int indiceRiviere = 1;
 int indiceIles = 1;
 GlobalRiviere GR;
 GlobalIles GI;
 
 getDataDimension(data,"dimensionX",dimX);
 getDataDimension(data,"dimensionY",dimY);
 
 Grille g(dimX,dimY);

 addCells(data,g);

 /* BlockCell cell6(&(g.getCell(5,4)));
  BlockCell cell7(&(g.getCell(1,1)));
  BlockCell cell8(&(g.getCell(1,2)));

  ListeCell L1(&cell6);
  L1.fusion(L1.getHead(),& cell7,GR);
  cout << endl;
  L1.printListe();
  L1.fusion(L1.getHead(),& cell8,GR);
  L1.printListe();
 */
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
   while(x < dimX){
    y=0;
    while (y < dimY){
      if(g.getCell(x,y).getEtat() == 3){
	noircir(g,GR,GI,x,y,indiceRiviere);
      }else if(g.getCell(x,y).getEtat() == 5){
      	blanchir(g,GR,GI,x,y,indiceIles);
      }
      g.getBlockCell(x,y).printBlock();
      y++;
    }
    x++;
  }
   cout << " ============= AFFICHAGE DE LA GRILLE APRES L'INIT DES ZONES POTENTIELS =========== "<<endl;
  g.GrillePrint();

  cout << "============= AFFICHAGE DE CONTENU DE GLOBAL ILE ====================" <<endl;
  GI.printGlobalIles();

  cout << "============= AFFICHAGE DE CONTENU DE GLOBAL RIVIERE ====================" <<endl;
  GR.printGlobalRiviere();
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



