
/*
 * meteorito.h
 *
 * Copyright  (C) Juan F. Huete
 */
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream> 

#include "fecha.h"
//! Clase crimen

/*! Métodos--> crimen:: crimen(), setID(), setCaseNumber(), setDate(), setIucr(), setPrimaryType(), setDescription, setLocationDescription,
setArrest(), setDomestic(), setLatitude(), setLongitude(), getID(), getCaseNumber(), getDate(), getIucr(), getPrimaryType(), getDescription(),
getLocationDescription(), getArrest(), getDomestic(), getLatitude(), getLongitude()

 * Descripción 

 *Un crimen es un objeto que posee un compendio de datos relacionados con un crimen.

 *Estos datos son almacenados en variables, cada una con su set y get propio.

 *Su implementación precisa de un crimen ya creado, o de inicializar uno a uno sus valores.

Ejemplo de su uso:
\code
...
crimen cr;
cr.setID(2345);
cr.setCaseNumber(AFS3423);
//Así sucesivamente
...
\endcode
 */


class crimen
{
public:

    /** @brief Constructor por defecto.
     */
    crimen();

    /** @brief Constructor de copia.
        @param x conjunto a copiar.
     */
    crimen(const crimen& x);

    /**
     * @brief Convierte un string a crimen
     * @param cadena
     * @return 
     */
    void convertir(const string& cadena);

    /** @brief Set de la variable ID.
            @param id ID a asignar.
     */
    void setID(long int & id);

    /** @brief Set de la variable caseNumber.
            @param s String a asignar.
     */
    void setCaseNumber(const string & s);

    /** @brief Set de la variable date.
            @param d Fecha a asignar.
     */
    void setDate(const fecha & d);

    /** @brief Set de la variable iucr.
            @param i String a asignar.
     */
    void setIucr(const string & i);

    /** @brief Set de la variable primaryType.
            @param p String a asignar.
     */
    void setPrimaryType(const string & p);

    /** @brief Set de la variable description.
            @param d String a asignar.
     */
    void setDescription(const string & d);

    /** @brief Set de la variable locationDescription.
            @param l String a asignar.
     */
    void setLocationDescription(const string & l);

    /** @brief Set de la variable arrest.
            @param a Bool a asignar.
     */
    void setArrest(bool a);

    /** @brief Set de la variable domestica.
            @param d Bool a asignar.
     */
    void setDomestic(bool d);

    /** @brief Set de la variable latitude.
            @param l Double a asignar.
     */
    void setLatitude(const double & l);

    /** @brief Set de la variable longitude.
            @param l Double a asignar.
     */
    void setLongitude(const double & l);

    /** @brief Get de la variable ID.
            @return Devuelve el ID (long int).
     */
    long int getID() const;

    /** @brief Get de la variable caseNumber.
            @return Devuelve el caseNumber (string).
     */
    string getCaseNumber() const;

    /** @brief Get de la variable date.
            @return Devuelve el date (fecha).
     */
    fecha getDate() const;

    /** @brief Get de la variable iucr.
            @return Devuelve el iucr (string).
     */
    string getIucr() const;

    /** @brief Get de la variable primaryType.
            @return Devuelve el primaryType (string).
     */
    string getPrimaryType() const;

    /** @brief Get de la variable description.
            @return Devuelve el description (string).
     */
    string getDescription() const;

    /** @brief Get de la variable locationDescription.
            @return Devuelve el locationDescription (string).
     */
    string getLocationDescription() const;

    /** @brief Get de la variable arrest.
            @return Devuelve el arrest (bool).
     */
    bool getArrest() const;

    /** @brief Get de la variable domestic.
            @return Devuelve el domestic (bool).
     */
    bool getDomestic() const;

    /** @brief Get de la variable latitude.
            @return Devuelve el latitude (double).
     */
    double getLatitude() const;

    /** @brief Get de la variable longitude.
            @return Devuelve el longitude (double).
     */
    double getLongitude() const;

    /** @brief Asigna un conjunto a otro.
     */
    crimen & operator=(const crimen & x);

    /** @brief Comprueba si un crimen es igual a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si son iguales, false en caso contrario.
     */
    bool operator==(const crimen & x) const;

    /** @brief Comprueba si un crimen no es igual a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si se cumple la condición, false en caso contrario.
            @post  No se modifica el conjunto.
     */
    bool operator!=(const crimen & x) const;

    /** @brief Comprueba si un crimen es menor estricto a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si se cumple la condición, false en caso contrario.
            @post  No se modifica el conjunto.
     */
    bool operator<(const crimen & x) const;

    /** @brief Comprueba si un crimen es mayor estricto a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si se cumple la condición, false en caso contrario.
            @post  No se modifica el conjunto.
     */
    bool operator>(const crimen & x) const;

    /** @brief Comprueba si un crimen es menor o igual a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si se cumple la condición, false en caso contrario.
            @post  No se modifica el conjunto.
     */
    bool operator<=(const crimen & x) const;

    /** @brief Comprueba si un crimen es mayor o igual a otro mediante su ID
            @param x Crimen con el que compara.
            @return true si se cumple la condición, false en caso contrario.
            @post  No se modifica el conjunto.
     */
    bool operator>=(const crimen & x) const;

private:
    //Atributos 
    long int ID;
    string caseNumber;
    fecha date;
    string iucr;
    string primaryType;
    string description;
    string locationDescription;
    bool arrest;
    bool domestic;
    double latitude;
    double longitude;

    /** @brief imprime todas las entradas del conjunto
            @post  No se modifica el conjunto.
     */
    friend ostream& operator<<(ostream& os, const crimen& x);
    friend class ComparacionPorID;
    friend class ComparacionPorFecha;
    friend class ComparacionPorIUCR;
};

/***************************** FUNCTORES **********************************************/

/**@brief Comparacion con fecha decreciente
 */
class ComparacionPorFechaDecreciente
{
public:

    /**@brief sobrecarga del operador indexador
     *@param Los dos crimenes a comparar
     *@return true si cumple la condicion, falso en caso contrario
     */
    bool operator()(const crimen &a, const crimen &b)const;
    friend class crimen;
};

/**@brief Comparacion con fecha creciente
 */
class ComparacionPorFechaCreciente
{
public:

    /**@brief sobrecarga del operador indexador
     *@param Los dos crimenes a comparar
     *@return true si cumple la condicion, falso en caso contrario
     */
    bool operator()(const crimen &a, const crimen &b)const;
    friend class crimen;
};

/**@brief Comparacion con IUCR creciente
 */
class ComparacionPorIUCRCreciente
{
public:

    /**@brief sobrecarga del operador indexador
     *@param Los dos crimenes a comparar
     *@return true si cumple la condicion, falso en caso contrario
     */
    bool operator()(const crimen &a, const crimen &b)const;
    friend class crimen;
};

/**@brief Comparacion con IUCR decreciente
 */
class ComparacionPorIUCRDecreciente
{
public:

    /**@brief sobrecarga del operador indexador
     *@param Los dos crimenes a comparar
     *@return true si cumple la condicion, falso en caso contrario
     */
    bool operator()(const crimen &a, const crimen &b)const;
    friend class crimen;
};


#include "crimen.hxx"
#endif

