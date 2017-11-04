#include <iostream>
#include "Cronologia.h"
#include "Fecha_Historica.h"

using namespace std;

//Resize
  void Cronologia::resize(int r){
     if(r>reservados){
     Fecha_Historica *aux = new Fecha_Historica[r];
     for (int i=0; i<neventos; i++)
        aux[i]=event[i];
     delete[] event;
     event = aux;
     reservados=r;
     }
  }

//Ordena
  void Cronologia::ordenar(){
     for (int i=neventos-1; i>0; --i)
      for (int j=0; j<i; ++j)
         if (event[j].getAnio() > event[j+1].getAnio()) {
            Fecha_Historica aux;
            aux = event[j];
            event[j] = event[j+1];
            event[j+1]= aux;
         }
  }

  void Cronologia::liberarMemoria(){
    neventos=reservados=0;
    delete [] event;
  }

  void Cronologia::reservarMemoria(int numero){
    if(numero>0){
      reservados=numero;
      Fecha_Historica *event = new Fecha_Historica [numero];
    }
    else
      reservados=0;
  }

  void Cronologia::copiar(Fecha_Historica *f, int reserv, int eventos){
    liberarMemoria();
    reservarMemoria(reserv);
    neventos=eventos;
    for(int i= 0; i< eventos; i++)
      event[i]=f[i];
  }

//Construye una cronología dadas una fecha y un número
  Cronologia::Cronologia(Fecha_Historica *eh, int n){
    copiar(eh, n, n);
 }

//Constructor vacío
  Cronologia::Cronologia():reservados(0),neventos(0),event(0){}


//Constructor de copia
   Cronologia::Cronologia(const Cronologia& c){
    *this=c;
   }

//Operador de asignación
  Cronologia& Cronologia::operator=(const Cronologia& c){
    if(this != &c)
      copiar(c.event, c.reservados, c.neventos);

    return *this;
  }

//Destructor
  Cronologia::~Cronologia(){
    liberarMemoria();
  }

//Añade objeto de Fecha_Historica
  void Cronologia::addEvento(Fecha_Historica& eh){
     if (neventos == reservados){
        if (neventos==0)
           resize(1);
        else
           resize(2*reservados);
     }
     event[neventos]=eh;
     neventos++;
     ordenar();
  }

//Mira si un evento está en la cronología
  bool Cronologia::estaRepetido(string evento){
    bool repetida=false;
    for(int i=0; i<neventos && !repetida; i++)
      repetida=event[i].estaRepetido(evento);
    return repetida;
  }

  //Dado un año devolvemos los eventos que se dieron en él
    Fecha_Historica Cronologia::getEventos(int a){
      int posicion_anio = buscarAnio(a);
      if(posicion_anio != -1)
        return event[posicion_anio];
      else{
        Fecha_Historica vacia;
        return vacia;
      }
      }


//Busca un año en la Cronología y devuelve si dicho año está en la cronología o no.
  int Cronologia::buscarAnio(int f){
     int i=0;
     bool valido=false;
     while(i<neventos && !valido){
        if(event[i].getAnio()==f)
           valido = true;
        else
           ++i;
     }
     if(!valido)
        i=-1;
     return i;
  }

//Devuelve el año en el que ha habido un mayor número de eventos
  int Cronologia::maxNumEvents(){
    int max= event[0].getNumEventos();
    int anio_max= event[0].getAnio();

    for(int i=1; i< neventos; i++){
      if(event[i].getNumEventos() > max){
        max= event[i].getNumEventos();
        anio_max= event[i].getAnio();
      }
    }
    return anio_max;
  }

//Devuelve la unión ordenada de dos cronologías, sin elementos repetidos
  void Cronologia::unionCronologias(const Cronologia& c, Cronologia& u){
    int i=0, j=0;
    while(i< neventos && j< c.neventos){
      if(event[i].getAnio() < c.event[j].getAnio()){
        u.addEvento(event[i]);
        i++;
      }

      if(event[i].getAnio() > c.event[j].getAnio()){
        u.addEvento(c.event[j]);
        j++;
      }

      if(event[i].getAnio() == c.event[j].getAnio()){
        Fecha_Historica aux;

        aux.setAnio(event[i].getAnio());
        aux.unionEventos(event[i], c.event[j], aux);
        u.addEvento(aux);
        i++;
        j++;
      }
    }

    while(j< c.neventos){
      u.addEvento(c.event[j]);
      j++;
    }

    while(i< neventos){
      u.addEvento(event[i]);
      i++;
    }
  }

//Dadas dos cronologías crea una con los elementos (años y dentro de estos los eventos) que están en ambas
  void Cronologia::interseccionCronologias(Cronologia &c, Cronologia &i){
      int k= 0, j= 0;

      ordenar();
      c.ordenar();

      while(k< neventos && j< c.neventos){
        if(event[k].getAnio() == c.event[j].getAnio()){
          Fecha_Historica aux;
          event[k].interseccionEventos(c.event[j], aux);
          aux.setAnio(event[k].getAnio());
          i.addEvento(aux);
          k++;
          j++;
        }
        else if(event[k].getAnio() < c.event[j].getAnio())
          k++;

        else
          j++;
      }
    }

  //Devuelve el año en el que ha habido un menor número de eventos
    int Cronologia::minNumEvents(){
      int min= event[0].getNumEventos();
      int anio_min= event[0].getAnio();

      for(int i=1; i< neventos; i++){
        if(event[i].getNumEventos() < min){
          min= event[i].getNumEventos();
          anio_min= event[i].getAnio();
        }
      }
      return anio_min;
    }

//Devuelve si un año está o no dentro de la Cronología
  bool Cronologia::estaRepetido(int anio){
    bool repetido= false;

    for(int i= 0; i< neventos && !repetido; i++){
      if(event[i].getAnio() == anio)
        repetido= true;

    }
    return repetido;
  }

//Busca un evento en la Cronología y devuelve su posición en el vector
  Cronologia Cronologia::buscarEventos(string s){
     Cronologia nuevo;
     for (int i=0; i < neventos; ++i){
        Fecha_Historica aux;
        if(event[i].buscarEventos(s,aux)){
           nuevo.addEvento(aux);
        }
     }
     nuevo.ordenar();
     return nuevo;
   }

 //Buscar eventos que sucedieron entre dos años
   Cronologia Cronologia::buscarEventoEntre(int anio1,int anio2){
    Cronologia nuevo;
    for(int i=buscarAnio(anio1);i<buscarAnio(anio2)+1;i++){
      nuevo.addEvento(event[i]);
    }

    return nuevo;
  }

//Operador <<
  ostream& operator<< (ostream& os, const Cronologia& c){
     for(int i=0; i<c.neventos; i++)
        os << c.event[i];
     return os;
  }

//Operador >>
  istream& operator>> (istream& is, Cronologia& c){
     Fecha_Historica b;
     while(is >> b){
        c.addEvento(b);
     }
     return is;
}
