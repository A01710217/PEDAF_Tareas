# PEDAF_Tareas.

# Correcciones realizadas:

# 7_Arbol_Desplegado_Splay_Tree.

#### En esta tarea de splay tree, del archivo main.cpp, tengo "fail" en el caso 5 y 6, casos que consultan el metodo inorder():

> 5.- esperada [15 7 10 16 17]
> 
>  programa [17 16 15 7 10]
> 
> fail

> 6.- esperada [15 7 10 17]
> 
>  programa [17 15 7 10]
> 
> fail

#### La retro sobre la tarea de Splay Tree, el error lo ponen en el find, pero creo que es un error del delete (igual esto no afecta por que solo pierdo un  punto). Ahora bien en la retro se coloca donde fallo mi codigo:

```
 add success
 add success
 add success
 find success
 find success
 find success
 find success
 find success
 find success
 remove success
 remove fail
 remove success
 remove success
 remove success
 remove success
```

#### Con esto dedusco que mi codigo tiene errores del remove, errores evidentes antes de hacer la entrega.

### Metodos anteriores:

#### Metodo remove() de la clase Node:
```
template <class T>
Node<T>* Node<T>::remove(T val) {
	if (val < value) {
		if (left == nullptr)
			return this;
		left = left->remove(val);
	} else if (val > value) {
		if (right == nullptr)
			return this;
		right = right->remove(val);
	} else {
		if (left == nullptr) {
			Node<T>* temp = right;
			delete this;
			return temp;
		} else if (right == nullptr) {
			Node<T>* temp = left;
			delete this;
			return temp;
		}

		Node<T>* temp = right;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		value = temp->value;
		right = right->remove(temp->value);
	}
	return this;
}
```

#### Metodo remove() de la clase SplayTree:

...

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
				succ->parent = 0;
				if(succ->left)
					succ->left->parent = succ;
				if(succ->right)
					succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

...
```

### Corrección:
