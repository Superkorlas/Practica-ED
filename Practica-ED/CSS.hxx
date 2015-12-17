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
    //Datos necesarios
    ID id = x.getID();
    fecha date = x.getDate();
    string descripcion = x.getDescription();
    Longitud longitud = x.getLongitude();
    Latitud latitud = x.getLatitude();
    
    //Insercion en baseDatos
    this->baseDatos[id] = x;
    CSS::iterator it;
    it.it = this->baseDatos.find(id);
    
    //Insercion en DateAccess
    pair< fecha, map< ID, crimen>::iterator > tmp;
    tmp.first = x.getDate();
    tmp.second = it.it;
    this->DateAccess.insert(tmp);
    
    //Insercion en IUCRAccess
    CSS::IUCR_iterator aux;
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
    
    //Insercion en index (unordered_map)
    string::iterator it_s;
    string termino = "";
    for (it_s = descripcion.begin(); it_s != descripcion.end(); it_s++)
    {
        if((*it_s) == ' ')
        {
            unordered_map<Termino, set<ID> >::iterator it_u(index.find(termino));
            if (it_u != index.end())
            {
                (*it_u).second.insert(id);
            }
            else
            {
                set<ID> unordered;
                unordered.insert(id);
                index[termino] = unordered;
            }
            termino = "";
        }
        
        else
        {
            termino += (*it_s);
        }
    }
    
    //Insercion en posicionGeo  map<Longitud,multimap<Latitud, ID> >
    multimap <Latitud, ID> m;
    m.insert(pair<Latitud, ID>(latitud, id));
    posicionGeo[longitud] = m;
}

bool CSS::erase(unsigned int ID)
{
    CSS::iterator temp = this->find_ID(ID);
    if (temp.it != baseDatos.end())
    {
        //Obtención de datos necesarios
        string Iucr = temp.it->second.getIucr();
        string descripcion = temp.it->second.getDescription();
        Longitud longitud = temp.it->second.getLongitude();
        Latitud latitud = temp.it->second.getLatitude();
        
        //Borrado de DateAccess
        multimap< fecha, map< unsigned int, crimen>::iterator >::iterator it_date;
        bool encontrado = false;
        for (it_date = DateAccess.begin(); it_date != DateAccess.end() && !encontrado; it_date++)
        {
            if (it_date->second == temp.it)
            {
                DateAccess.erase(it_date);
                encontrado = true;
            }
        }
        
        //Borrado de IUCRAccess
        map<IUCR, set<unsigned int> >::iterator aux = this->IUCRAccess.find(Iucr);
        aux->second.erase(ID);
        if (aux->second.size() == 0)
            IUCRAccess.erase(aux);
        
        //Borrado en index (unordered_map)
        string::iterator it_s;
        string termino = "";
        for (it_s = descripcion.begin(); it_s != descripcion.end(); it_s++)
        {
            if((*it_s) == ' ')
            {
                unordered_map<Termino, set<unsigned int> >::iterator it_u(index.find(termino));
                (*it_u).second.erase(ID);
                termino = "";
            }

            else
            {
                termino += (*it_s);
            }
        }
        
        //Borrado en posicionGeo  map<Longitud,multimap<Latitud, ID> >
        map<Longitud,multimap<Latitud, unsigned int> >::iterator posicion(posicionGeo.find(longitud));
        multimap <Latitud, unsigned int>::iterator pos((*posicion).second.begin());
        for (pos = (*posicion).second.begin(); pos != (*posicion).second.end(); pos++)
        {
            if (pos->second == ID)
            {
                posicion->second.erase(pos);
                if(posicion->second.empty())
                    posicionGeo.erase(posicion);
            }
        }
                
        //Borrado de baseDatos
        baseDatos.erase(ID);
        
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
    CSS::iterator aux;
    aux.it = baseDatos.find(ID);
    if (aux.it != baseDatos.end())
        (*aux.it).second.setArrest(value);
}

list<ID> CSS::inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2)
{
    list<ID> lista;
    
    for (auto tmp = posicionGeo.lower_bound(x1); tmp != posicionGeo.upper_bound(x2); tmp++)
    {
        for (auto aux = tmp->second.lower_bound((y1)); aux != tmp->second.upper_bound(y2); aux++)
        {
            lista.push_back(aux->second);
        }
    }
    
    return lista;
}

CSS::IUCR_iterator CSS::lower_bound(IUCR aux)
{
    CSS::IUCR_iterator it;
    it.it_m = IUCRAccess.lower_bound(aux);
    it.it_s = it.it_m->second.begin();
    return it;
}

CSS::IUCR_iterator CSS::upper_bound(IUCR aux)
{
    CSS::IUCR_iterator it;
    it.it_m = IUCRAccess.lower_bound(aux);
    it.it_s = it.it_m->second.begin();
    return it;
}

CSS::Date_iterator CSS::lower_bound(fecha aux)
{
    CSS::Date_iterator it;
    it.it_mm = DateAccess.lower_bound(aux);
    return it;
}

CSS::Date_iterator CSS::upper_bound(fecha aux)
{
    CSS::Date_iterator it;
    it.it_mm = DateAccess.lower_bound(aux);
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

CSS::IUCR_iterator CSS::ibegin()
{
    CSS::IUCR_iterator sal;
    sal.it_m = IUCRAccess.begin();
    sal.it_s = IUCRAccess.begin()->second.begin();
    return sal;
}

CSS::IUCR_iterator CSS::iend()
{
    CSS::IUCR_iterator sal;
    sal.it_m = IUCRAccess.end();
    sal.it_s = IUCRAccess.begin()->second.end();
    return sal;
}

CSS::Date_iterator CSS::dbegin()
{
    CSS::Date_iterator sal;
    sal.it_mm= DateAccess.begin();
    return sal;
}

CSS::Date_iterator CSS::dend()
{
    CSS::Date_iterator sal;
    sal.it_mm= DateAccess.end();
    return sal;
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int)
{
    CSS::IUCR_iterator tmp;
    tmp = (*this);
    ++(*this);
    return tmp;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++()
{
    assert(this->it_m != ptr->IUCRAccess.end());
    
    if(this->it_s != this->it_m->second.end())
        this->it_s++;
    else 
    {
        this->it_m++;
        if(this->it_m != ptr->IUCRAccess.end())
            this->it_s = this->it_m->second.begin();
    }
    return (*this);
}


pair<const ID, crimen >& CSS::iterator::operator*()
{
    return (*this->it);
}

pair<const ID, crimen >& CSS::IUCR_iterator::operator*()
{
    CSS::iterator aux;
    aux = ptr->find_ID(*it_s);
    return (*aux.it);
}

pair<const ID, crimen >& CSS::Date_iterator::operator*()
{
    return (*(*this).it_mm->second);
}

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

