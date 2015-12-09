/* 
 * File:   CSS.hxx
 * Author: superkorlas
 *
 * Created on 9 de diciembre de 2015, 18:07
 */

#ifndef CSS_HXX
#define	CSS_HXX

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
                
                baseDatos.insert(pair<ID, crimen>(aux.getID(),aux));
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
    baseDatos.insert(x.getID(), x);
}

bool CSS::erase( unsigned int ID)
{
    if(baseDatos.erase(ID))
        return true;
    else
        return false;
}

ostream & operator<<(ostream & sal, const CSS & D)
{
    typename map<ID, crimen>::iterator it;
    
    for (it = D.baseDatos.begin(); it != D.baseDatos.end(); it++)
    {
        cout << (*it).second;
    }
    return sal;
}

/////////////////////////////////ITERADORES/////////////////////////////////////

pair<const ID, crimen >& CSS::iterator::operator*()
{
    return *(this->it);
}

#endif	/* CSS_HXX */

