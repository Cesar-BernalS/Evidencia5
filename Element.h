/* María Fernanda García Bushbeck A01199490
César Tadeo Bernal Sauceda A00841810
Regina Aguilar García A00841923

Fecha: 6/12/2025

Este archivo tiene como objetivo definir la estructura de un elemento que se almacenará en la tabla hash.
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Element{
    public: 
        T data;
        string strKey;
        int key;
        int status;

        Element<T>();
};

// Constructor: Inicializa un elemento con valores por defecto
// Complejidad: O(1)
template <class T>
Element<T>::Element(){
    strKey = "";
    status = 0; // 0: Vacia, 1: Ocupada; 2: Borrada
    key = 0;
    data = 0;
}

#endif