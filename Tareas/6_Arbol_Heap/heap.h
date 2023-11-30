// =========================================================
// Nombre: heap.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 29/10/2023.
// =========================================================

#ifndef HEAP_H
#define HEAP_H

template <class T>
class Heap {
    private:
	    T *data; //Arbol heap
        unsigned int heapSize; //Tamaño del heap
        unsigned int count; //Contador de elementos

        //Metodos vistos en clase
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);

    public:
        //Constructor
        Heap(unsigned int) ;
        //Destructor
        ~Heap();

        //Metodos vistos en clase
        bool empty() const; //Metodo empty() para saber si el heap esta vacio
        bool full() const; //Metodo full() para saber si el heap esta lleno
        void clear(); //Metodo clear() para limpiar el heap
        
        //Metdos de la tarea
        void push(T);
        void pop();
        T top() const;
        unsigned int size() const;
        
        //Metodo toString() para compatibilidad con el main
        std::string toString() const;

};

//Constructor de la clase Heap
template <class T>
Heap<T>::Heap(unsigned int sze)  {
    //Inicializar el arreglo
    heapSize = sze;
    data = new T[heapSize];
    count = 0;
}

//Descrutor de la clase Heap
template <class T>
Heap<T>::~Heap() {
    //Borrar
    delete [] data;
    data = 0;
    heapSize = 0;
    count = 0;
}

//Metodo empty() para saber si el heap esta vacio
template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

//Metodo full() para saber si el heap esta lleno
template <class T>
bool Heap<T>::full() const {
    return (count == heapSize);
}

//Metodo clear() para limpiar el heap
template <class T>
void Heap<T>::clear() {
    count = 0;
}

//Metodos parent() para obtener el padre de un nodo
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return ((pos - 1) / 2);
}

//Metdo left() para obtener el hijo izquierdo de un nodo
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return ((2 * pos) + 1);
}

//Metodo right() para obtener el hijo derecho de un nodo
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return ((2 * pos) + 2);
}

//Metodo swap() para intercambiar dos nodos
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

//Metodo heapify() para ordenar el heap
template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;

    if (le <= count && data[le] < data[min]) {
        min = le;
    }
    if (ri <= count && data[ri] < data[min]) {
        min = ri;
    }
    if (min != pos) {
        swap(pos, min);
        heapify(min);
    }
}

//Metodo push() para insertar un elemento en el heap
template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

//Metodo pop() para eliminar un elemento del heap
template <class T>
void Heap<T>::pop()  {
    T aux;

    aux = data[0];
    data[0] = data[--count]; //Se decrementa el contador
    //Nota: --count es igual a count = count - 1, pero ese count se le resta antes de usarlo
    heapify(0);
}

//Metodo top() para obtener el elemento de la cima del heap
template <class T>
T Heap<T>::top() const {
    return data[0];
}

//Metodo size() para obtener el tamaño del heap
template <class T>
unsigned int Heap<T>::size() const {
    return count;
}

//Metodo para compatibilidad con el main
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";	
    
    for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} 
        aux << data[i];
	} 
    
    aux << "]";
	return aux.str();
}

#endif
