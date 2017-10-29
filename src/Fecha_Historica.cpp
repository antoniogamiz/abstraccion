#include <iostream>
#include<sstream>
#include "Fecha_Historica.h"

using namespace std;

//Resize simple
  void Fecha_Historica::Resize(int r){
     string *aux = new string[r];
     for(int i=0; i<numeventos; ++i){
        aux[i]=str[i];
     }
     delete[] str;
     str = aux;
     reservados = r;
  }

  void Fecha_Historica::ReservarMemoria(int n){
    assert(n>0);
    reservados=n;
    string *str = new string [n];
  }

  void Fecha_Historica::LiberarMemoria(){
    anio=numeventos=reservados=0;
    delete [] str;
  }

  void Fecha_Historica::Copiar(string *s, int reserv, int num_events){
    assert(reserv >= num_events);
    ReservarMemoria(reserv);
    numeventos=num_events;
    for(int i=0; i<num_events; i++)
      str[i]=s[i];
  }

//Constructor vacío
  Fecha_Historica::Fecha_Historica():anio(0),reservados(0),numeventos(0),str(0){}


//Constructor con parametros año, cadena de eventos y número de eventos a añadir
  Fecha_Historica::Fecha_Historica(int a, string *s, int n){
     assert(a >= 0 && a<= 9999);
     anio = a;
     ReservarMemoria(n);
     Copiar(s,n,n);
  }

//Constructor de copia
   Fecha_Historica::Fecha_Historica(const Fecha_Historica &e){
    *this=e;
   }

   Fecha_Historica& Fecha_Historica::operator=(const Fecha_Historica &e){
       if(this != &e){
         LiberarMemoria();
         anio=e.anio;
         Copiar(e.str,e.reservados,e.numeventos);
       }
       return *this;
   }


//Método de acceso a año
   int Fecha_Historica::GetAnio(){
    return anio;
   }


//Añade un evento
  void Fecha_Historica::AddEvento(string &event){
     if (numeventos == reservados){
        if (numeventos==0)
           Resize(1);
        else
        Resize(2*reservados);
     }
     str[numeventos]=event;
     numeventos++;
  }


//Buscador de eventos
  bool Fecha_Historica::buscarEventos(string s, Fecha_Historica &matches){
     bool encontrado=false;
     for (int i=0; i < numeventos; ++i){
        if(str[i].find(s) != -1 ){
           matches.AddEvento(str[i]);
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
    e.str=NULL;
    e.str=new string[n];

    stringstream ss(line);

    for(int i=0; i<n; i++)
        getline(ss, e.str[i], '#');
    return is;

  }
