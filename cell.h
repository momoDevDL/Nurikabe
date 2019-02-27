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
  Cell* ref;
  Riviere* riv;
  Iles* ile;
 public:
  Cell();
  Cell(int etat,int cellNum);
  //accesseur en lecture
  int getEtat()const;
  int getCellNum()const;
  int getPosX()const;
  int getPosY()const;
  Cell* getRef();
  Riviere* getRiv();
  Iles* getIle();

  //accesseur en ecriture
  void setEtat(int);
  void setCellNum(int);
  void setPosX(int);
  void setPosY(int);
  void setRef(Cell*);
  void setRiv(Riviere*);
  void setIle(Iles*);
  void print();

  bool conflit();


};
#endif
