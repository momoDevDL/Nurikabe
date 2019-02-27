CXX=g++ -std=c++11
CXX_FLAGS= -ansi -Wall -pedantic -g

SOURCE=   ListeCell.cpp  Iles.cpp  cell.cpp BlockCell.cpp  Riviere.cpp   grille.cpp option.cpp prog.cpp GlobalRiviere.cpp main.cpp

PROG=Nurikabe

MSG_OK = @ echo "\t\t\t........................OK"

.SUFFIXES : .cpp .h .o

all : $(PROG)

.cpp.o :
	$(CXX) -c $(CXX_FLAGS) $<
	$(MSG_OK)

$(PROG) : $(SOURCE:.cpp=.o)
	$(CXX) $^ $(CXX_FLAGS) -o $(PROG) 
	$(MSG_OK)
clear :
	rm $(SOURCE:.cpp=.o)



