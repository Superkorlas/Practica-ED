/* 
 * conjunto.h
 * 
 * Copyright  (C) Juan F. Huete
 */

#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream> 
#include <algorithm>

#include "crimen.h"

using namespace std;

template <class CMP> class conjunto;
/** @brief imprime todas las entradas del conjunto 
        @post  No se modifica el conjunto.
        @todo implementar esta funcion
 */
template <class CMP>
ostream & operator<<(ostream & sal, const conjunto<CMP> & D);



//! Clase conjunto

/*! Métodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripción

 * Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

 * Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

 * Además encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al número de elementos en el conjunto.

 * El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática. 
 
 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 @todo Implementa esta clase, junto con su documentación asociada
 */



template <class CMP>
class conjunto
{
public:
    /** @brief entrada permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto
     */
    typedef crimen entrada;
    /** @brief size_type numero de elementos en el conjunto
     */
    typedef unsigned int size_type;
    /** @brief constructor primitivo. 
     */
    conjunto();
    //declaraciones previa de los iteradores
    class iterator;
    class const_iterator;
    class arrest_iterator; // Iterador sobre los delitos que implicaron un arresto (Arrest==true)
    class const_arrest_iterator;
    class description_iterator; // Iterador sobre los delitos que concuerdan con la descripcion
    class const_description_iterator;

    /** @brief constructor de copia
    @param[in] d conjunto a copiar
     */
    conjunto(const conjunto<CMP> & d);



    /**@brief Constructor de conjunto que contiene los elementos contenidos en el rango [ini,fin) 
    @param ini iterador inicial, fin iterador final

     */
    conjunto(iterator ini, iterator fin);

    /** @brief busca un crimen en el conjunto
            @param id identificador del crimen  buscar
            @return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
            @post no modifica el conjunto.
	
            \code Ejemplo
	
            if (C.find(12345)!=C.end() ) cout << "Esta" ;
            else cout << "No esta";
	
            \endcode
     */
    conjunto::const_iterator find(const long int & id) const;

    /** @brief busca un crimen en el conjunto
    @param crimen a buscar
    @return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
    @post no modifica el conjunto.
	
    \code Ejemplo
	
    if (C.find(12345)!=C.end() ) cout << "Esta" ;
    else cout << "No esta";
	
    \endcode
     */
    conjunto::iterator find(const entrada &c)const;

    /** @brief busca los crimenes con el mismo codigo IUCR
    @param icur identificador del crimen  buscar
    @return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
    @post no modifica el conjunto.
    \verbatim Uso
    vector<crimen> C, A;
    ....
    A = C.findIUCR("0460");
    \endverbatim
     */
    conjunto findIUCR(const string & iucr) const;

    /** @brief busca los crimenes que contienen una determinada descripcion 
            @param descr string que representa la descripcion del delito buscar
            @return Devuelve un  conjunto con todos los crimenes  que contengan descr en su descripcionR. Si no existe ninguno devuelve el conjunto vacio.
            @post no modifica el conjunto.
            \verbatim Uso
            vector<crimen> C, A;
            ....
            A = C.findDESCR("BATTERY");
            \endverbatim
     */
    conjunto findDESCR(const string & descr) const;

    /** @brief Inserta una entrada en el conjunto
            @param e entrada a insertar
            @return true si la entrada se ha podido insertar con éxito. False en caso contrario
            @post 	 Si e no esta en el conjunto, el size() sera incrementado en 1.
     */
    bool insert(const conjunto<CMP>::entrada & e);



    /** @brief Borra el delito dado un identificacador.
	
    Busca la entrada con id en el conjunto  y si la encuentra la borra
	
    @param[in] id a borrar
    @return true si la entrada se ha podido borrar con éxito. False en caso contrario
    @post Si esta en el conjunto su tamaño se decrementa en 1.
     */
    bool erase(const long int & id);


    /** @brief Borra una crimen con identificador dado por e.getID() en el conjunto.
	
    Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra
	
    @param[in] entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
    @return true si la entrada se ha podido borrar con éxito. False en caso contrario
    @post Si esta en el conjunto su tamaño se decrementa en 1.
     */
    bool erase(const conjunto<CMP>::entrada & e);

    /**@brief Devuelven un iterador al primer elemento en el contenedor que no precede a x en el conjunto,
     esto es, es equivalente a x o le sigue según la relacion de orden definida por CMP. 
     Esta función utiliza el functor interno devolviendo un iterador al primer elemento, e, 
     para el que se satisface que comp(e,x) es falso. 
     *@param crimen a buscar
     *@return iterador al encontrado o al siguiente * si no está.
     */
    iterator lower_bound(const entrada & x);

    /**@brief Devuelven un iterador constante al primer elemento en el contenedor que no precede a x en el conjunto,
     esto es, es equivalente a x o le sigue según la relacion de orden definida por CMP. 
     Esta función utiliza el functor interno devolviendo un iterador al primer elemento, e, 
     para el que se satisface que comp(e,x) es falso. 
     *@param crimen a buscar
     *@return iterador constante el encontrado o al siguiente * si no está.
     */
    const_iterator lower_bound(const entrada & x) const;

    /**@brief Devuelven un iterador al primer elemento que sigue a x según la relacion de orden definida por CMP. 
    Esta función utiliza el functor interno devolviendo un iterador al primer elemento, e, 
    para el que se satisface que comp(x,e) es cierto.
    iterator upper_bound (const entrada & x);
     *@param crimen a buscar
     *@return iterador el encontrado o al siguiente * si no está.
     */
    iterator upper_bound(const entrada & x);

    /**@brief Devuelven un iterador constante al primer elemento que sigue a x según la relacion de orden definida por CMP. 
    Esta función utiliza el functor interno devolviendo un iterador al primer elemento, e, 
    para el que se satisface que comp(x,e) es cierto.
    iterator upper_bound (const entrada & x);
     *@param crimen a buscar
     *@return iterador constante el encontrado o al siguiente * si no está.
     */
    const_iterator upper_bound(const entrada & x) const;


    /** @brief operador de asignación
            @param[in] org conjunto  a copiar.
             Crea un conjunto duplicado exacto de org.
     */
    conjunto<CMP> & operator=(const conjunto<CMP> & org);

    /** @brief numero de entradas en el conjunto
            @post  No se modifica el conjunto.
     */
    unsigned int size() const;


    /** @brief Chequea si el conjunto esta vacio
        @return true si size()==0, false en caso contrario.
     */
    bool empty() const;


    // ================================= ITERADORES ========================================/

    // ================================= iterator ==========================================/

    /**@brief devuelve iterador al inicio del conjunto
     */
    typename conjunto<CMP>::iterator begin();

    /**@brief devuelve iterador al final (posición siguiente al último del conjunto
     */
    typename conjunto<CMP>::iterator end();

    /** @brief class iterator
     * forward iterador sobre el conjunto, LECTURA
     *  iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
     * */
    class iterator
    {
    public:

        /** @brief constructor defecto iterator
         */
        iterator();

        /** @brief constructor copia iterator
         */
        iterator(const iterator & it);

        /** @brief Sobrecarga del operador asterisco.
                    @return Devuelve el un conjunto.
         */
        const typename conjunto<CMP>::entrada & operator*() const;

        /** @brief Sobrecarga del operador ++. Operador de pre-incremento.
                @return Devuelve un iterador conjunto actual y luego incrementa a donde apunta el iterador.
         */
        iterator operator++(int);

        /** @brief Sobrecarga del operador ++. Operador de post-incremento.
                @return Devuelve un iterador conjunto siguiente.
         */
        iterator & operator++();

        /** @brief Sobrecarga del operador --. Operador de pre-decremento.
                 @return Devuelve un iterador conjunto actual y luego decrementa a donde apunta el iterador.
         */
        iterator operator--(int);

        /** @brief Sobrecarga del operador --. Operador de post-decremento.
                @return Devuelve un iterador conjunto anterior.
         */
        iterator & operator--();

        /** @brief Sobrecarga del operador ==. Operador de comparacion de igualdad.
                @return Devuelve true si son iguales y false si no lo son.
         */
        bool operator==(const iterator & it);

        /** @brief Sobrecarga del operador !=. Operador de comparacion de desigualdad.
                @return Devuelve false si son iguales y true si no lo son.
         */
        bool operator!=(const iterator & it);

    private:
        /** @brief Declaramos esta clase como amiga de conjunto.
         */
        friend class conjunto<CMP>;

        /** @brief Iterador sobre un vector de crimenes.
         */
        vector<entrada>::iterator itv;
    };

    // ================================= const_iterator ==========================================/

    /** @brief  
    @return Devuelve el const_iterator a la primera posición del conjunto.
            @post no modifica el diccionario
     */
    typename conjunto<CMP>::const_iterator cbegin();

    /** @brief iterador al final
    @return Devuelve el iterador constante a la  posición final del conjunto.
            @post no modifica el diccionario
     */
    typename conjunto<CMP>::const_iterator cend();

    /** @brief class const_iterator
     * forward iterador constante sobre el diccionario, Lectura 
     *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
     * */
    class const_iterator
    {
    public:
        /** @brief constructor defecto const_iterator
         */
        const_iterator();

        /** @brief constructor copia const_iterator
         */
        const_iterator(const const_iterator & it);

        /** @brief Convierte iterator en const_iterator
         */
        const_iterator(const iterator & it);

        /** @brief Sobrecarga del operador asterisco.
            @return Devuelve un conjunto.
         */
        const typename conjunto<CMP>::entrada & operator*() const;

        /** @brief Sobrecarga del operador ++. Operador de pre-incremento.
                 @return Devuelve un iterador conjunto actual y luego incrementa a donde apunta el iterador.
         */
        const_iterator operator++(int);

        /** @brief Sobrecarga del operador ++ en modo post-incremento. 
    @return Devuelve una referencia del iterador a la posición siguiente del conjunto de crimenes.
         */
        const_iterator & operator++();

        /** @brief Sobrecarga del operador -- en modo pre-decremento.
    @return Devuelve un iterador al conjunto actual y luego decrementa a donde apunta el iterador.
         */
        const_iterator operator--(int);

        /** @brief Sobrecarga del operador -- en modo post-decremento. 
@return Devuelve una referencia del iterador a la posición anterior del conjunto de crimenes.
         */
        const_iterator & operator--();

        /** @brief Sobrecarga del operador ==. Operador de comparacion de igualdad.
                @return Devuelve true si son iguales y false si no lo son.
         */
        bool operator==(const const_iterator & it);

        /** @brief Sobrecarga del operador !=. Operador de comparacion de desigualdad.
                @return Devuelve false si son iguales y true si no lo son.
         */
        bool operator!=(const const_iterator & it);

    private:

        /** @brief Iterador sobre un vector de crimenes.
         */
        vector<entrada>::const_iterator c_itv;

        /** @brief Declaramos esta clase como amiga de conjunto.
         */
        friend class conjunto<CMP>;

    };

private:
    vector<crimen> vc; // vector ORDENADO por crimen.id que almacena los elementos del conjunto

    /** \invariant
 
    IR: rep ==> bool
 
   \li Para todo i, 0 <= i < vc.size() se cumple
           vc[i].ID > 0;
   \li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
           vc[i].ID< vc[i+1].ID

     */


    /** @brief Chequea el Invariante de la representacion 
        @return true si el invariante es correcto, falso en caso contrario
     */
    bool cheq_rep() const;

    //  declaracion del operator<< como metodo amigo
    friend ostream & operator<< <> (ostream & sal, const conjunto<CMP> & D);

    // Clases amigas  ....
    friend class iterator;
    friend class const_iterator;

    CMP comp;
};



#include "conjunto.hxx"

#endif
