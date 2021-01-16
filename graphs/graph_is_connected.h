//
// Created by Vova on 16.01.2021.
//

#pragma once


#include <olymp_functions.hpp>
#include <data_structures/graphs.h>

template<class WeightType>
void connected_dfs(li v, std::vector<bool>& mark, const std::vector<std::vector<std::pair<li, WeightType>>>& graph) {
	mark[v] = true;

	for(auto p : graph[v]) {
		auto[new_v, w] = p;
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
