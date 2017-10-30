#include <iostream>
#include<sstream>
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

  void Fecha_Historica::reservarMemoria(int n){
    assert(n>0);
    reservados=n;
    string *str = new string [n];
  }

//Método que libera memoria dinámica
  void Fecha_Historica::liberarMemoria(){
    anio=numeventos=reservados=0;
    delete [] str;
  }

//Método que copia una fecha histórica
  void Fecha_Historica::copiar(string *s, int reserv, int num_events){
    assert(reserv >= num_events);
    reservarMemoria(reserv);
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
     reservarMemoria(n);
     copiar(s,n,n);
  }

//Constructor de copia
   Fecha_Historica::Fecha_Historica(const Fecha_Historica &e){
    *this=e;
   }

   Fecha_Historica& Fecha_Historica::operator=(const Fecha_Historica &e){
       if(this != &e){
         liberarMemoria();
         anio=e.anio;
         copiar(e.str,e.reservados,e.numeventos);
       }
       return *this;
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

//Dadas dos fechas históricas une sus eventos sin que haya ningún elemento repetido
    string* Fecha_Historica::unionEventos(Fecha_Historica f1, Fecha_Historica f2){
      Fecha_Historica u;

      for(int i= 0; i< f1.numeventos; i++){
        if(! u.estaRepetido(f1.str[i]))
          u.addEvento(f1.str[i]);
      }

      for(int i= 0; i< f1.numeventos; i++){
        if(! u.estaRepetido(f2.str[i]))
          u.addEvento(f2.str[i]);
      }
      return u.str;
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
    e.str=NULL;
    e.str=new string[n];

    stringstream ss(line);

    for(int i=0; i<n; i++)
        getline(ss, e.str[i], '#');
    return is;

  }

