/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef _CRONOLOGIA_
#define _CRONOLOGIA_

#include <iostream>
#include <string>
#include "Fecha_Historica.h"

using namespace std;

/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto
  * con tres campos, dos enteros y un vector de objetos de Fecha_Historica
  * Los dos enteros son utilizados para trabajar
  * con el vector dinámicamente. Lo representamos como
  *
  * Año_1 a.C/d.C N_eventos evento/s:
  * *)Fecha_Historica_1
  * ...
  * *)Fecha_Historica_N
  * .
  * .
  * .
  * Año_N a.C/d.C N_eventos evento/s:
  * *)Fecha_Historica_1
  * ...
  * *)Fecha_Historica_M
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author
  * @author
  * @date
  */

class Cronologia {

 private:
/**
  * @page repConjunto Rep del TDA Cronologia
  *
  * @section invConjunto Invariante de la representación
  *
  * El invariante está ligado al de los Eventos_Historicos \e rep.anio < 0 && rep.anio > 9999
  * que ya hemos fijado anteriormente
  *
  * @section faConjunto Función de abstracción
  *
  * Un objeto válido @e rep del TDA Cronologia representa al valor
  *
  * Año_1 a.C/d.C N_eventos evento/s:
  * *)Fecha_Historica_1
  * ...
  * *)Fecha_Historica_N
  * .
  * .
  * .
  * Año_N a.C/d.C N_eventos evento/s:
  * *)Fecha_Historica_1
  * ...
  * *)Fecha_Historica_M
  *
  */

  int neventos;               /**< número objetos Fecha_Historica almacenados */
  int reservados;             /**< número de elementos reservados, */
  Fecha_Historica *event;    /**< vector de Eventos Historicos */

  void resize(int r);         /**< Función privada para mantener el vector dinámico de string */
  void ordenar();             /**< Función privada para ordener los eventos según la fecha */


 public:

/**
  * @brief Constructor por defecto de la clase. Lo creamos sencillamente para evitar
  * errores o asignaciones de basura a objetos de nuestra clase. Crea una Cronologia
  * por defecto con año 0, con el vector nulo y 0 anios y reservados
  */

  Cronologia();

/**
  * @brief Constructor de la clase
  * @param eh vector de Fecha_Historica
  * @param n número de objetos Fecha_Historica que contienen el vector eh que se pasa como parámetro
  * @return Crea el evento con n Fecha_Historica asociados
  * @pre n debe ser un número positivo igual al número de objetos contenidos en el vector eh
  */

  Cronologia(Fecha_Historica *eh, int n);

/**
  * @brief Constructor de copias de la clase
  * @param c objeto de la clase que se quiere copiar
  * @return Crea el evento con los datos de c
  */

  Cronologia(const Cronologia& c);

  /**
    * @brief Operador de asignación de la clase
    * @param c objeto de la clase que se quiere copiar
    * @return Crea el evento con los datos de c
    */

  Cronologia& operator=(const Cronologia& c);

/**
  * @brief Destructor de la clase. Hace un delete del vector de Fecha_Historica
  */

  ~Cronologia();

/**
  * @brief Añade un Evento Histórico  en la Cronología
  * @param eh el nuevo Evento Historico
  * @pre la posición
  * @return no devuelve nada
  */

  void addEvento(Fecha_Historica& eh);


  /**
  * @brief Busca si un evento está repetido en la Cronología.
  * @param evento evento que queremos saber si aparece más de una vez o no
  * @return Devuelve true si está repetido, false si no lo está
  */

  bool estaRepetido(string evento);


  /**
  * @brief Dadas dos cronologías las une en otra
  * @param c cronología que se va a unir a la que invoca a la función
  * @param u cronología resultante de unirlas
  */

  void unionCronologias(const Cronologia& c, Cronologia& u);



  /**
    * @brief Devuelve los eventos ocurridos en un año
    * @param a año del que se quieren saber los eventos
    * @return string* vector de string con los eventos
    */

    Fecha_Historica getEventos(int a);


/**
  * @brief Busca un Evento Histórico dado su fecha
  * @param f la fecha del evento a buscar
  * @pre la fecha debe ser válida
  * @return Devuelve la posición del evento
  */

  int buscarAnio(int f);


  /**
  * @brief Busca si un año está repetido en la Cronología
  * @param anio año que queremos saber si aparece más de una vez o no
  * @return Devuelve true si está repetido, false si no lo está
  */

  bool estaRepetido(int anio);



  /**
  * @brief buscador de eventos dado una palabra clave
  * @param s vector de string con la palabra a buscar
  * @return Devuelve una Cronología
  */

  Cronologia buscarEventos(string s);

  /**
  * @brief Busca el año que mayor número de eventos ha tenido
  * @return Año con con mayor número de eventos
  */

  int maxNumEvents();



  /**
  * @brief Busca el año que menor número de eventos ha tenido
  * @return Año con con menor número de eventos
  */

  int minNumEvents();


/**
  * @brief Salida de una Cronologia a ostream
  * @param os stream de salida
  * @param c Cronologia a escribir
  * @post Se obtienen varios años seguidos de la cadena de Eventos_Historico con el formato
  * de Fecha_Historica
  */

  friend ostream& operator<< (ostream& os, const Cronologia& c);

/**
  * @brief Entrada de una Cronologia desde istream
  * @param is stream de entrada
  * @param c Cronologia que recibe el valor
  * @retval La Cronologia leída en c
  * @pre La entrada tiene el formato de Fecha_Historica neventos numero de veces
  */

  friend istream& operator>> (istream& is, Cronologia& c);

};

#endif
