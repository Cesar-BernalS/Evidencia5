/* María Fernanda García Bushbeck A01199490
César Tadeo Bernal Sauceda A00841810
Regina Aguilar García A00841923

Fecha: 6/12/2025

Este archivo tiene como objetivo leer un archivo de bitácora, contar los accesos por IP y permitir consultas interactivas.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"

using namespace std;

// Función para extraer la IP de una línea de la bitácora
// Complejidad: O(1)
string extraerIP(string linea){
    string w1, s2, s3, ipPort;
    stringstream ss(linea);

    ss >> w1 >> s2 >> s3 >> ipPort;

    size_t pos = ipPort.find(':');
    return ipPort.substr(0, pos);
}

// Función principal
int main(){
    HashTable<int> ht;

    ifstream archivo("sorted_bitacora_EV5.txt");

    if(!archivo){
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;
    while(getline(archivo, linea)){
        if(linea.size() < 10) continue; // Evitar líneas demasiado cortas

        string ip = extraerIP(linea);

        int count = ht.search(ip);
        ht.insert(ip, count + 1);
    }
    archivo.close();
    
    cout << "Conteo de accesos por IP:" << endl;
    string consulta;
    while(true){ // Bucle de consulta interactiva
        cout << "Ingrese una IP para consultar (o 'salir' para terminar): ";
        cin >> consulta;
        if(consulta == "salir") break;

        int accesos = ht.search(consulta);
        if(accesos != 0){
            cout << "La IP " << consulta << " tiene " << accesos << " accesos." << endl;
        }else{
            cout << "La IP " << consulta << " no se encontró en el registro." << endl;
        }
    }
}