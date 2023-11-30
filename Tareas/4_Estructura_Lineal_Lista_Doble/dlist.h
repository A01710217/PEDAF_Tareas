// =========================================================
// Nombre: dlist.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 28/09/2023.
// =========================================================

#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

template <class T> class DList; //Adelantar declaracion de clase DList

template <class T>
class DLink {
private:
	//Constructores
	DLink(T); //Constructor por defecto
	DLink(T, DLink<T>*, DLink<T>*); //Constructor con parametros
	DLink(const DLink<T>&); //Constructor por copia

	//Variables
	T value; //Valor del nodo
	DLink<T> *previous; //Apuntador al elemento anterior
	DLink<T> *next; //Apuntador al elemento siguiente

	//Definir clase DList como amiga de la clase DLink, para usar sus variables privadas
	friend class DList<T>; 
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(nullptr), next(nullptr) {} //Constructor por defecto, inicializa los apuntadores en nullptr

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {} //Constructor con parametros, inicializa los apuntadores 

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {} //Constructor por copia, inicializa los apuntadores

template <class T>
class DList {
	private:
		//Variables
        DLink<T> *head; //Apuntador al primer elemento
	    DLink<T> *tail; //Apuntador al ultimo elemento
	    int size; //Tamaño de la lista

    public:
		//Constructor
		DList(); //Constructor por defecto
	    DList(const DList<T>&); //Constructor por copia
	    //Destructor
        ~DList();
		//Metodos
        bool empty() const; //Metodo empty() para saber si la lista está vacía
        void clear(); //Metodo clear() para borrar la lista
		
		void insertion(T); //Metodo insertion() para insertar un elemento
        T search(T); //Devuelve el indice del elemento buscado
    	void update(int, T); //Metodo update() para actualizar un elemento
    	void deleteAt(int); //Metodo deleteAt() para borrar un elemento

		std::string toStringForward() const; //Metodo toStringForward() para imprimir la lista de forma normal
        std::string toStringBackward() const; //Metodo toStringBackward() para imprimir la lista de forma inversa
};

template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr) {}

template <class T>
DList<T>::DList(const DList<T> &source) : head(nullptr), tail(nullptr) {
	//Punteros auxiliares
	DLink<T> *p, *q; 

	//Si la lista está vacía, inicializa los apuntadores en nullptr
	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} 
	else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
DList<T>::~DList() {
	clear();
}

//Metodo clear() visto en clase
template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

//Metodo empty() para saber si la lista está vacía
template <class T>
bool DList<T>::empty() const {
	return (head == 0);
}

template <class T>
void DList<T>::insertion(T val) {
	//Creamos un nuevo nodo
	DLink<T> *newLink = new DLink<T>(val);

	//If que evalua si la lista está vacía, si lo esta == head y tail a newLink
	if (empty()) {
		head = newLink;
		tail = newLink;
	} 
	else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
T DList<T>::search(T val) {
	//Creamos un puntero auxiliar para recorrer la lista
	DLink<T> *current = head;
	int index = 0;
	
	//Ciclo while para recorrer la lista
	while (current) {
		if (current->value == val) {
			return index;
		}
		current = current->next;
		index++;
	}
	//Si no encuentra el valor, devuelve -1
	return -1;
}

template <class T>
void DList<T>::update(int index, T val) {
    //Creamos un puntero auxiliar para recorrer la lista
    DLink<T> *current = head;

    //Mediante un cilco for, recorremos hasta llegar al índice deseado
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    //Actualizamos el valor en el índice dado
    current->value = val;
}

template <class T>
void DList<T>::deleteAt(int index) {
	//Variables auxiliares
    int pos;
    DLink<T> *p;

    //Si el índice es el primero
    if (index == 0) {
        p = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } 
		else {
            head = p->next;
            p->next->previous = nullptr;
        }
        delete p;
        size--;
        return;
    }

    //Variables auxiliares, para no modificar originales
    p = head; //Apuntador
    pos = 0;  //Iterador para saber dónde estamos

    //Recorremos hasta encontrar el índice que buscamos
    while (pos != index) {
        p = p->next;
        pos++;
    }

    p->previous->next = p->next; //Así como sus direcciones

    //Si no es el último elemento de la lista, modifica los apuntadores
    if (p->next != nullptr) {
        p->next->previous = p->previous;
    }

    //Reducimos el tamaño y borramos el objeto
    size--;
    delete p;
}

/* Metodos para hacer compatible el main */
//Metodos dados por el profesor

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif
