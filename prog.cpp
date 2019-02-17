#include"grille.h"
#include<iostream>
#include"ListeCell.h"
#include"option.h"
#include"prog.h"
#include<map>
#include<cstdlib>
#include<cstdio>

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
  y = atoi((val.substr(0,res)).c_str());
  val = val.substr(res+1);
  num = atoi((val.substr(0,res)).c_str());
}

void addCells(map<string,string> &data,Grille &g){
 int posX;
 int posY;
 int etat;
 int num;
 
 map<string,string>::iterator itr;
 itr = data.find("numCell");
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

void initGrille(map<string,string>& data){
 int dimX;
 int dimY;

 
 getDataDimension(data,"dimensionX",dimX);
 getDataDimension(data,"dimensionY",dimY);
 
 Grille g(dimX,dimY);

 addCells(data,g);

  BlockCell cell6(&(g.getCell(5,4)));
  BlockCell cell7(&(g.getCell(1,1)));
  BlockCell cell8(&(g.getCell(1,2)));

  ListeCell L1(&cell6);
  L1.fusion(L1.getHead(),& cell7);
  cout << endl;
  L1.printListe();
  L1.fusion(L1.getHead(),& cell8);
  L1.printListe();

  g.GrillePrint();
    
}


void MyProgram(int argc,char** argv){
  map<string,string> data;
  Option tabOption[5]={Option(Option::HELP,Option::AUCUN,"-h","L'aide de Jeu et affichage des options"),
		       Option(Option::DIMENSION,Option::AUCUN,"-d","determiner les dimensions dimension de la grille"),
		       Option(Option::CONFIG,Option::STRING,"-cfg","Configurer les cellules en passant un ficher de config"),
		       Option(Option::VERSION,Option::AUCUN,"-v","Version de programme"),
  		       Option(Option::AUTHORS,Option::AUCUN,"-a","auteurs de Programme")};
  if(argc==1){
    data.insert(std::pair<string,string>("dimensionX","15"));
    data.insert(std::pair<string,string>("dimensionY","15"));
    data.insert(std::pair<string,string>("numCell","3"));
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
