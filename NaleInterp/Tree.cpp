#include "Tree.h"

namespace Nale {
	template<class T>
	node<T>::node() {};

	template<class T>
	node<T>::node(T value, node<T>* parent) {
		this->parent = parent;
		this->value = value;
	}

	template<class T>
	node<T>::node(T value) {
		this->value = value;
	}

	template<class T>
	tree<T>::tree(node<T>* root) {
		this->root = root;
	}

	template<class T>
	void tree<T>::traverse(void (action)(node<T>*), node<T>* start) {
		for (int i = 0; i < start->children.size; i++) {
			action(start->children[i]);
			traverse(start->children[i]);
		}
	}
}