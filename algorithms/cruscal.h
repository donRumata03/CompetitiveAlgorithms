//
// Created by Vova on 14.01.2021.
//

#pragma once

#include <data_structures/graphs.h>
#include <data_structures/DSU.h>

template<class WeightType>
std::vector<std::vector<std::pair<li, WeightType>>> cruscal_find_mst(const std::vector<std::vector<std::pair<li, WeightType>>>& graph) {
	li vertexes = graph.size();
	std::vector<base_edge<WeightType>> edge_list;

	/// Convert to edge_list:
	for (size_t i = 0; i < graph.size(); ++i) {
		for (size_t j = 0; j < graph[i].size(); ++j) {
			auto [to, weight] = graph[i][j];
			edge_list.push_back({ i, to, weight });
		}
	}

	/// Sort:
	std::sort(edge_list.begin(), edge_list.end(), [](auto first_edge, auto second_edge){ return first_edge.weight < second_edge.weight; });

	/// Find used edges:
	DSU dsu(vertexes);
	std::vector<base_edge<WeightType>> mst_edges;
	for (auto& edge : edge_list) {
		if (dsu.find(edge.first) != dsu.find(edge.second)) {
			dsu.unite(edge.first, edge.second);
			mst_edges.push_back(edge);
		}
	}

	/// Convert backwards:
	std::vector<std::vector<std::pair<li, WeightType>>> res(vertexes);
	for (auto& edge: mst_edges) {
		res[edge.first].push_back({ edge.second, edge.weight });
	}

	return res;
}
