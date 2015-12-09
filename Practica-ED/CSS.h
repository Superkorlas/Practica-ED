/* 
 * File:   CSS.h
 * Author: superkorlas
 *
 * Created on 9 de diciembre de 2015, 18:07
 */

#ifndef CSS_H
#define	CSS_H

#include "crimen.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef float Longitud;
typedef float Latitud;
typedef unsigned int ID;
typedef string Termino;
typedef string IUCR;

class CSS
{
private:
    map<ID,crimen> baseDatos; 
//    multimap<Date, map<ID,crimen>::iterator > > DateAccess;
//    map<IUCR,set<ID> > IUCRAccess;
//    unordered_map<Termino, set<ID> > index;
//    map<Longitud,multimap<latitud, ID> > posicionGeo;

public:
    CSS();
    bool load(string nombreDB);
    void insert(const crimen & x);
    bool erase( unsigned int ID);
    
    friend ostream & operator<< (ostream & sal, const CSS & D);
    
    class iterator {
    private:
        /* @brief it  itera sobre los ID del map 
      */
        map<ID,crimen>::iterator it;
    public:
           pair<const ID, crimen > & operator*();   
    
    };
};

ostream & operator<<(ostream & sal, const CSS & D);


#include "CSS.hxx"
#endif	/* CSS_H */