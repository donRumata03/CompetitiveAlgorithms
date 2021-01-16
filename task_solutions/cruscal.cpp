//
// Created by Vova on 16.01.2021.
//

/// Olymp_func:

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <utility>
#include <fstream>

#include <unordered_set>
#include <unordered_map>


using li = long long int;


template<class FirstT, class SecondT>
std::ostream& operator << (std::ostream& os, const std::pair<FirstT, SecondT>& pair) {
	os << "(" << pair.first << ", " << pair.second << ")";

	return os;
}


template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vector) {
	// for (auto& v: vector) os << v << " ";
	for (size_t i = 0; i < vector.size(); ++i) {
		os << vector[i];
		if (i != vector.size() - 1) os << " ";
	}

	return os;
}

/// DSU:

class DSU {
	std::vector<li> sizes;
	mutable std::vector<li> data;
	li n = 0;

public:
	DSU() = default;
	explicit DSU(li _n) : n(_n), data(_n), sizes(_n, 1) {
		std::iota(data.begin(), data.end(), 0);
	}

	[[nodiscard]] li size() const { return n; }

	/**
	 * @returns the index of element representing the set of the element
	 */
	li find(li element) const {
		if (data[element] == element) return element;

		return data[element] = find(data[element]);
	}

	/**
	 * unites sets in which the elements are situated
	 * @returns the resultant set representation element index
	 */
	li unite(li first, li second) {
		first = find(first);
		second = find(second);

		if (first == second) return first;

		// add second to first, first should be bigger of equal:
		if (sizes[first] < sizes[second]) std::swap(first, second);

		data[second] = first;
		sizes[first] += sizes[second];

		return first;
	}

	/**
	 * Makes a new set with root of the vertex at «index»
	 * BREAKS SIZE HEURISTIC!
	 */
	void make_set(li index) {
		data[index] = index;
		sizes[index] = 1;
	}


	std::vector<std::vector<li>> dump_sets() const {
		std::vector<std::vector<li>> res;

		auto set_indexes_set = std::unordered_set<li>(data.begin(), data.end());
		li set_number = set_indexes_set.size();
		// std::cout << "Different sets found: " << set_number << std::endl;

		res.resize(set_number);

		// Enumerate sets:
		std::unordered_map<li, li> set_repersentor_to_index_converter;
		set_repersentor_to_index_converter.reserve(set_number);

		li this_set_index = 0;
		for (auto& it : set_indexes_set) {
			set_repersentor_to_index_converter[it] = this_set_index;
			this_set_index++;
		}

		// for(auto& it : set_repersentor_to_index_converter) std::cout << it << std::endl;

		for (li i = 0; i < n; ++i) {
			auto set_representor = find(i);
			auto new_set_index = set_repersentor_to_index_converter[set_representor];
			res[new_set_index].push_back(i);
		}

		return res;
	}


	// ________________________________
	friend void output_dsu(const DSU&);
};



/// Graphs:
template<class Weight>
struct base_edge {
	li first = -1;
	li second = -1;

	Weight weight = 1;

	base_edge(li _first, li _second, Weight _weight) : first(_first), second(_second), weight(_weight) {}
};

using int_edge = base_edge<li>;
using float_edge = base_edge<double>;


/// Cruscal:
template<class WeightType>
std::vector<base_edge<WeightType>> cruscal_find_mst(const std::vector<std::vector<std::pair<li, WeightType>>>& graph) {
	li vertexes = graph.size();
	std::vector<base_edge<WeightType>> edge_list;

	/// Convert to edge_list:
	for (li i = 0; i < graph.size(); ++i) {
		for (li j = 0; j < graph[i].size(); ++j) {
			auto to = graph[i][j].first;
			auto weight = graph[i][j].second;
			edge_list.push_back(base_edge<WeightType>{i, to, weight});
		}
	}

	/// Sort:
	std::sort(edge_list.begin(), edge_list.end(), [](base_edge<WeightType> first_edge, base_edge<WeightType> second_edge){ return first_edge.weight < second_edge.weight; });

	/// Find used edges:
	DSU dsu(vertexes);
	std::vector<base_edge<WeightType>> mst_edges;
	for (auto& edge : edge_list) {
		if (dsu.find(edge.first) != dsu.find(edge.second)) {
			dsu.unite(edge.first, edge.second);
			mst_edges.push_back(edge);
		}
	}

//	/// Convert backwards:
//	std::vector<std::vector<std::pair<li, WeightType>>> res(vertexes);
//	for (auto& edge: mst_edges) {
//		res[edge.first].push_back({ edge.second, edge.weight });
//	}

	return mst_edges;
}


/// Connection:
template<class WeightType>
void connected_dfs(li v, std::vector<bool>& mark, const std::vector<std::vector<std::pair<li, WeightType>>>& graph) {
	mark[v] = true;

	for(auto p : graph[v]) {
		// auto[new_v, w] = p;
		auto new_v = p.first;
		auto w = p.second;
		if (!mark[new_v]) {
			connected_dfs(new_v, mark, graph);
		}
	}
}

template<class WeightType>
bool is_connected(const std::vector<std::vector<std::pair<li, WeightType>>>& graph) {
	li n = graph.size();
	std::vector<bool> mark(n, false);

	// DFS from the first vertex:
	connected_dfs(0, mark, graph);

	return std::all_of(mark.begin(), mark.end(), [](bool val){ return val; });
}


int main() {
	li n, m;

	std::cin >> n >> m;

	std::vector<std::vector<std::pair<li, li>>> graph(n);
	for (size_t i = 0; i < m; ++i) {
		li from, to, weight;
		std::cin >> from >> to >> weight;

		graph[from].emplace_back( to, weight );
		graph[to].emplace_back( from, weight );
	}

	auto graph_is_connected = is_connected(graph);
	if (!graph_is_connected) {
		std::cout << "NON-CONNECTED" << std::endl;
		return 0;
	}

	li weight_sum = 0;
	for (auto& edge : cruscal_find_mst(graph)) {
		weight_sum += edge.weight;
	}
	std::cout << weight_sum << std::endl;

	return 0;
}


/*

 >>> 5 7
1 2 5
1 3 2
2 3 4
2 4 3
3 4 6
0 3 20
0 4 10

>>> 19

 */
