#include "conjunto.h"
#include "crimen.h"
#include "fecha.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

using namespace std;


int contador = 0;


//Convierte una cadena en un crimen
crimen convertir(const string& cadena)
{
	string temp = "";
	int primero = 0;
	int  ultimo = 0;
	crimen a_devolver;
	
	for (int i = 0; i < 22; i++)
	{
		if (cadena[primero] == '\"')
		{
			ultimo = cadena.find_first_of('\"', ++primero);
		}
		else if (cadena[primero] == ',' && cadena[primero-1] == '\"')
		{
			primero++;
			ultimo = cadena.find_first_of(",", primero);
		}
	
		else
		{
			ultimo = cadena.find_first_of(",", primero);
		}
		
		temp = cadena.substr(primero, (ultimo-primero));
		
		if (i == 0) //ID 
		{
			long int enteroID = atoi(temp.c_str());
			a_devolver.setID(enteroID);
		}
		
		else if (i == 1) //Case Number 
		{
			a_devolver.setCaseNumber(temp);
		}
		
		if (i == 2) //Date
		{
			fecha aux = temp;
			a_devolver.setDate(aux);
		}
		
		else if (i == 4) //IUCR
		{
			a_devolver.setIucr(temp);
		}
		
		else if (i == 5) //Primary Tape 
		{
			a_devolver.setPrimaryType(temp);
		}
		
		else if (i == 6) //Description
		{
			a_devolver.setDescription(temp);
		}
		
		else if (i == 7) //Location Description 
		{
			a_devolver.setLocationDescription(temp);
		}
		
		else if (i == 8) //Arrest
		{
			if(temp == "true")
				a_devolver.setArrest(true);
			else a_devolver.setArrest(false);
		}
		
		else if (i == 9) //Domestic
		{
			if(temp == "true")
				a_devolver.setDomestic(true);
			else a_devolver.setDomestic(false);
		}
		
		else if (i == 19 && temp != "") //Latitud 
		{
			long double enteroID = atof(temp.c_str());
			a_devolver.setLatitude(enteroID);
		}
		
		else if (i == 20 && temp != "") //Longitud
		{
			long double enteroID = atof(temp.c_str());
			a_devolver.setLongitude(enteroID);
		}
		
		primero = ++ultimo;
	}
	return a_devolver;
}

/** @brief lee un fichero de delitos, linea a linea
@param[in] s nombre del fichero
@param[in,out] C conjunto sobre el que se lee
@return true si la lectura ha sido correcta, false en caso contrario
*/

template <class CMP>
bool load(conjunto<CMP> &C, const string & s) {
	ifstream fe;
	string cadena;
	int contador = 0;

	cout << "Abrimos " << s << endl;
	fe.open(s.c_str(), ifstream::in);
	if (fe.fail())
	{
		cerr << "Error al abrir el fichero " << s << endl;
	}
	else {
		getline(fe, cadena, '\n'); //leo la cabecera del fichero
		cout << cadena << endl;
		while (/*!fe.eof()*/contador < 10)
		{
			getline(fe, cadena, '\n');
			if (!fe.eof()) {
				//cout << "leo:: " << cadena << endl;
				// Convertir cadena a crimen
				// crimen aux = cadena;
				crimen aux = convertir(cadena);
				// Insertar cadena en el conjunto
				// C.insert(aux);
				C.insert(aux);
			}
			contador++;
		}
		fe.close();
		return true;
	} // else
	fe.close();
	return false;
}

int main()
{

	conjunto<less<crimen> > ChicagoDB;

	load(ChicagoDB, "crimenes.csv");

	cout << ChicagoDB << endl;

	/* Comprobacion de lower_bound(): * /  
	conjunto<ComparacionPorIDCreciente>::iterator it1, it2;
	it1 = ChicagoDB.begin();
	crimen c1(*it1);
	cout << "Este es----------------------------------------------" << endl;
	cout << c1 << endl;
	it2 = ChicagoDB.lower_bound(c1);
	cout << "Resultado de lower_bound----------------------------------------------" << endl;
	cout << *it2;
	
	/* Comprobacion de const_lower_bound(): * /
	conjunto<ComparacionPorIDCreciente>::const_iterator it3, it4;
	it3 = ChicagoDB.begin();
	crimen c2(*it3);
	cout << "Este es----------------------------------------------" << endl;
	cout << c2 << endl;
	it4 = ChicagoDB.lower_bound(c2);
	cout << "Resultado de lower_bound----------------------------------------------" << endl;
	cout << *it4;
	


    /* Comprobacion de upper_bound(): * /
	conjunto<ComparacionPorIDCreciente>::iterator it1, it2;
	it1 = ChicagoDB.begin();
	crimen c1(*it1);
	cout << "Este es----------------------------------------------" << endl;
	cout << c1 << endl;
	it2 = ChicagoDB.upper_bound(c1);
	cout << "Resultado de upper_bound----------------------------------------------" << endl;
	cout << *it2;


	/* Comprobacion de const_upper_bound(): * /
	conjunto<ComparacionPorIDCreciente>::const_iterator it3, it4;
	it3 = ChicagoDB.begin();
	crimen c2(*it3);
	cout << "Este es----------------------------------------------" << endl;
	cout << c2 << endl;
	it4 = ChicagoDB.upper_bound(c2);
	cout << "Resultado de upper_bound----------------------------------------------" << endl;
	cout << *it4;
*/

	conjunto<less<crimen> >::iterator it1, it2;
	it1= ChicagoDB.begin();
	it1++;
	it1++;
	crimen c2(*it1);
	cout << "Este es----------------------------------------------" << endl;
	cout << c2 << endl;
	it2 = ChicagoDB.upper_bound(c2);
	cout << "Resultado de upper_bound----------------------------------------------" << endl;
	if(it2!=ChicagoDB.end())
		cout << *it2;

	it2 = ChicagoDB.lower_bound(c2);
	cout << "Resultado de lower_bound----------------------------------------------" << endl;
	if(it2!=ChicagoDB.end())
		cout << *it2;

	/*
	conjunto<less<crimen> > prueba(it1,it2);
	cout << "Segundo conjunto.\n";
	cout << prueba;
	*/


/*
	conjunto<ComparacionPorFechaCreciente>::iterator it;
	for(it = ChicagoDB.begin(); it != ChicagoDB.end(); it++)
		cout << *it << endl;

// */
	return 0;
}
