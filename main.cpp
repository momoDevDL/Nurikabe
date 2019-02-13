#include"grille.h"
#include<iostream>
#include"ListeCell.h"
#include"option.h"
using namespace std;


void Myprogram(int dimX,int dimY){
  Grille g(dimX,dimY);
  g.addVal(2,0,4);
  g.GrillePrint();
  g.addVal(6,0,2);
  g.addVal(3,2,3);
  g.GrillePrint();
  g.addEtat(1,1,2);
  g.addEtat(1,1,1);
  g.addEtat(2,0,3);
  g.GrillePrint();
  cout<<endl;
  
  BlockCell cell6(&(g.getCell(0,2)));
  BlockCell cell7(&(g.getCell(1,1)));
  BlockCell cell8(&(g.getCell(1,2)));
  
  ListeCell L1(&cell6);
  
  L1.fusion(L1.getHead(),& cell7);
  L1.printListe();
  L1.fusion(L1.getHead(),& cell8);
  L1.printListe();
}

void MyProgram(int argc,char** argv){
   
  Option tabOption[5]={Option(Option::HELP,Option::AUCUN,"-h","L'aide de Jeu et affichage des options"),
		       Option(Option::DIMENSION,Option::AUCUN,"-d","determiner les dimensions dimension de la grille"),
		       Option(Option::CONFIG,Option::STRING,"-cfg","Configurer les cellules en passant un ficher de config"),
		       Option(Option::VERSION,Option::AUCUN,"-v","Version de programme"),
  		       Option(Option::AUTHORS,Option::AUCUN,"-a","auteurs de Programme")};
  if(argc==1){
    Myprogram(15,25);
  }else{
    for(int i=1;i<argc;i++){
      for(int j=0;j<5;j++){
	
	if(argv[i][0]=='-'){
	  if(argv[i] == tabOption[j].getraccourci()){
	    launchOption(tabOption,tabOption[j],i,argv);
	  }
	}else{
	  
	  string s = ID2String(tabOption[j].getId());
	  
	  if(argv[i] == s ){
	    launchOption(tabOption,tabOption[j],i,argv);
	  }
	  
	}
	
      }
      
    } 
  }
}

/*int findDimensionX(istream read){
  string s;
  getline(read,s,":");
  if(atoi(read.peek())){
    return atoi(read.peek());
  }else{
    cout<<"mode de config erroné veuillez resaisir la dimension sans espace juste apres les ':'"<<endl;
    terminate():
  }
  
}

int findDimensionY(istream read){
 
  if(atoi(read.peek())){
    return atoi(read.peek());
  }else{
    cout<<"mode de config erroné veuillez resaisir la dimension sans espace juste apres les ':'"<<endl;
    terminate():
  }
  
  }*/

/*void MyProgram(string fichier){
  istream read("fichier");
  if(!read.is_open()){
    cout<<"Erreur d'ouverture de flux"<<endl;
  }else{
    MyProgram(findDimensionX(),findDimensionY());
    getline(read);
    while(getline(read)){
      read.ignore(8,"(");
      atoi(read.peek())
    }
  }
	       
 
  }*/

int main(int argc,char** argv){
  MyProgram(argc,argv);
  return 0;
}
