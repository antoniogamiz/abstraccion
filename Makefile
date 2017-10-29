INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src
BIN=./bin
CXX = g++
CPPFLAGS = -Wall -g -c 

$(BIN)/pruebacronologia : $(OBJ)/pruebacronologia.o $(LIB)/libcron.a
	$(CXX) -g -o $(BIN)/pruebacronologia $(OBJ)/pruebacronologia.o -I$(INCLUDE) -L$(LIB) -lcron

$(LIB)/libcron.a : $(OBJ)/Fecha_Historica.o $(OBJ)/Cronologia.o
	ar rvs $(LIB)/libcron.a $(OBJ)/Fecha_Historica.o $(OBJ)/Cronologia.o

$(OBJ)/Fecha_Historica.o : $(SRC)/Fecha_Historica.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Fecha_Historica.o $(SRC)/Fecha_Historica.cpp -I$(INCLUDE)

$(OBJ)/Cronologia.o : $(SRC)/Cronologia.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Cronologia.o $(SRC)/Cronologia.cpp -I$(INCLUDE)

$(OBJ)/pruebacronologia.o : $(SRC)/pruebacronologia.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/pruebacronologia.o $(SRC)/pruebacronologia.cpp -I$(INCLUDE)
 #************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(BIN)/*

mrproper : clean
	-rm $(BIN)/* doc/html/*
