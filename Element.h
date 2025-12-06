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

template <class T>
Element<T>::Element(){
    strKey = "";
    status = 0; // 0: Vacia, 1: Ocupada; 2: Borrada
    key = 0;
    data = 0;
}

#endif