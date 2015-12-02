#include <string>
#include <iostream> 

#include "fecha.h"

using namespace std;

//definición de los constructores

crimen::crimen()
{
	(*this).ID = 0;
	(*this).caseNumber = "";
	(*this).date;
	(*this).iucr = "";
	(*this).primaryType = "";
	(*this).description = "";
	(*this).locationDescription = "";
	(*this).arrest = false;
	(*this).domestic = false;
	(*this).latitude = 0;
	(*this).longitude = 0;

}

crimen::crimen(const crimen& x)
{
	*this = x;
}

//definición de los set

void crimen::setID(long int & id)
{
	(*this).ID = id;
}

void crimen::setCaseNumber(const string &  s)
{
	(*this).caseNumber = s;
}

void crimen::setDate(const fecha & d)
{
	(*this).date = d;
}

void crimen::setIucr(const string & i)
{
	(*this).iucr = i;
}

void crimen::setPrimaryType(const string & p)
{
	(*this).primaryType = p;
}

void crimen::setDescription(const string & d)
{
	(*this).description = d;
}

void crimen::setLocationDescription(const string & l)
{
	(*this).locationDescription = l;
}

void crimen::setArrest(bool a)
{
	(*this).arrest = a;
}

void crimen::setDomestic(bool d)
{
	(*this).domestic = d;
}

void crimen::setLatitude(const double & l)
{
	(*this).latitude = l;
}

void crimen::setLongitude(const double & l)
{
	(*this).longitude = l;
}

//definición de los get

long int crimen::getID() const
{
	return ID;
}

string crimen::getCaseNumber() const
{
	return caseNumber;
}

fecha crimen::getDate() const
{
	return date;
}

string crimen::getIucr() const
{
	return iucr;
}

string crimen::getPrimaryType() const
{
	return primaryType;
}

string crimen::getDescription() const
{
	return description;
}

string crimen::getLocationDescription() const
{
	return locationDescription;
}

bool crimen::getArrest() const
{
	return arrest;
}

bool crimen::getDomestic() const
{
	return domestic;
}

double crimen::getLatitude() const
{
	return latitude;
}

double crimen::getLongitude() const
{
	return longitude;
}

//definición de las sobrecargas

crimen & crimen::operator=(const crimen & x)
{
	if(this!= &x)
	{
		(*this).ID = x.ID;
		(*this).caseNumber = x.caseNumber;
		(*this).date = x.date;
		(*this).iucr = x.iucr;
		(*this).primaryType = x.primaryType;
		(*this).description = x.description;
		(*this).locationDescription = x.locationDescription;
		(*this).arrest = x.arrest;
		(*this).domestic = x.domestic;
		(*this).latitude = x.latitude;
		(*this).longitude = x.longitude;
	}

}

bool crimen::operator==(const crimen & x) const
{
	return ((*this).ID == x.ID);
}

bool crimen::operator!=(const crimen & x) const
{
	return !(*this == x);
}

bool crimen::operator<(const crimen & x) const
{
	return ((*this).ID < x.ID);
}

bool crimen::operator<=(const crimen & x) const
{
	return !((*this) > x);
}

bool crimen::operator>(const crimen & x) const
{
	return ((*this).ID > x.ID);
}

bool crimen::operator>=(const crimen & x) const
{
	return !(*this < x);
}

ostream& operator<< (ostream& os, const crimen& x)
{
	
	os << "ID: " << x.ID << "\n" << "Case Number: " << x.caseNumber << "\n"
		<< "Date: " << x.date << "\n" << "IUCR: " << x.iucr << "\n" << "Primary Type: "
		<< x.primaryType << "\n" << "Description: " << x.description << "\n"
		<< "Location Description: " << x.locationDescription << "\n";
	
	if(x.arrest == true)
		os << "Arrest: true" << "\n";
	else 
		os << "Arrest: false" << "\n";
		
	if(x.domestic == true)
		os << "Domestic: true" << "\n";
	else 
		os << "Domestic: false" << "\n";
	
	os  << "Latitude: " << x.latitude << "\n" << "Longitude: " << x.longitude << "\n\n";
	
	return os;
}

/***************************** FUNCTORES **********************************************/


bool ComparacionPorFechaDecreciente::operator()(const crimen &a, const crimen &b)const
{
	return (a.getDate() < b.getDate());
}

bool ComparacionPorFechaCreciente::operator()(const crimen &a, const crimen &b)const
{
	return (a.getDate() > b.getDate());
}

bool ComparacionPorIUCRCreciente::operator()(const crimen &a, const crimen &b)const
{
	return (a.getIucr() > b.getIucr());
}

bool ComparacionPorIUCRDecreciente::operator()(const crimen &a, const crimen &b)const
{
	return (a.getIucr() < b.getIucr());
}
