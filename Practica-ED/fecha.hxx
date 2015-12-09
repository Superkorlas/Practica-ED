#include <iostream>
#include <string>

using namespace std;

/** @brief fichero de implementacion de la clase fecha

 */
fecha::fecha()
{
    // @todo implementar esta funcion
    sec = 0;
    min = 0;
    hour = 0;
    mday = 1;
    mon = 1;
    year = 2000;
}

fecha::fecha(const fecha& x)
{
    // @todo implementar esta funcion
    *this = x;
}

fecha::fecha(const string& s)
{
    *this = s;
}

int fecha::getSec() const
{
    return sec;
}

int fecha::getMin() const
{
    return min;
}

int fecha::getHour() const
{
    return hour;
}

int fecha::getDay() const
{
    return mday;
}

int fecha::getMon() const
{
    return mon;
}

int fecha::getYear() const
{
    return year;
}

fecha & fecha::operator=(const fecha& f)
{
    //Sobrecarga del operador de asignaci�n
    if (this != &f)
    {
        (*this).sec = f.sec;
        (*this).min = f.min;
        (*this).hour = f.hour;
        (*this).mday = f.mday;
        (*this).mon = f.mon;
        (*this).year = f.year;
    }
    return *this;
}

fecha & fecha::operator=(const string& s) // formato  mm/dd/aaaa hh:mm:ss AM/PM
{
    (*this).mon = atoi((s.substr(0, 2)).c_str());
    (*this).mday = atoi((s.substr(3, 2)).c_str());
    (*this).year = atoi((s.substr(6, 4)).c_str());
    (*this).hour = atoi((s.substr(11, 2)).c_str());
    (*this).min = atoi((s.substr(14, 2)).c_str());
    (*this).sec = atoi((s.substr(17, 2)).c_str());

    if (s.compare(20, 2, "PM") == 0)
    {
        if (hour != 12)
            (*this).hour += 12;
    }
    else if (s.compare(20, 2, "AM") == 0)
    {
        if (hour == 12)
            (*this).hour = 0;
    }
}

string fecha::toString() const
{
    string meridian = (hour >= 12) ? "PM" : "AM";

    string mes, dia, hora, minutos, segundos;

    if (mon < 10 && mon > 0)
    {
        mes = "0" + to_string(mon);
    }
    else
    {
        mes = to_string(mon);
    }

    if (mday < 10 && mday > 0)
    {
        dia = "0" + to_string(mday);
    }
    else
    {
        dia = to_string(mday);
    }

    if (hour < 10 && hour >= 0)
    {
        hora = "0" + to_string(hour);
    }
    else
    {
        hora = to_string(hour);
    }

    if (min < 10 && min >= 0)
    {
        minutos = "0" + to_string(min);
    }
    else
    {
        minutos = to_string(min);
    }

    if (sec < 10 && sec >= 0)
    {
        segundos = "0" + to_string(sec);
    }
    else
    {
        segundos = to_string(sec);
    }

    string cadena = mes + "/" + dia + "/" + to_string(year) + " " +
            hora + ":" + minutos + ":" + segundos + " " + meridian;

    return cadena;
}

bool fecha::operator==(const fecha& f)const
{

    string fecha_1 = (*this).toString();
    string fecha_2 = f.toString();

    return (fecha_1.compare(fecha_2) == 0);

}

bool fecha::operator<(const fecha& f)const
{
    if (year < f.year)
        return true;
    else if (year > f.year)
        return false;

    if (mon < f.mon)
        return true;
    else if (mon > f.mon)
        return false;

    if (mday < f.mday)
        return true;
    else if (mday > f.mday)
        return false;

    float hora_1 = (hour * 60 * 60) + (min * 60) + sec;
    float hora_2 = (f.hour * 60 * 60) + (f.min * 60) + f.sec;
    return (hora_1 < hora_2);
}

bool fecha::operator<=(const fecha& f)const
{
    return (*this < f || *this == f);
}

bool fecha::operator>(const fecha& f)const
{
    return !(*this < f || *this == f);
}

bool fecha::operator>=(const fecha& f)const
{
    return !(*this < f);
}

bool fecha::operator!=(const fecha& f) const
{
    return !((*this) == f);
}

ostream& operator<<(ostream& os, const fecha& f)
{
    // @todo implementa esta funcion

    os << f.toString();
    return os;
}
