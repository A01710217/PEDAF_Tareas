// =========================================================
// Nombre: sorts.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 07/09/2023.
// =========================================================

#ifndef SORTS_H
#define SORTS_H

#include <vector>

template <class T>
class Sorts {
    //Funciones axiliares
    private:
	    void intercambiar(std::vector<T>&, int, int);
	    void copiarArreglo(std::vector<T>&, std::vector<T>&, int, int);
	    void combinarArreglo(std::vector<T>&, std::vector<T>&, int, int, int);
	    void combinardivicion(std::vector<T>&, std::vector<T>&, int, int);
		int bs_aux(std::vector<T> &, int, int, int);
    public:
        std::vector<T> ordenaSeleccion(std::vector<T> &);
        std::vector<T> ordenaBurbuja(std::vector<T> &);
        std::vector<T> ordenaMerge(std::vector<T> &);
        int busqSecuencial(const std::vector<T> &, const T &);
        T busqBinaria(const std::vector<T> &, int);
};

template <class T>
void Sorts<T>::intercambiar(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &prueba) {
	int pos;

	for (int i = prueba.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (prueba[j] > prueba[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			intercambiar(prueba, i, pos);
		}
	}
	return prueba;
}

template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T> &prueba) {
    //std::vector<T> v(prueba);
	for (int i = prueba.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (prueba[j] > prueba[j + 1]) {
				intercambiar(prueba, j, j + 1);
			}
		}
	}

    return prueba;
}

//Metodo adaptado de la clase
template <class T>
void Sorts<T>::copiarArreglo(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::combinarArreglo(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}	
}

template <class T>
void Sorts<T>::combinardivicion(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	combinardivicion(A, B, low, mid);
	combinardivicion(A, B, mid + 1, high);
	combinarArreglo(A, B, low, mid, high);
	copiarArreglo(A, B, low, high);
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &prueba) {
	std::vector<T> tmp(prueba.size());

	combinardivicion(prueba, tmp, 0, prueba.size() - 1);
	return prueba;
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &prueba, const T &val){
	int mid;
	int low = 0;
	int high = prueba.size() - 1;

	while (low <= high) {
		mid = (high + low) / 2;
		if (val == prueba[mid]) return mid;
		else if (val < prueba[mid]) high = mid - 1;
		else if (val > prueba[mid]) low = mid + 1;
	}
	if (prueba[low]==val) return low;
	else return -1;
}

template <class T>
int Sorts<T>::bs_aux(std::vector<T> &v, int low, int high, int val) {
	int mid;

	if (low < high) {
		mid = (high + low) / 2;
		if (val == v[mid]) return mid;
		else if (val < v[mid]) return bs_aux(v, low, high - 1, val);
		else if (val > v[mid]) return bs_aux(v, low + 1, high, val);
 	}
	return -1;
}

template <class T>
T Sorts<T>::busqBinaria(const std::vector<T> &prueba, int val) {
	std::vector<T> v(prueba);
	return bs_aux(v, 0, v.size() - 1, val);
}

#endif
