/* María Fernanda García Bushbeck A01199490
César Tadeo Bernal Sauceda A00841810
Regina Aguilar García A00841923

Fecha: 6/12/2025

Este archivo tiene como objetivo implementar una tabla hash para almacenar, buscar y eliminar elementos basados en claves de tipo string.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "Element.h"

#define MAXSIZE 20000 

using namespace std;

template <class T>
class HashTable{
    private:
        Element<T> **table;
        int currSize;
        // ---- FUNCIÓN HASH CORREGIDA ----
        int makeKey(string keyStr){
            int key = 0;
            for (char c : keyStr)
                key += c;
            return key;
        }
    public:
        HashTable();
        bool insert(string nameKey, T value);
        T search(string nameKey);
        bool remove(string nameKey);
        void print();
        ~HashTable();
};

// Constructor: Inicializa la tabla hash y el tamaño actual
// Complejidad: O(n)
template <class T>
HashTable<T>::HashTable(){
    currSize = 0;
    table = new Element<T>*[MAXSIZE];
    for(int i = 0; i < MAXSIZE; i++){
        table[i] = new Element<T>();
    }
}

// Inserta un nuevo elemento en la tabla hash
// Complejidad: O(1) en promedio, O(n) en el peor caso
template <class T>
bool HashTable<T>::insert(string nameKey, T value){
    int collisionCounter = 0;
    int intKey = makeKey(nameKey);
    int idx = intKey % MAXSIZE;
    int firstDeleted = -1;
    while (true) {
        if (table[idx]->status == 0) { // Vacía
            if (firstDeleted != -1) idx = firstDeleted;
            table[idx]->data = value;
            table[idx]->strKey = nameKey;
            table[idx]->key = intKey;
            table[idx]->status = 1;
            currSize++;
            return true;
        }
        if (table[idx]->status == 2) { // Borrada
            if (firstDeleted == -1)
                firstDeleted = idx;
        }
        if (table[idx]->status == 1 && table[idx]->strKey == nameKey) { // Actualizar valor existente
            table[idx]->data = value;
            return true;
        }
        collisionCounter++;
        idx = (intKey + collisionCounter) % MAXSIZE;
        if (collisionCounter >= MAXSIZE) { // Tabla llena
            cout << "Full table" << endl;
            return false;
        }
    }
}

// Busca un elemento en la tabla hash
// Complejidad: O(1) en promedio, O(n) en el peor caso
template <class T>
T HashTable<T>::search(string nameKey){
    int collisionCounter = 0;
    int intKey = makeKey(nameKey);
    int idx = (intKey + collisionCounter) % MAXSIZE;

    while(true){
        if(table[idx]->status != 0){
            if(table[idx]->status == 1 && table[idx]->strKey == nameKey){
                return table[idx]->data;
            }else{
                collisionCounter++;
                idx = (intKey + collisionCounter) % MAXSIZE;
            }
        }else{
            return T();  
        }
    }
}

// Elimina un elemento de la tabla hash
// Complejidad: O(1) en promedio, O(n) en el peor caso
template <class T>
bool HashTable<T>::remove(string nameKey){
    int collisionCounter = 0;
    int intKey = makeKey(nameKey);
    int idx = (intKey + collisionCounter) % MAXSIZE;

    while(true){
        if(table[idx]->status != 0){
            if(table[idx]->status == 1 && table[idx]->strKey == nameKey){
                table[idx]->status = 2;
                currSize--;
                return true;
            }
            collisionCounter++;
            idx = (intKey + collisionCounter) % MAXSIZE; 
        }else{
            cout << "Error: Key not found." << endl;
            return false; 
        }
    }
}

// Imprime el contenido de la tabla hash
// Complejidad: O(n)
template <class T>
void HashTable<T>::print() {
    for(int i = 0; i < MAXSIZE; i++){
        if(table[i]->status != 1){
            cout << "table[" << i << "] Empty" << endl;
        }else{
            cout << "table[" << i << "] " << table[i]->strKey << " -> " << table[i]->data << endl;
        }
    }
    cout << endl;
}

// Destructor: Libera la memoria asignada a la tabla hash
// Complejidad: O(n)
template <class T>
HashTable<T>::~HashTable(){
    for(int i = 0; i < MAXSIZE; i++){
        delete table[i];
    }
    delete[] table;
}

#endif