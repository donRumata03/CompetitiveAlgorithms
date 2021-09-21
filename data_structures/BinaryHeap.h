//
// Created by Vova on 21.09.2021.
//

#pragma once

#include "olymp_functions.hpp"

template <class T, class Relation>
class BinaryHeap
{
public:
	static li get_left_child(li node_index) { return node_index * 2 + 1; }
	static li get_right_child(li node_index) { return node_index * 2 + 2; }

	static li get_parent(li node_index) {
		return (node_index - 1) / 2;
	}

private:
	std::vector<T> m_array;

	bool has_left_child(li node_index) {
		return get_left_child(node_index) < m_array.size();
	}
	bool has_right_child(li node_index) {
		return get_right_child(node_index) < m_array.size();
	}

public:
	BinaryHeap() {}

	void insert(const T& element) {
		m_array.push_back(element);

		// Sift up:
		li newbie_index = m_array.size() - 1;
		while (newbie_index != 0 and m_array[get_parent(newbie_index)] > m_array[newbie_index]) {
			std::swap(m_array[newbie_index], m_array[get_parent(newbie_index)]);
			newbie_index = get_parent(newbie_index);
		}
	}

	const T& get_front() {
		assert(not m_array.empty());

		return m_array.front();
	}

	T pop_front() {
		T old_front = get_front();
		m_array.front() = m_array.back();
		m_array.pop_back();

		// Sift down (now first element can be too «big»!):

	}
};


