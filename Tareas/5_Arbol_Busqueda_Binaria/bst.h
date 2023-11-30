// =========================================================
// Nombre: bst.h
// Autor: Axel Camacho Villafuerte.
// Fecha: 09/10/2023.
// =========================================================

#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

template <class T> class BST; //Adelantar declaracion de clase BST

template <class T>
class TreeNode {
	private:
		//Variables
		T value;
		TreeNode *left, *right;

	public:
		//Constructores
		TreeNode(T);
		TreeNode(T, TreeNode<T>*, TreeNode<T>*);

		//Metodos
		void add(T);
		bool find(T);
		void removeChilds();
		void ancestors(std::stringstream&, T) const;
		void inorder(std::stringstream&) const;
		void preorder(std::stringstream&) const;
		void postorder(std::stringstream&) const;
		void levelbylevel(std::stringstream&, int) const;

		//Definir clase TreeNode como amiga de la clase BST, para usar sus variables privadas
		friend class BST<T>; 
};

//Constructor de la clase TreeNode, recibe un valor y lo asigna al nodo, además de asignar los nodos izquierdo y derecho a nulptr.
template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0){}

//Constructor de la clase TreeNode, recibe un valor y dos nodos, asigna el valor al nodo, y asigna los nodos izquierdo y derecho a los nodos recibidos.
template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

//Método add, recibe un valor y lo agrega al árbol.
template <class T>
void TreeNode<T>::add(T val) {
	//If para saber Si el valor es menor al valor del nodo
	if (val < value) {
		//If para saber si el nodo izquierdo es diferente de nullptr
		if (left != 0) {
			left->add(val); //Recursión
		} else { //Si no, crea un nuevo nodo con el valor recibido
			left = new TreeNode<T>(val); //Asigna el nuevo nodo al nodo izquierdo
		}
	} else { //Si no, el valor es mayor al valor del nodo
		//If para saber si el nodo derecho es diferente de nullptr
		if (right != 0) { 
			right->add(val); //Recursión
		} else { //Si no, crea un nuevo nodo con el valor recibido
			right = new TreeNode<T>(val); //Asigna el nuevo nodo al nodo derecho
		}
	}
}

//Método find, recibe un valor y retorna true si el valor se encuentra en el árbol, false si no.
template <class T>
bool TreeNode<T>::find(T val) {
	//If caso bace para recursión
	if (val == value) {
		return true; //Si el valor es igual al valor del nodo, valor encontrado
	}
	else if (val < value) {
		return (left != 0 && left->find(val)); //Si el valor es menor al valor del nodo, busca en el hijo izquierdo
	}
	else if (val > value) {
		return (right != 0 && right->find(val)); //Si el valor es mayor al valor del nodo, busca en el hijo derecho
	}
	return false; //Si no se encuentra el valor, retorna false
}

//Método removeChilds, elimina todos los nodos hijos del nodo.
template <class T>
void TreeNode<T>::removeChilds() {
	//If para saber si el nodo izquierdo es diferente de nullptr
	if (left != 0) {
		left->removeChilds(); //Recursión.
		delete left; //Elimina el nodo izquierdo.
		left = 0; //Asigna el nodo izquierdo a nullptr.
	}
	//If para saber si el nodo derecho es diferente de nullptr
	if (right != 0) {
		right->removeChilds(); //Recursión.
		delete right; //Elimina el nodo derecho.
		right = 0; //Asigna el nodo derecho a nullptr.
	}
}

//Método auxiliar de ancestors, recibe un stringstream y un valor, y lo llena con los ancestros del valor en el árbol.
template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
	//If para saber si el valor es diferente al valor del nodo.
    if (value != val) {
		//If para saber si el stringstream esdta vacío.
        if (aux.tellp() != 1) {
            aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
        }
        aux << value; //Concatena el valor del nodo en el stringstream.

		//If para saber si el valor es menor al valor del nodo y si el nodo izquierdo es diferente de nullptr.
        if (val < value && left != nullptr) {
            left->ancestors(aux, val); //Recursión.
        }
		//If para saber si el valor es mayor al valor del nodo y si el nodo derecho es diferente de nullptr.
        if (val > value && right != nullptr) {
            right->ancestors(aux, val); //Recursión.
        }
    }
}

//Método auxiliar inorder, recorre el árbol deforma inorder transversal y retorna un stringstrem y lo llena con los valores del árbol en orden.
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	//If para saber si el nodo izquierdo es diferente de nullptr.
	if (left != 0) {
		left->inorder(aux); //Recursión.
	}
	//If para saber si el stringstream esdta vacío.
	if (aux.tellp() != 1) { //
		aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
	}
	aux << value; //Concatena el valor del nodo en el stringstream.
	//If para saber si el nodo derecho es diferente de nullptr.
	if (right != 0) {
		right->inorder(aux); //Recursión.
	}
}

//Método auxiliar preorder, recorre el árbol deforma preorder transversal y retorna un stringstrem y lo llena con los valores del árbol en orden.
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value; //Concatena el valor del nodo en el stringstream.
	//If para saber si el nodo izquierdo es diferente de nullptr.
	if (left != 0) {
		aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
		left->preorder(aux); //Recursión.
	}
	//If para saber si el nodo derecho es diferente de nullptr.
	if (right != 0) {
		aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
		right->preorder(aux); //Recursión.
	}
}

//Método auxiliar postorder, recorre el árbol deforma postorder transversal y retorna un stringstrem y lo llena con los valores del árbol en orden.
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	//If para saber si el nodo izquierdo es diferente de nullptr.
	if (left != 0) {
		left->postorder(aux); //Recursión.
	}
	//If para saber si el nodo derecho es diferente de nullptr.
	if (right != 0) {
		right->postorder(aux); //Recursión.
	}
	//If para saber si el stringstream esdta vacío.
	if (aux.tellp() != 1) {
		aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
	}
	aux << value; //Concatena el valor del nodo en el stringstream.
}

//Método auxiliar levelbylevel, recorre el árbol deforma levelbylevel transversal y retorna un stringstrem y lo llena con los valores del árbol en orden.
template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux, int level) const {
	//If para saber si el nivel es == 1.
    if (level == 1) {
		//If para saber si el stringstream esdta vacío.
		if (aux.tellp() != 1) {
			aux << " "; //Concatenar un espacio en el stringstream para pasar los test del main.
		}
        aux << value; //Concatena el valor del nodo en el stringstream.
    } 
	//Si level es > 1.
	else if (level > 1) {
		//If para saber si el nodo izquierdo es diferente de nullptr.
        if (left != 0) {
            left->levelbylevel(aux, level - 1); //Recursión.
        }
		//If para saber si el nodo derecho es diferente de nullptr.
        if (right != 0) {
            right->levelbylevel(aux, level - 1); //Recursión.
        }
    }
}

//Clase BST
template <class T>
class BST {
	private:
		//Variable
		TreeNode<T> *root;

	public:
		//Constructor
		BST();
		//Destructor
		~BST();

		//Metodos
		bool empty() const;
		void add(T);
		bool find(T) const;
		void removeAll();
		std::string preorder() const;
		std::string inorder() const;
		std::string postorder() const;
		std::string levelbylevelstring() const;
		std::string visit() const;
		int height() const;
		int heightAux(const TreeNode<T>*) const;
		std::string ancestors(T) const;
		int whatlevelamI(T) const;
		int whatlevelamIAux(TreeNode<T>*, T, int) const;
};

//Constructor de la clase BST, asigna el nodo raíz a nullptr.
template <class T>
BST<T>::BST() : root(0) {}

//Destructor de la clase BST, elimina todos los nodos del árbol.
template <class T>
BST<T>::~BST() {
	removeAll();
}

//Método removeAll, elimina todos los nodos del árbol.
template <class T>
void BST<T>::removeAll() {
	//If para saber si el nodo raíz es diferente de nullptr.
	if (root != 0) {
		root->removeChilds(); //Llama al método removeChilds del nodo raíz.
	}
	delete root; //Elimina el nodo raíz.
	root = 0; //Asigna el nodo raíz a nullptr.
}

//Método empty, retorna true si el árbol está vacío, false si no.
template <class T>
bool BST<T>::empty() const {
	return (root == 0); //Retorna true si el nodo raíz es igual a nullptr, false si no.
}

//Método add, recibe un valor y lo agrega al árbol.
template <class T>
void BST<T>::add(T val) {
	//If para saber si el nodo raíz es diferente de nullptr.
	if (root != 0) {
		//If para saber si el valor ya existe en el árbol.
		if (!root->find(val)) {
			root->add(val); //Llama al método add del nodo raíz.
		}
	}
	//Si no existe el nodo raíz.
	else {
		root = new TreeNode<T>(val); //Crea el nodo raíz con el valor recibido.
	}
}

//Método find, recibe un valor y retorna true si el valor se encuentra en el árbol, false si no.
template <class T>	
bool BST<T>::find(T val) const {
	//If para saber si el nodo raíz es diferente de nullptr.
	if (root != 0) {
		return root->find(val); //Llama al método find del nodo raíz.
	}
	//Si no el nodo raíz es == nullptr 
	else {
		return false; //Retorna false.
	}
}

//Método preorder, retorna un string con los valores del árbol en preorden.
template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux; //Crea un stringstream.

	//Concatena los valores del árbol en preorden en el stringstream, para pasar los teast del main.
	aux << "[";
	//If para saber si el árbol está vacío.
	if (!empty()) { 
		root->preorder(aux); //Llama al método preorder del nodo raíz, para recorrer el árbol en preorden.
	}
	aux << "]";
	return aux.str(); //Retorna el stringstream.
}

//Método inorder, recorre el árbol deforma inorder transversal y retorna un string con los valores del árbol en inorder.
template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux; //Crea un stringstream.

	//Concatena los valores del árbol en inorder en el stringstream, para pasar los teast del main.
	aux << "[";
	//If para saber si el árbol está vacío.
	if (!empty()) {
		root->inorder(aux); //Llama al método inorder del nodo raíz, para recorrer el árbol en inorder.
	}
	aux << "]";
	return aux.str(); //Retorna el stringstream.
}

//Método postorder, recorre el árbol deforma postorder transversal y retorna un string con los valores del árbol en postorder.
template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux; //Crea un stringstream.

	//Concatena los valores del árbol en postorder en el stringstream, para pasar los teast del main.
	aux << "[";
	//If para saber si el árbol está vacío.
	if (!empty()) {
		root->postorder(aux); //Llama al método postorder del nodo raíz, para recorrer el árbol en postorder.
	}
	aux << "]";
	return aux.str(); //Retorna el stringstream.
}

//Método levelbylevelstring, recorre el árbol deforma levelbylevel transversal y retorna un string con los valores del árbol en levelbylevel.
template <class T>
std::string BST<T>::levelbylevelstring() const {
	std::stringstream aux; //Crea un stringstream.
	int h = height(); //Obtiene la altura del árbol.

	aux << "[";
	//If para saber si el árbol está vacío.
	if (!empty()) {
		//Ciclo for para recorrer el árbol en levelbylevel y escalando la altura.
    	for (int i = 1; i <= h; i++) {
        	root->levelbylevel(aux, i); //Llama al método levelbylevel del nodo raíz, para recorrer el árbol en levelbylevel.
    	}
		
	}
	aux << "]";
	return aux.str(); //Retorna el stringstream.
}

//Método visit, recorre el árbol en preorden, inorden y postorden, y los concatena en un string para los teast del main.
template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux; //Crea un stringstream.

	aux << preorder() << "\n"; //Concatena el recorrido en preorden para los test del main.
	aux << inorder() << "\n"; //Concatena el recorrido en inorder para los test del main.
	aux << postorder() << "\n";	//Concatena el recorrido en postorden para los test del main.
	aux << levelbylevelstring(); //Concatena el recorrido en levelbylevel para los test del main.

	return aux.str(); //Retorna el stringstream.
}

//Método auxiliar heightAux, para obtener la altura del arbol, recibe un nodo y retorna la altura del árbol.
template <class T>
int BST<T>::heightAux(const TreeNode<T>* node) const {
	int lheight = 0, rheight = 0; //Variables para almacenar la altura de los subárboles izquierdo y derecho.

	//If para saber si el nodo es igual a nullptr.
    if (node == 0) {
        return 0;
    }
	//Si no, realiza la recursión. 
	else {
        lheight = heightAux(node->left); //Llama a la función recursiva para el subárbol izquierdo.
        rheight = heightAux(node->right); //Llama a la función recursiva para el subárbol derecho.
		//If para saber si la altura del subárbol izquierdo es mayor a la altura del subárbol derecho.
        if (lheight > rheight) {
            return(lheight + 1); //Retorna la altura del subárbol izquierdo.
        } 
		//Si no, retorna la altura del subárbol derecho.
		else {
            return(rheight + 1); //Retorna la altura del subárbol derecho.
        }
    }
}

//Método height, retorna la altura del árbol.
template <class T>
int BST<T>::height() const {
    return heightAux(root); //Llama a una función auxiliar para realizar la búsqueda recursiva.
}

//Método ancestors, recibe un valor y retorna los ancestros del valor en el árbol.
template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux; //Crea un stringstream.

	//If para saber si el árbol está vacío.
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val); //Llama al método ansestors del nodo raíz, para obtener el ansestro.
    aux << "]";
    return aux.str(); //Retorna el stringstream
}

//Metodo auxiliar para whatlevelamI, recibe un nodo, un valor y un nivel, y retorna el nivel en el que se encuentra el valor en el árbol.
template <class T>
int BST<T>::whatlevelamIAux(TreeNode<T>* node, T val, int level) const {
    if (node == 0) {
        return -1; // El valor no se encuentra en el árbol, retorna -1.
    }

	//If para saber si el valor es igual al valor del nodo
    if (val == node->value) {
        return level; // El valor se encuentra en este nivel.
    } else if (val < node->value) {
        return whatlevelamIAux(node->left, val, level + 1); // Busca en el subárbol izquierdo.
    } else {
        return whatlevelamIAux(node->right, val, level + 1); // Busca en el subárbol derecho.
    }
}

//Método whatlevelamI, recibe un valor y retorna el nivel en el que se encuentra el valor en el árbol.
template <class T>
int BST<T>::whatlevelamI(T val) const {
    return whatlevelamIAux(root, val, 1); //Llama a una función auxiliar para realizar la búsqueda recursiva.
}

#endif
