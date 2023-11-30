// =========================================================
// Nombre: list.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 24/09/2023.
// =========================================================

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <sstream>

template <class T> class List; //Adelantar declaracion de clase List

template <class T>
class Link {
	private:
		//Variables
    	T value;
    	Link<T>* next;

		//Constructores
		Link(T);
		//Definir clase link como amiga de la clase List
		friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(nullptr) {}

template <class T>
class List {
	private:
		//Variables
		Link<T> *head;

    public:
		//Constructor
		List();
		//Destructor
        ~List();
		//Metodos
        bool empty() const; //Metodo empty() para saber si la lista está vacía
        void clear(); //Metodo clear() para borrar la lista

		void insertion(T); //Metodo insertion() para insertar un elemento
		T search(T); //Devuelve el indice del elemento buscado
    	void update(int, T); //Metodo update() para actualizar un elemento
    	void deleteAt(int); //Metodo deleteAt() para borrar un elemento
		
		std::string toString() const; //Metodo toString() para convertir la lista en string
};

template <class T>
List<T>::List() : head(nullptr) {}

template <class T>
List<T>::~List() {
	clear();
}

//Metodo clear() visto en clase
template <class T>
void List<T>::clear() {
	//Creamos dos punteros auxiliares
	Link<T> *p, *q;

	//Inicializamos p con el valor de head
	p = head;
	//Ciloc while para recorrer la lista y borrar los nodos
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	//Asignamos el valor de head a nullptr
	head = 0;
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
void List<T>::insertion(T val) {
	//Creamos un nuevo nodo
    Link<T>* newVal = new Link<T>(val);

    if (head == 0) {
        head = newVal;
    } else {
        Link<T>* current = head;
        while (current->next != 0) {
            current = current->next;
        }
        current->next = newVal;
    }
}

template <class T>
T List<T>::search(T val) {
	Link<T> *current = head;
	int index = 0;
	while (current) {
		if (current->value == val) {
			return index;
		}
		current = current->next;
		index++;
	}
	return -1;
}

template <class T>
void List<T>::update(int index, T val) {
    //Creamos un puntero auxiliar para recorrer la lista
    Link<T> *current = head;

    //Mediante un cilco for, recorremos hasta llegar al índice deseado
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    //Actualizamos el valor en el índice dado
    current->value = val;
}

template <class T>
void List<T>::deleteAt(int index) {
    if (index == 0) {
        Link<T> *temp = head;
        head = head->next;
        delete temp;
    } else {
        Link<T> *current = head;
        int currentIndex = 0;
        while (current) {
            if (currentIndex == index - 1) {
                Link<T> *temp = current->next;
                current->next = temp->next;
                delete temp;
            }
            current = current->next;
            currentIndex++;
        }
    }
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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

#endif
