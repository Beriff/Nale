#pragma once
#include <vector>
namespace Nale {
	template<class T>
	class node {
	public:
		node();
		node(T value);
		node(T value, node<T>* parent);

		T value;
		node<T>* parent;
		std::vector<node<T>*> children;
	};

	template<class T>
	class tree {
		tree();
		tree(node<T>* root);
		void traverse(void (action)(node<T>*), node<T>* start);

		node<T>* root;
	};
}