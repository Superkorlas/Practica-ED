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
    ID id = x.getID();
    
    this->baseDatos[id] = x;
    
    typename CSS::IUCR_iterator aux;
    aux.it_m= IUCRAccess.find(x.getIucr());
    if(aux.it_m != IUCRAccess.end())
    {
        (*aux.it_m).second.insert(id);
    }
    else
    {
        set<ID> temp;
        temp.insert(id);
        IUCRAccess[x.getIucr()] = temp;    
    }
}

bool CSS::erase(unsigned int ID)
{
    typename CSS::iterator temp = this->find_ID(ID);
    if (temp.it != baseDatos.end())
    {
        //Obtención de datos necesarios
        string Iucr = temp.it->second.getIucr();
        
        //Borrado de baseDatos
        baseDatos.erase(ID);
        
        //Borrado de IUCRAccess
        map<IUCR, set<unsigned int> >::iterator aux = this->IUCRAccess.find(Iucr);
        aux->second.erase(ID);
        if (aux->second.size() == 0)
            IUCRAccess.erase(aux);
        
        return true;
    }
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

CSS::IUCR_iterator CSS::lower_bound(IUCR aux)
{
    typename CSS::IUCR_iterator it;
    it.it_m = IUCRAccess.lower_bound(aux);
    it.it_s = it.it_m->second.begin();
    return it;
}

CSS::IUCR_iterator CSS::upper_bound(IUCR aux)
{
    typename CSS::IUCR_iterator it;
//    it.it_m = std::upper_bound(IUCRAccess.begin(), IUCRAccess.end(), aux);
    it.it_m = IUCRAccess.lower_bound(aux);
    it.it_s = it.it_m->second.begin();
    return it;
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
    typename CSS::IUCR_iterator sal;
    sal.it_m = IUCRAccess.end();
    sal.it_s = IUCRAccess.begin()->second.end();
}

//pair<const ID, crimen >& CSS::iterator::operator*()
//{
//    pair<const ID, crimen > aux;
//    aux.first = (*this->it).first;
//    aux.second = (*this->it).second;
//    return aux;
//}
//
//pair<const ID, crimen >& CSS::IUCR_iterator::operator*()
//{
//    CSS::iterator aux;
//    aux.it = baseDatos.find(*it_s);
//    return ((*aux.it).first, (*aux.it).second);
//}

//pair<const ID, crimen >& CSS::Date_iterator::operator*()
//{
//    return *(this->it);
//}

CSS::iterator::iterator()
{

}

CSS::IUCR_iterator::IUCR_iterator()
{
    
}

CSS::Date_iterator::Date_iterator()
{
    
}

#endif	/* CSS_HXX */

