/* 
 * File:   CSS.hxx
 * Author: superkorlas
 *
 * Created on 9 de diciembre de 2015, 18:07
 */

#ifndef CSS_HXX
#define	CSS_HXX

#include "CSS.h"

CSS::CSS()
{

}

bool CSS::load(string nombreDB)
{
    ifstream fe;
    string cadena;
    int contador = 0;

    cout << "Abrimos " << nombreDB << endl;
    fe.open(nombreDB.c_str(), ifstream::in);

    if (fe.fail())
    {
        cerr << "Error al abrir el fichero " << nombreDB << endl;
    }
    else
    {
        getline(fe, cadena, '\n'); //leo la cabecera del fichero
        cout << cadena << endl;
        while (/*!fe.eof()*/contador < 10)
        {
            getline(fe, cadena, '\n');
            if (!fe.eof())
            {
                // Convertir cadena a crimen
                // crimen aux = cadena;
                crimen aux;
                aux.convertir(cadena);
                // Insertar cadena en el conjunto
                // C.insert(aux);

                this->insert(aux);
            }
            contador++;
        }
        fe.close();
        return true;
    } // else
    fe.close();
    return false;
}

void CSS::insert(const crimen & x)
{
    baseDatos[x.getID()] = x;
    
    typename CSS::IUCR_iterator aux;
    aux.it_m= IUCRAccess.find(x.getIucr());
    if(aux.it_m != IUCRAccess.end())
    {
        
    }
    else
    {
        set<ID> aux;
        aux.insert(x.getID());
        IUCRAccess[x.getIucr()] = aux;    
    }
}

bool CSS::erase(unsigned int ID)
{
    if (baseDatos.erase(ID))
        return true;
    else
        return false;
}

typename CSS::iterator CSS::find_ID(const unsigned int ID)
{
    typename CSS::iterator it_devolver;
    it_devolver.it = baseDatos.find(ID);
    return it_devolver;
}

void CSS::setArrest(const unsigned int ID, bool value)
{
    typename CSS::iterator aux;
    aux.it = baseDatos.find(ID);
    if (aux.it != baseDatos.end())
        (*aux.it).second.setArrest(value);
}

ostream & operator<<(ostream & sal, const CSS & D)
{
    auto aux = D.baseDatos.begin();

    for (aux; aux != D.baseDatos.end(); aux++)
    {
        sal << (*aux).second;
    }
    return sal;
}

/////////////////////////////////ITERADORES/////////////////////////////////////

typename CSS::iterator CSS::begin()
{
    typename CSS::iterator sal;
    sal.it = baseDatos.begin();
    return sal;
}

typename CSS::iterator CSS::end()
{
    typename CSS::iterator sal;
    sal.it = baseDatos.end();
    return sal;
}

typename CSS::IUCR_iterator CSS::ibegin()
{
    typename CSS::IUCR_iterator sal;
    sal.it_m = IUCRAccess.begin();
    sal.it_s = IUCRAccess.begin()->second.begin();
}

typename CSS::IUCR_iterator CSS::iend()
{
    
}

pair<const ID, crimen >& CSS::iterator::operator*()
{
    return *(this->it);
}

CSS::iterator::iterator()
{

}

CSS::IUCR_iterator::IUCR_iterator()
{
    
}

#endif	/* CSS_HXX */

