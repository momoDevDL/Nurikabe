#include"grille.h"
#include<iostream>
#include"ListeCell.h"
#include"option.h"
using namespace std;
void MyProgram(int dimX,int dimY){
  Grille g(dimX,dimY);
  g.addVal(2,0,4);
  g.GrillePrint();
  g.addVal(6,0,2);
  g.addVal(3,2,3);
  g.GrillePrint();
  g.addEtat(1,1,2);
  g.addEtat(2,0,3);
  g.GrillePrint();
  (g.getCell(1,1)).print();

  BlockCell cell6(&(g.getCell(0,2)));
  BlockCell cell7(&(g.getCell(0,3)));
  // cell6.setEtatCell((g.getCell(0,4)).getEtat());
  ListeCell L1(&cell6);
  cout<<L1.getSize()<<endl;
  L1.addAfter(L1.getTail(),&cell7);
  //L1.addAfter(L1.getTail(),&(g.getCell(1,3)));
  // cout<<L1.getSize()<<endl;
  L1.printListe();
}

int main(int argc,char** argv){
  
  Option tabOption[5]={Option(Option::HELP,Option::AUCUN,"-h","L'aide de Jeu"),
		       Option(Option::DIMENSION,Option::ENTIER,"-d","determiner une dimension de grille"),
		       Option(Option::CONFIG,Option::STRING,"-cfg","Configurer les cellules"),
		       Option(Option::VERSION,Option::AUCUN,"-v","Version de programme"),
  		       Option(Option::AUTHORS,Option::AUCUN,"-a","auteur de Programme")};
  if(argc==1){
    MyProgram(5,5);
  }else{
    for(int i=1;i<argc;i++){
      for(int j=0;j<5;j++){
	
	if(argv[i][0]=='-'){
	  if(argv[i] == tabOption[j].getraccourci()){
	      launchOption(tabOption,tabOption[j]);
	    }
	}else{
	
	string s = ID2String(tabOption[j].getId());
	
	if(argv[i] == s ){
	  launchOption(tabOption,tabOption[j]);
	  }
	  
	}
	
      }
      
    } 
  }
}
