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

  void Fecha_Historica::liberarMemoria(){
    anio=numeventos=reservados=0;
    delete[] str;
  }

  void Fecha_Historica::reservarMemoria(int n){
    if(n<0)
      reservados=0;
    else
      reservados=n;

    str= new string [reservados];
  }

  void Fecha_Historica::copiar(string *s, int num_events, int _reservados){
    assert(num_events<=_reservados);
    numeventos=num_events;

    reservarMemoria(_reservados);

    for(int i= 0; i<numeventos; i++)
      str[i]= s[i];
  }

//Constructor vacío
  Fecha_Historica::Fecha_Historica():anio(0),reservados(0),numeventos(0),str(0){}


//Constructor con parametros año, cadena de eventos y número de eventos a añadir
  Fecha_Historica::Fecha_Historica(int a, string *s, int n){
     assert(a >= 0 && a<= 9999);
     liberarMemoria();
     anio = a;
     copiar(s, n, n);
  }

//Constructor de copia
   Fecha_Historica::Fecha_Historica(const Fecha_Historica &e){
    *this=e;
   }

//Operador de asignación
   Fecha_Historica& Fecha_Historica::operator=(const Fecha_Historica &e){
      if(this != &e){
        anio=e.anio;
        copiar(e.str, e.numeventos, e.reservados);
      }
       return *this;
   }

//Destructor
   Fecha_Historica::~Fecha_Historica(){
    liberarMemoria();
   }

//Método de acceso a año
   int Fecha_Historica::getAnio(){
    return anio;
   }

//Establecemos año como un valor pasado como parámetro
   void Fecha_Historica::setAnio(int a){
    assert(a>=0 && a<= 9999);
     anio=a;
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

//Dado un evento busca si está en los de la fecha histórica
  bool Fecha_Historica::estaRepetido(string evento){
    bool repetido=false;
    for(int i= 0; i< numeventos && !repetido; i++){
      if(evento.compare(str[i]) == 0)
        repetido=true;
    }
    return repetido;
  }

//Método de acceso a los eventos ocurridos en la Fecha_Historica
  string* Fecha_Historica::getEventos(){
    return str;
  }

//Dadas dos fechas históricas crea otra con la unión ordenada y sin eventos repetidos de ambas
  void Fecha_Historica::unionEventos(const Fecha_Historica &f1, const Fecha_Historica &f2, Fecha_Historica &u ){
    for(int i= 0; i< f1.numeventos; i++){
      if(! u.estaRepetido(f1.str[i]))
        u.addEvento(f1.str[i]);
    }

    for(int i= 0; i< f2.numeventos; i++){
      if(! u.estaRepetido(f2.str[i]))
        u.addEvento(f2.str[i]);
    }
  }

//Dadas dos fechas históricas crea una con los eventos que ambas tienen en común
void Fecha_Historica::interseccionEventos(Fecha_Historica f, Fecha_Historica &i){
    if(numeventos < f.numeventos){
      for(int j= 0; j< numeventos; j++){
        if(f.estaRepetido(str[j]) && ! i.estaRepetido(str[j]))
          i.addEvento(str[j]);
      }
    }
    else{
      for(int j= 0; j< f.numeventos; j++){
        if(estaRepetido(f.str[j]) && ! i.estaRepetido(f.str[j]))
          i.addEvento(f.str[j]);
      }
    }
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
