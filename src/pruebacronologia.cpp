///////////////////////////////////////////////////////////////////////
//
// PRÁCTICA 2 DE ESTRUCTURA DE DATOS.
//
// AUTORES: ELENA MERELO MOLINA Y ANTONIO GÁMIZ DELGADO.
//
///////////////////////////////////////////////////////////////////////
#include "Cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
/////////////////////////////////////////////////////////////////////////////////////////

//Comprobamos que el número de argumentos se correcto.
  if (argc!=3){
    cout<<"Dime el nombre de dos ficheros que contengan cronologías" <<endl;
    return 0;
  }

/////////////////////////////////////////////////////////////////////////////////////////

//Leemos la primera cronología.

  ifstream f (argv[1]);
   if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }
   Cronologia cron1;
   f >> cron1;

/////////////////////////////////////////////////////////////////////////////////////////

//Leemos la segunda cronología.

  ifstream ff (argv[2]);
  if (!ff){
    cout<<"No puedo abrir el fichero "<<argv[2]<<endl;
    return 0;
  }

  Cronologia cron2;
  ff >> cron2;

/////////////////////////////////////////////////////////////////////////////////////////

   //Mostramos las cronoogías leídas.

   cout << "Primera cronología leida del archivo: " << endl << cron1 << endl;
   cout << "Segunda cronología leida del archivo: " << endl << cron2 << endl;

/////////////////////////////////////////////////////////////////////////////////////////

   //Comprobamos el funcionamiento de Fecha_Historica::estaRepetido;

   string evento;
   cout << "Introduzca un evento para comprobar si está en alguna de las cronologías:" << endl;
   getline(cin, evento);
   if(cron1.estaRepetido(evento))
    cout << "Este evento se encuentra en "<< argv[1] << "." << endl;
  else
    cout << "Este evento no se encuentra en "<< argv[1] << "." << endl;
  if(cron2.estaRepetido(evento))
    cout << "Este evento se encuentra en "<< argv[2] << "." << endl;
  else
    cout << "Este evento no se encuentra en "<< argv[2] << "." << endl;

/////////////////////////////////////////////////////////////////////////////////////////

   //Probamos la funcion Cronologia::buscarEventoEntre(int anio1, int anio2);

   cout << "Introduzca dos años entre los que quiere ver los eventos de la cronología 1: " << endl;
   int anio1=0; int anio2=0;
   cin >> anio1 >> anio2;
   Cronologia buscar = cron1.buscarEventoEntre(anio1,anio2);
   cout << "Los eventos entre los años " << anio1 << " y " << anio2 << " son: " << endl << buscar << endl;

/////////////////////////////////////////////////////////////////////////////////////////

  //Unimos las dos cronologías y mostramos por pantalla el resultado.

  Cronologia u;

  cron1.unionCronologias(cron2, u);

  cout << "Cronología resultante de unir: " << argv[1] << " con " << argv[2] << " :" << endl << u << endl;

/////////////////////////////////////////////////////////////////////////////////////////

  //Intersectamos las dos cronologías y mostramos por pantalla el resultado.

  Cronologia interHard;
  cron1.interseccionCronologiasHard(cron2, interHard);

  cout << "Cronología resultante de intersectar totalmente: " << argv[1] << " con " << argv[2] << " :" << endl << interHard << endl;

  Cronologia interSoft;
  cron1.interseccionCronologiasSoft(cron2, interSoft);

  cout << "Cronología resultante de intersectar: " << argv[1] << " con " << argv[2] << " :" << endl << interSoft << endl;
/////////////////////////////////////////////////////////////////////////////////////////
//Probamos que funciona getEventos()
  int a;
  cout << "Introduzca un año de la cronología del que quiera saber los eventos: " << endl;
  cin >> a;
  if(cron1.estaRepetido(a))
    cout << "Eventos de la cronología 1 ocurridos en ese año: " << cron1.getEventos(a);

  if(cron2.estaRepetido(a))
    cout << "Eventos de la cronología 2 ocurridos en ese año: " << cron2.getEventos(a);

/////////////////////////////////////////////////////////////////////////////////////////

   //Probamos las funciones Cronologia::maxNumEvents y Cronologia::minNumEvents.

  cout << "El máximo número de eventos de " << argv[1] << "tuvo lugar en el año: " << cron1.maxNumEvents() << endl;
  cout << "El máximo número de eventos de " << argv[2] << "tuvo lugar en el año: " << cron2.maxNumEvents() << endl;

  cout << "El mínimo número de eventos de " << argv[1] << " tuvo lugar en el año: " << cron1.minNumEvents() << endl;
  cout << "El mínimo número de eventos de " << argv[2] << " tuvo lugar en el año: " << cron2.minNumEvents() << endl;

/////////////////////////////////////////////////////////////////////////////////////////
}
