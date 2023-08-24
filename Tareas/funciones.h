// =========================================================
// Nombre: funciones.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 25/08/2023.
// =========================================================

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "funciones.h"
#include <iostream>

class Funciones {
    public:
    int sumaIterativa(int n);
    int sumaRecursiva(int n);
    int sumaDirecta(int n);
};

int Funciones::sumaIterativa(int n) {
	int cont = 0;
	for (int i = 0; n >= i; i++) {
		cont += i;
	}
	return cont;
}

int Funciones::sumaRecursiva(int n) {
    if (n == 0) return	0;
	else return n + sumaRecursiva(n-1);
}

int Funciones::sumaDirecta(int n) {
    int sumD = (n * (n + 1)) / 2;
    return sumD;
}

#endif
