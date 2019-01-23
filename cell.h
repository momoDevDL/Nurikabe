#ifndef __CELL_H
#define __CELL_H

class Cell{

 private:
  int etat;
  int cellNum;
 public:
  Cell();
  Cell(int etat,int cellNum);
  //accesseur en lecture
  int getEtat()const;
  int getCellNum()const;

  //accesseur en ecriture
  void setEtat(int);
  void setCellNum(int);
  void print();

  bool conflit();


};
#endif
