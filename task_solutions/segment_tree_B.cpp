//
// Created by Vova on 22.11.2020.
//

////////			Olymp functions		////////

//
// Created by Vova on 22.11.2020.
//

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <utility>
#include <fstream>


template<class FirstT, class SecondT>
std::ostream& operator << (std::ostream& os, const std::pair<FirstT, SecondT>& pair) {
	os << "(" << pair.first << ", " << pair.second << ")";

	return os;
}


template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vector) {
	for (auto& v: vector) os << v << " ";

	return os;
}


////////			Segment tree		////////

//
// Created by Vova on 22.11.2020.
//

using li = long long int;



template<class T, class BaseOperation>
class SegmentTree
{
public:
	SegmentTree() = delete;
	explicit SegmentTree(const std::vector<T>& initial_data);

	T compute(li l, li r); // sum of array[l, r)
	T get(li index) { return get(0, 0, n, index); }
	void set(li index, const T& value) { set(0, 0, n, index, value); }

private:
// API:
	li left_child(li v) { return v * 2 + 1; }
	li right_child(li v) { return v * 2 + 2; }
	void update_value(li v) { tree[v] = BaseOperation::compute(tree[left_child(v)], tree[right_child(v)]); }


	void build (const std::vector<T>& initial_data, li v, li left_responsibility, li right_responsibility);
	T compute (li v, li left_responsibility, li right_responsibility, li l, li r);

	T get(li v, li left_responsibility, li right_responsibility, li index);
	void set(li v, li left_responsibility, li right_responsibility, li index, const T& value);


private: // data
	li n;
	std::vector<T> tree;
	// std::vector<T> additions;
};


/**
 * Segment Tree Method Implementations
 */

template <class T, class BaseOperation>
SegmentTree<T, BaseOperation>::SegmentTree (const std::vector<T>& initial_data) : n(initial_data.size())
{
	tree.assign(n * 4, BaseOperation::default_value());

	build(initial_data, 0, 0, n);

	// std::cout << tree << std::endl;
}

template <class T, class BaseOperation>
void SegmentTree<T, BaseOperation>::build (const std::vector<T>& initial_data, li v, li left_responsibility,
                                           li right_responsibility)
{
	// std::cout << "Vertex: " << v
	// 	<< " : [" << left_responsibility << "; " << right_responsibility << ")"
	// << std::endl;

	if (left_responsibility + 1 == right_responsibility) {
		tree[v] = initial_data[left_responsibility];
	}
	else {
		li mid = (left_responsibility + right_responsibility) / 2;

		build(initial_data, left_child(v), left_responsibility, mid);
		build(initial_data, right_child(v), mid, right_responsibility);

		// tree[v] = tree[left_child(v)] + tree[right_child(v)]; // TODO: something else (max, min, sum depending on the BaseOperation!
		update_value(v);
	}
}

template <class T, class BaseOperation>
T SegmentTree<T, BaseOperation>::compute (li l, li r)
{
	return compute(0, 0, n, l, r);
}

template <class T, class BaseOperation>
T SegmentTree<T, BaseOperation>::compute (li v, li left_responsibility, li right_responsibility, li l, li r)
{
	if (l >= r) return BaseOperation::default_value();

	assert(l >= left_responsibility && l <= right_responsibility);
	assert(r >= left_responsibility && r <= right_responsibility);

	if (l == left_responsibility && r == right_responsibility) {
		return tree[v];
	}

	li mid = (left_responsibility + right_responsibility) / 2;

	// If it's fully covered by the left child:
	if (r <= mid) { // [l, r) is in [left_responsibility, mid)
		return compute(left_child(v), left_responsibility, mid, l, r);
	}
	// If it's fully covered by the right child:
	if (l >= mid) { // [l, r) is in [left_responsibility, mid)
		return compute(right_child(v), mid, right_responsibility, l, r);
	}

	// Divide the segment into two parts:
	return
			BaseOperation::compute(
					compute(left_child(v), left_responsibility, mid, l, mid),
					compute(right_child(v), mid, right_responsibility, mid, r)
			);
}

template <class T, class BaseOperation>
T SegmentTree<T, BaseOperation>::get (li v, li left_responsibility, li right_responsibility, li index)
{
	if (left_responsibility + 1 == right_responsibility) {
		assert(left_responsibility == index);
		return tree[v];
	}

	li mid = (left_responsibility + right_responsibility) / 2;

	if (index < mid) return get(left_child(v), left_responsibility, mid, index);
	return get(right_child(v), mid, right_responsibility, index);
}

template <class T, class BaseOperation>
void SegmentTree<T, BaseOperation>::set (li v, li left_responsibility, li right_responsibility, li index, const T& value)
{
	if (left_responsibility + 1 == right_responsibility) {
		assert(left_responsibility == index);
		tree[v] = value;
	}
	else {
		li mid = (left_responsibility + right_responsibility) / 2;

		if (index < mid) {
			set(left_child(v), left_responsibility, mid, index, value);
		}
		else {
			set(right_child(v), mid, right_responsibility, index, value);
		}
		update_value(v);
	}
}




/**
 * Operation Templates
 */

template<class T>
struct SumOperation {
	static T compute(const T& v1, const T& v2) {
		return v1 + v2;
	}

	static T default_value() {
		return T{}; // also T(0)
	}
};

template<class T>
struct MaxOperation {
	static T compute(const T& v1, const T& v2) {
		return std::max(v1, v2);
	}

	static T default_value() {
		return std::numeric_limits<T>::min();
	}
};

template<class T>
struct MinOperation {
	static T compute(const T& v1, const T& v2) {
		return std::min(v1, v2);
	}

	static T default_value() {
		return std::numeric_limits<T>::max();
	}
};


/**
 * Segment Tree aliases
 */

template<class T>
using SumSegmentTree = SegmentTree<T, SumOperation<T>>;

template<class T>
using MaxSegmentTree = SegmentTree<T, MaxOperation<T>>;

template<class T>
using MinSegmentTree = SegmentTree<T, MinOperation<T>>;





/////////////////////////////////////////////////////////////
///				The actual solution				/////////////
/////////////////////////////////////////////////////////////

constexpr li max_n = 1e5 + 2;

int main()
{
	std::ifstream in("rvq.in");
	std::ofstream out("rvq.out");

	assert(in.is_open());
	assert(out.is_open());

	std::vector<li> arr(max_n);
	li arr_index = 0;
	std::generate(arr.begin(), arr.end(), [&arr_index](){
		li this_n = arr_index + 1;
		arr_index++;
		return (this_n * this_n) % 12345 + (this_n * this_n * this_n) % 23456;
	});

	// std::cout << std::vector<li>(arr.begin(), arr.begin() + 100) << std::endl;

	MaxSegmentTree<li> max_tree(arr);
	MinSegmentTree<li> min_tree(arr);

	li k;
	in >> k;

	for (size_t i = 0; i < k; ++i) {
		li first, second;
		in >> first >> second;

		if (first > 0) {
			li index_first = first - 1;
			li index_second = second;

			auto max_val = max_tree.compute(index_first, index_second);
			auto min_val = min_tree.compute(index_first, index_second);

			out << (max_val - min_val) << std::endl;
		}
		else {
			li index = -first - 1;

			max_tree.set(index, second);
			min_tree.set(index, second);
		}
	}
}