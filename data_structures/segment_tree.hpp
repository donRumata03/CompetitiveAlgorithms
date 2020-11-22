//
// Created by Vova on 22.11.2020.
//

#pragma once

#include "olymp_funcions.hpp"

using li = long long int;



template<class T, class BaseOperation>
class SegmentTree
{
public:
	SegmentTree() = delete;
	SegmentTree(const std::vector<T>& initial_data);

private:
	li left_child(li v) { return v * 2 + 1; }
	li right_child(li v) { return v * 2 + 2; }


	void build (const std::vector<T>& initial_data, li v, li left_responsibility, li right_responsibility);

private: // data
	std::vector<T> tree;
	// std::vector<T> additions;
};


/**
 * Segment Tree Method Implementations
 */

template <class T, class BaseOperation>
SegmentTree<T, BaseOperation>::SegmentTree (const std::vector<T>& initial_data)
{
	tree.resize(initial_data.size() * 4);

	build(initial_data, 0, 0, initial_data.size());

	// for (auto& t : tree) std::cout << t << " ";
	// std::cout << std::endl;
	std::cout << tree << std::endl;
}

template <class T, class BaseOperation>
void SegmentTree<T, BaseOperation>::build (const std::vector<T>& initial_data, li v, li left_responsibility,
                                           li right_responsibility)
{
	std::cout << "Vertex: " << v <<
	// << " left range: " << left_responsibility << " right range: " << right_responsibility <<
	" : [" << left_responsibility << "; " << right_responsibility << ")"
	<< std::endl;

	if (left_responsibility + 1 == right_responsibility) {
		tree[v] = initial_data[left_responsibility];
	}
	else {
		li mid = (left_responsibility + right_responsibility) / 2;

		build(initial_data, left_child(v), left_responsibility, mid);
		build(initial_data, right_child(v), mid, right_responsibility);

		tree[v] = tree[left_child(v)] + tree[right_child(v)]; // TODO: something else (max, min, sum depending on the BaseOperation!
	}
}


/**
 * Operation Templates
 */

template<class T>
struct SumOperation {
	static void compute() {

	}
};


/**
 * Segment Tree aliases
 */
template<class T>
using SumSegmentTree = SegmentTree<T, SumOperation<T>>;


