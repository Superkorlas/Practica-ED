/*! Implementacion  de la clase conjunto

*/

/** @todo implementar la funcion
*/

template<class CMP>
conjunto<CMP>::conjunto()
{}

template<class CMP>
conjunto<CMP>::conjunto(const conjunto<CMP> & d)
{
	(*this).vc = d.vc;
}

template<class CMP>
conjunto<CMP>::conjunto(iterator ini, iterator fin)
{
	while(ini!=fin){
		this->vc.push_back(*ini);
		ini++;
	}

}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::find( const long int & id) const
{
	typename conjunto<CMP>::const_iterator it_devolver;

	it_devolver.c_itv = vc.end();

	bool encontrado = false; 
	 
	for(it_devolver.c_itv = vc.begin(); it_devolver.c_itv != vc.end() && !encontrado; it_devolver.c_itv++)
	{
		if(it_devolver.c_itv->getID() == id)
		{
			encontrado = true;
		}
	}

	return it_devolver;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::find(const entrada &c)const
{
	typename conjunto<CMP>::const_iterator dev;
	dev = this.find(c.getID());

	return dev;
}

template<class CMP>
conjunto<CMP> conjunto<CMP>::findIUCR(const string & iucr) const
{
	conjunto<CMP> encontrados;
	typename vector<crimen>::const_iterator it;

	for(it = vc.cbegin(); it != vc.cend(); it++)
	{

		if( (*it).getIucr() == iucr )
			encontrados.insert((*it));
	}

	return encontrados;
}

template<class CMP>
conjunto<CMP> conjunto<CMP>::findDESCR(const string & descr) const
{
	conjunto<CMP> encontrados;
	typename vector<crimen>::const_iterator it;

	for(it = vc.cbegin(); it != vc.cend(); it++)
	{
		//Si contiene a la cadena descr devuelve la posicion de la palabra,si no la contiene devuelve un -1
		if( (*it).getDescription().find(descr) != -1)
			encontrados.insert(*it);
	}

	return encontrados;
}

template<class CMP>
bool conjunto<CMP>::insert(const conjunto<CMP>::entrada& e)
{

	typename vector<crimen>::iterator it;
	bool introducido = false;

	//Si no hubiera ningun crimen en el vector, directamente lo introduce el crimen
	if(size() == 0){
		vc.push_back(e);
		introducido = true;
	}
	//En el caso de que haya crimenes en el vector
	else
	{	
		typename conjunto<CMP>::const_iterator com;

		com = find(e.getID());

		//Este if busca si ya existe en el conjunto, y si no existe entra.
		if (com.c_itv == vc.end())
		{
			for(it = vc.begin(); it != vc.end() && !introducido; it++)
			{
				if (comp(e, (*it)) )  //CORREGIDO
				{
					vc.insert(it, e);	//Insertar crimen en la posicion dada por it
					introducido = true;
				} 
				else if(it+1 == vc.cend())	//En caso de que el lugar a ocupar sea el ultimo
				{	
					vc.push_back(e);
					introducido = true;
				}
			}
		}
	}
	//Retornar si lo ha introducido o no.
	return introducido;
}

template<class CMP>
bool conjunto<CMP>::erase(const long int & id)
{
	bool encontrado = false;
	typename vector<crimen>::iterator it;
	
	if(size() != 0)
	{	
		for(it = vc.begin(); it != vc.end() && !encontrado; it++)
		{
			if((*it).getID() == id)
				{
					vc.erase(it);
					encontrado = true;
				}
		}
	}

	return encontrado;
}

template<class CMP>
bool conjunto<CMP>::erase(const conjunto<CMP>::entrada & e)
{
	bool encontrado = erase(e.getID());

	return encontrado;
}

template<class CMP>
conjunto<CMP> & conjunto<CMP>::operator=(const conjunto<CMP> & org)
{
	(*this).vc = org.vc;
}

template<class CMP>
unsigned int conjunto<CMP>::size() const
{
	return vc.size();
}

template<class CMP>
bool conjunto<CMP>::empty()const
{
	return (size() == 0);
}

template<class CMP>
ostream &  operator << ( ostream & sal, const conjunto<CMP> & D)
{
	typename vector<crimen>::const_iterator it;
	for(it = D.vc.cbegin(); it != D.vc.cend(); it++)
	{
		cout << *it;
	}
	return sal;
}

template<class CMP>
bool conjunto<CMP>::cheq_rep() const
{
	bool invariante = true;
	typename vector<crimen>::const_iterator it,it_mayor;
	
	//Comprobamos que todos los crímenes tengan un ID válido (mayor que 0).
	for(it = vc.cbegin(); it != vc.cend(); it++)
	{
		if((*it).getID() < 0)
		{
			invariante = false;
		}
	}
	
	//Comprobamos que todos los crímenes tengan un ID menor que el crimen siguiente.
	for(it = vc.cbegin(); it != vc.cend() - 1; it++)
	{
		it_mayor = it + 1;
		if((*it).getID() > (*it_mayor).getID())
		{
			invariante = false;
		}
	}
	
	return invariante;
}

template <class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::lower_bound (const conjunto<CMP>::entrada& x)
{
	typename vector<crimen>::iterator it;
	it = std::lower_bound(vc.begin(), vc.end(), x, comp);
	typename conjunto<CMP>::iterator salida;
	salida.itv = it;
	return salida;
}

template <class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::lower_bound (const conjunto<CMP>::entrada& x) const
{
	typename vector<crimen>::const_iterator it;
	it = std::lower_bound(vc.begin(), vc.end(), x, comp);
	typename conjunto<CMP>::const_iterator salida;
	salida.itv = it;
	return salida;	
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::upper_bound(const conjunto<CMP>::entrada & x)
{

	typename vector<crimen>::iterator it;
	it = std::upper_bound(vc.begin(), vc.end(), x, comp);
	typename conjunto<CMP>::iterator salida;
	salida.itv = it;
	return salida;
	
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::upper_bound(const conjunto<CMP>::entrada & x) const
{
	typename vector<crimen>::const_iterator it;
	it = std::upper_bound(vc.cbegin(), vc.cend(), x, comp);
	typename conjunto<CMP>::const_iterator salida;
	salida.itv = it;
	return salida;
}

// ================================= ITERADORES ========================================/

// ================================= iterator ==========================================/

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::begin()
{
	typename conjunto<CMP>::iterator sal;
	sal.itv = vc.begin();
    return  sal;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::end()
{
	typename conjunto<CMP>::iterator sal;
	sal.itv = vc.end();
	return sal;
}

template<class CMP>
conjunto<CMP>::iterator::iterator()
{}

template<class CMP>
conjunto<CMP>::iterator::iterator(const conjunto<CMP>::iterator & i)
{
  	itv = i.itv;
}

template<class CMP>
const typename conjunto<CMP>::entrada& conjunto<CMP>::iterator::operator*() const
{
	return *(this->itv);
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator++(int)
{
	typename conjunto<CMP>::iterator temp(*this);
	(this->itv)++;
	return temp;
}

template<class CMP>
typename conjunto<CMP>::iterator& conjunto<CMP>::iterator::operator++()
{
	this->itv = this->itv +1;
	return (*this);
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator--(int)
{
	typename conjunto<CMP>::iterator temp(*this);
	--(*this);
	return temp;
}

template<class CMP>
typename conjunto<CMP>::iterator& conjunto<CMP>::iterator::operator--()
{
	this->itv = this->itv -1;
	return (*this);
}

template<class CMP>
bool conjunto<CMP>::iterator::operator==(const iterator & it)
{
	return (this->itv == it.itv);
}

template<class CMP>
bool conjunto<CMP>::iterator::operator!=(const iterator & it)
{
	return (this->itv != it.itv);
}

// ================================= const_iterator ==========================================/
template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cbegin()
{
	typename conjunto<CMP>::const_iterator sal;
	sal.c_itv = vc.cbegin();
    return sal;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cend()
{
	typename conjunto<CMP>::const_iterator sal;
	sal.c_itv = vc.cend();
	return sal;
}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator()
{}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::const_iterator & i)
{
  	c_itv = i.c_itv;
}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::iterator & i)
{
  	c_itv = i.itv;
}

template<class CMP>
const typename  conjunto<CMP>::entrada& conjunto<CMP>::const_iterator::operator*() const
{
	return *(this->c_itv);
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator++(int)
{
	typename conjunto<CMP>::const_iterator temp(*this);
	(this->c_itv)++;
	return temp;
}

template<class CMP>
typename conjunto<CMP>::const_iterator& conjunto<CMP>::const_iterator::operator++()
{
	this->c_itv = this->c_itv +1;
	return (*this);
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator--(int)
{
	typename conjunto<CMP>::const_iterator temp(*this);
	--(*this);
	return temp;
}

template<class CMP>
typename conjunto<CMP>::const_iterator& conjunto<CMP>::const_iterator::operator--()
{
	this->c_itv = this->c_itv -1;
	return (*this);
}

template<class CMP>
bool conjunto<CMP>::const_iterator::operator==(const const_iterator & it)
{
	return (this->c_itv == it.c_itv);
}

template<class CMP>
bool conjunto<CMP>::const_iterator::operator!=(const const_iterator & it)
{
	return (this->c_itv != it.c_itv);
}
