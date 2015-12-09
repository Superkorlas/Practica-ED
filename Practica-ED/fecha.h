/*
 * meteorito.h
 *
 * Copyright  (C) Juan F. Huete
 */
#ifndef __FECHA_H
#define __FECHA_H

#include <string>
#include <iostream> 
#include <stdlib.h>

using namespace std;

//!Clase fecha

/*!Métodos--> fecha:: fecha(), getSec(), getMin(), getHour(), getDay(), getMon(), getYear() 

 *  Descripción

 * Esta clase contiene toda la información asociada a una fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM

Ejemplo de su uso:
\code
...
string cad1 = "01/01/2000 00:00:00 AM";
fecha date1(cad1);
string cad2 = "01/09/2015 01:00:00 AM";
fecha date2(cad2);
if(date1 <= date2)
{
        cout << "date1 menor o igual que date2" << endl;
}
else 
{
        cout << "date2 menor que date1" << endl;	
}
...
\endcode

 */

class fecha
{
public:
    /** @brief Constructor por defecto.
     */
    fecha();

    /** @brief Constructor de copia.
            @param x Conjunto a copiar.
     */
    fecha(const fecha& x);

    /** @brief Constructor a partir de un string.
            @param s Parametro con formato mm/dd/aaaa hh:mm:ss AM/PM
     */
    fecha(const string& s);

    //Getters & Setters
    /** @brief Get de la variable sec 
            @return Devuelve la variable sec
     */
    int getSec()const;

    /** @brief Get de la variable min
            @return Devuelve la variable min
     */
    int getMin()const;

    /** @brief Get de la variable hour
            @return Devuelve la variable hour
     */
    int getHour()const;

    /** @brief Get de la variable mday
            @return Devuelve la variable mday
     */
    int getDay()const;

    /** @brief Get de la variable mon
            @return Devuelve la variable mon
     */
    int getMon()const;

    /** @brief Get de la variable year
            @return Devuelve la variable year
     */
    int getYear()const;

    /** @brief Operador de asignacion.
            @param f Fecha a copiar.
            Crea una fecha duplicada exacta a f.
     */
    fecha & operator=(const fecha& f);

    /** @brief Operador de asignacion.
            @param s String a copiar.
            Crea una fecha duplicada a partir de s.
     */
    fecha & operator=(const string& s); // s es un string con el formato mm/dd/aaaa hh:mm:ss AM/PM

    /** @brief Transforma un objeto fecha a string.
            @return Un string con formato mm/dd/aaaa hh:mm:ss AM/PM.
     */
    string toString() const; //convierte la fecha a un string

    // Operadores relacionales
    /** @brief Comprueba si una fecha es igual a otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es igual, false en caso contrario.
     */
    bool operator==(const fecha& f) const;

    /** @brief Comprueba si una fecha es menor que otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es menor, false en caso contrario.
     */
    bool operator<(const fecha& f)const;

    /** @brief Comprueba si una fecha es mayor que otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es mayor, false en caso contrario.
     */
    bool operator>(const fecha& f) const;

    /** @brief Comprueba si una fecha es menor o igual que otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es menor o igual, false en caso contrario.
     */
    bool operator<=(const fecha& f)const;

    /** @brief Comprueba si una fecha es mayor o igual que otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es mayor o igual, false en caso contrario.
     */
    bool operator>=(const fecha& f) const;

    /** @brief Comprueba si una fecha es distinta a otra.
            @param f Fecha con la que compara.
            @return Devuelve true si es distinta, false en caso contrario.
     */
    bool operator!=(const fecha& f)const;

private:
    int sec; // seconds of minutes from 0 to 61
    int min; // minutes of hour from 0 to 59
    int hour; // hours of day from 0 to 24
    int mday; // day of month from 1 to 31
    int mon; // month of year from 0 to 11
    int year; // year since 2000

    friend ostream& operator<<(ostream& os, const fecha& f);
};

/* @brief imprime fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
 */
ostream& operator<<(ostream& os, const fecha& f);

#include "fecha.hxx" // Incluimos la implementacion.


#endif
