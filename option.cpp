#include<iostream>
#include"option.h"
void MyProgram(int,int);
using namespace std;

//les constructeurs de terrain par defaut et paramétré
Option::Option():id(Option::NONE),type(AUCUN),raccourci(""),description("UNKNOWN"){}
Option::Option(Ido identifiant,Type t,string racc,string descr):id(identifiant),type(t),raccourci(racc),description(descr){}

Option& Option::operator=(const Option &opt){
  if(this != &opt){
  description = opt.getdescription();
  id = opt.getId();
  type = opt.getType();
  raccourci = opt.getraccourci();
  }
  return *this;
  
}
//accesseur en lecture 
Option::Ido Option::getId()const{
  return id;
}

string  Option::getraccourci()const{
  return raccourci;
}
string  Option::getdescription()const{
  return description;
}
Option::Type Option::getType()const{
  return type;
}

  //accesseurs en ecriture
void Option::setId(Option::Ido ID){
  id=ID;
}

void Option::setRaccourci(const string &r){
  raccourci=r;
}
void Option::setDescription(const string &d){
  description=d;
}
void Option::setType(Type t){
  type=t;
}

  //afficher l'option
void Option::print()const{
  cout<<ID2String(id)<<": ( "<<raccourci<<" ) "<<Type2String(type)<<" :"<<endl;
  cout<<"----Description----"<<endl;
  cout<<description<<endl;
  cout<<"/=--------------------=/"<<endl;
}


//transformer mon type en string
string Type2String(Option::Type t){
  string type;
  switch(t){
  case Option::ENTIER:
    type="<ENTIER>"; break;
  case Option::CHARACTER:
    type="<CHARACTER>"; break;
  case Option::AUCUN:
    type="<AUCUN>"; break;
  case Option::STRING:
    type="<STRING>"; break; 
  }
  return type;
}

//transformer mon id en
string ID2String(const Option::Ido Id){
  string ID;
  switch(Id){
  case Option::HELP:
    ID="HELP"; break;
  case Option::VERSION:
    ID="VERSION"; break;
  case Option::AUTHORS:
    ID="AUTHORS"; break;
  case Option::DIMENSION :
    ID="DIMENSION"; break;
  case Option::CONFIG :
    ID="CONFIG"; break;
  case Option::NONE:
    ID="UKNOWN"; break; 
  }
  return ID;
}

void launchHelp(Option* tab){
  int i=4;
  while(i>0){
    tab[i].print();
    i--;
  }
}
void launchVersion(Option &o){
  cout<<o.getdescription()<<endl;
  cout<<"\033[01;31;5mVERSION 1.0 \033[0m"<<endl;
}

void launchAuthors(Option &o){
  cout<<o.getdescription()<<endl;
  cout<<"==============\033[01;31;5mAUTHORS\033[0m========="<<endl;
  cout<<"-> \033[1;33mMohamed Masbah Abou Laich\033[0m"<<endl;
  cout<<"-> \033[1;33mAntoine Afflatet\033[0m "<<endl;
  cout<<"-> \033[1;33mAntoine Brahimi\033[0m"<<endl;
  cout<<"-> \033[1;33mAyoub Benhamdi\033[0m"<<endl;
}

int launchDimensionX(Option &o){
  int dimX;
  cout<<o.getdescription()<<endl;
  cout<<"Veuillez saisir la dimension X de la grille souhaitée : "<<endl;
  cin>>dimX;
  return dimX;
}

int launchDimensionY(){
  int dimY;
  cout<<"Veuillez saisir la dimension Y de la grille souhaitée : "<<endl;
  cin>>dimY;
  return dimY;
}

void launchOption(Option* tab,Option &o){
  int dimensionX;
  int dimensionY;
  switch(o.getId()){
    
  case Option::HELP:
    launchHelp(tab);
    break;
  case Option::VERSION:
    launchVersion(o);
    break;
  case Option::AUTHORS:
    launchAuthors(o);
    break;
  case Option::DIMENSION:
     dimensionX=launchDimensionX(o);
     dimensionY=launchDimensionY();
     MyProgram(dimensionX,dimensionY);
    break;
  case Option::CONFIG:
    cout<<"veuilleiz entrer votre config"<<endl;
    break;
  case Option::NONE:
    break;
  }
  
}
