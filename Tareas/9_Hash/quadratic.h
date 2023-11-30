// =========================================================
// Nombre: quadratic.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 22/11/2023.
// =========================================================

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
	private:
		unsigned int (*func)(const Key);
		unsigned int size;
		unsigned int count;

		Key *keys;
		Key initialValue;
		Value *values;

		long indexOf(const Key) const;

	public:
		//Constructor
		Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
		//Destructor
		~Quadratic();

		//Métodos
		void clear();

		bool full() const;
		bool put(Key, Value);
		Value get(const Key);

		std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)) {
	size = sze;
	keys = new Key[size];

	if (keys == 0) {
		return;
	}

	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];

	if (values == 0) {
		return;
	}

	for (int i = 0; i  < sze; i++){
        values[i] = 0;
    }

	func = f;
	count = 0;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete[] keys;
	keys = nullptr;
	delete[] values;
	values = nullptr;
	size = 0;
	func = nullptr;
	count = 0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;

	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	} while (start != i);
	return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start, c = 1;
	long pos;

	if (full()) {
		return false;
	}

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}

	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return true;
		}
        i = (start + c * c) % size;
        c++;
	} while (start != i);
	return false;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
	long pos = indexOf(k);

	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
		if(keys[i] != initialValue)
			aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
	}

	return aux.str();
}

#endif
