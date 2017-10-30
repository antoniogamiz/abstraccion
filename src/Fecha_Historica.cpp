#include <iostream>
#include<sstream>
#include<string>
#include "Fecha_Historica.h"

using namespace std;

//Resize simple
  void Fecha_Historica::resize(int r){
     string *aux = new string[r];
     for(int i=0; i<numeventos; ++i){
        aux[i]=str[i];
     }
     delete[] str;
     str = aux;
     reservados = r;
  }



//Constructor vacío
  Fecha_Historica::Fecha_Historica():anio(0),reservados(0),numeventos(0),str(0){}


//Constructor con parametros año, cadena de eventos y número de eventos a añadir
  Fecha_Historica::Fecha_Historica(int a, string *s, int n){
     assert(a >= 0 && a<= 9999);
     anio = a;
     string *str = new string[n];   
     for (int i=0; i<n; i++)
        str[i]=s[i];
  }

//Constructor de copia
   Fecha_Historica::Fecha_Historica(const Fecha_Historica &e){
    *this=e;
   }

   Fecha_Historica& Fecha_Historica::operator=(const Fecha_Historica &e){
      if(this != &e)
      str = new string[e.reservados];
      anio=e.anio;
      numeventos = e.numeventos;
      reservados = e.numeventos;
      for(int i=0; i<numeventos; ++i)
        str[i] = e.str[i];
       return *this;
   }


   Fecha_Historica::~Fecha_Historica(){
    anio=0;
    numeventos=0;
    reservados=0;
    delete[] str;
   }

//Método de acceso a año
   int Fecha_Historica::getAnio(){
    return anio;
   }

//Método de acceso al número de eventos acaecidos en un año
  int Fecha_Historica::getNumEventos(){
    return numeventos;
  }


//Añade un evento
  void Fecha_Historica::addEvento(string &event){
     if (numeventos == reservados){
        if (numeventos==0)
           resize(1);
        else
          resize(2*reservados);
     }
     str[numeventos]=event;
     numeventos++;
  }

  bool Fecha_Historica::estaRepetido(string evento){
    bool repetido=false;
    for(int i= 0; i< numeventos && !repetido; i++){
      if(evento.compare(str[i]) == 0)
        repetido=true;
    }
    return repetido;
  }


  //Elimina los eventos repetidos dentro de una Fecha
  string* Fecha_Historica::eliminaEventosRepetidos(){
    Fecha_Historica aux;
    aux.anio = anio;

    for(int i= 0; i< numeventos; i++){
      if(! aux.estaRepetido(str[i]))
        aux.addEvento(str[i]);
    }
    return aux.str;
  }



//Buscador de eventos
  bool Fecha_Historica::buscarEventos(string s, Fecha_Historica &matches){
     bool encontrado=false;
     for (int i=0; i < numeventos; ++i){
        if(str[i].find(s) != -1 ){
           matches.addEvento(str[i]);
           encontrado = true;
        }
     }
     if (encontrado){
        matches.anio=anio;
      }
    return encontrado;
   }

//Operador <<
  ostream& operator<< (ostream& os, const Fecha_Historica& e){
    os << e.anio;
    for(int i=0; i<e.numeventos; i++)
        os << '#' << e.str[i];
    os << endl;
    return os;
  }

//Operador >>
  istream& operator>> (istream& is, Fecha_Historica& e){
    string line; char c;
    is >> e.anio >> c;
    getline(is, line);

    int n=1;
    for(int i=0; i<line.length(); i++)
        if(line[i]=='#')
            n++;

    e.numeventos=n;
    e.reservados=e.numeventos;
    delete[] e.str;
    e.str=new string[n];

    stringstream ss(line);

    for(int i=0; i<n; i++)
        getline(ss, e.str[i], '#');
    return is;

  }
