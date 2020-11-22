//
// Created by Vova on 22.11.2020.
//

#pragma once

#include <vector>

using li = long long int;



template<class T, class BaseOperation>
class SegmentTree
{
public:
	SegmentTree() = delete;
	SegmentTree(const std::vector<T>& initial_data);

private:
	li left_child(li v) { return v * 2; }
	void right_child(size_t v);


	void build(const std::vector<T>& initial_data);

private: // data
	std::vector<T> tree;
	// std::vector<T> additions;
};

template <class T, class BaseOperation>
SegmentTree<T, BaseOperation>::SegmentTree (const std::vector<T>& initial_data)
{

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


