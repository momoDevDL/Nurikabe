#ifndef __CELL_H
#define __CELL_H

class Riviere;
class Iles;

class Cell{

 private:
  int posX;
  int posY;
  int etat;
  int cellNum;
  bool dejaVu;
  Cell* ref;
  Riviere* riv;
  Iles* iles;
  
 public:
  Cell();
  Cell(int etat,int cellNum);
  Cell& operator=(const Cell &c);
  //accesseur en lecture
  int getEtat()const;
  int getCellNum()const;
  int getPosX()const;
  int getPosY()const;
  Cell* getRef()const;
  Riviere* getRiv()const;
  
  Iles* getIles()const;
  bool getDejaVu()const;


  //accesseur en ecriture
  void setEtat(int);
  void setCellNum(int);
  void setPosX(int);
  void setPosY(int);
  void setRef(Cell*);
  void setRiv(Riviere*);     
  void setDejaVu(bool);
  void setIles(Iles*);

  void print();

  bool conflit();


};
#endif
