///////////////////////////////////////////////////////////////////////
//
// PRACTICA 2 DE ESTRUCTURA DE DATOS.
//
// AUTORES: ELENA MERELO MOLINA Y ANTONI GAMIZ DELGADO.
//
///////////////////////////////////////////////////////////////////////
#include "Cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){

  if (argc!=3){
      cout<<"Dime el nombre de dos ficheros que contengan cronologías" <<endl;
      return 0;
   }

  //Leemos la primera cronología.
   ifstream f (argv[1]);
   if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }
   Cronologia cron1;
   f >> cron1;

   //Leemos la segunda cronología.
   ifstream ff (argv[2]);
   if (!ff){
    cout<<"No puedo abrir el fichero "<<argv[2]<<endl;
    return 0;
   }
   Cronologia cron2;
   ff >> cron2;
  

   //Mostramos las cronoogías leídas.
   cout << "Primera cronología leida del archivo: " << endl << cron1 << endl;
   cout << "Segunda cronología leida del archivo: " << endl << cron2 << endl;

   //Comprobamos el funcionamiento de Fecha_Historica::estaRepetido;
   string evento;
   cout << "Introduzca un evento para comprobar si está en alguna de las cronologías:" << endl;
   cin >> evento;
   if(cron1.estaRepetido(evento))
    cout << "Este evento se encuentra en la primera cronología." << endl;
  else
    cout << "Este evento no se encuentra en la primera cronología." << endl;
  
  if(cron2.estaRepetido(evento))
    cout << "Este evento se encuentra en la segunda cronología." << endl;
  else
    cout << "Este evento no se encuentra en la segunda cronología." << endl;


}
