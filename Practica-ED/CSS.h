/* 
 * File:   CSS.h
 * Author: superkorlas
 *
 * Created on 9 de diciembre de 2015, 18:07
 */

#ifndef CSS_H
#define	CSS_H

#include "crimen.h"
#include "fecha.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "assert.h"
#include <map>
#include <unordered_map>
#include <set>
#include <list>

using namespace std;

typedef float Longitud;
typedef float Latitud;
typedef unsigned int ID;
typedef string Termino;
typedef string IUCR;

class CSS
{
private:
    map<ID, crimen> baseDatos;
    multimap<fecha, map<ID,crimen>::iterator > DateAccess;
    map<IUCR,set<ID> > IUCRAccess;
    unordered_map<Termino, set<ID> > index;
    map<Longitud,multimap<Latitud, ID> > posicionGeo;
    
    friend class iterator;
    friend class IUCR_iterator;
    friend class Date_iterator;

public:
    class iterator;
    class IUCR_iterator;
    class Date_iterator;

    CSS();
    bool load(string nombreDB);
    void insert(const crimen & x);
    bool erase(unsigned int ID);
    iterator find_ID(const unsigned int ID);
    void setArrest(const unsigned int ID, bool value);
//    vector<pair<ID,float> > Query(list<string> & q, int k);    
    list<ID> inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2 );
    
    /* Métodos relacionados con los iteradores */
    IUCR_iterator ibegin();
    IUCR_iterator iend();
    
    IUCR_iterator lower_bound(IUCR aux);
    IUCR_iterator upper_bound(IUCR aux);
    
    Date_iterator dbegin();
    Date_iterator dend();
    
    Date_iterator lower_bound(fecha aux);
    Date_iterator upper_bound(fecha aux);
    
    iterator begin();
    iterator end();

    friend ostream & operator<<(ostream & sal, const CSS & D);

    class iterator
    {
    private:
        /* @brief it  itera sobre los ID del map 
         */
        map<ID, crimen>::iterator it;

        friend class CSS;
    public:
        pair<const ID, crimen > & operator*();
        iterator();

    };

    class IUCR_iterator
    {
    private:
        /* @brief it_m itera sobre los IUCR del map 
         */
        map<IUCR, set<ID> >::iterator it_m;
        /* @brief it_s itera sobre los ID del set 
         */
        set<ID>::iterator it_s;
        
        friend class CSS;
    public:
        pair<const ID, crimen > & operator*();
        IUCR_iterator & operator++();
        IUCR_iterator operator++(int);
        CSS* ptr;
        IUCR_iterator();
    };

    class Date_iterator
    {
    private:
        multimap<fecha, map<ID, crimen>::iterator >::iterator it_mm;
        
        friend class CSS;
    public:
        pair<const ID, crimen > & operator*();
        Date_iterator();

    };
};

ostream & operator<<(ostream & sal, const CSS & D);


#include "CSS.hxx"
#endif	/* CSS_H */