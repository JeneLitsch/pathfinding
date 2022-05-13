#pragma once
#include "Graph.hxx"

namespace minos {
	std::vector<std::string> dijkstra_fast(
		const Graph & graph,
		const std::string & start,
		const std::string & end);

	std::vector<std::string> dijkstra_full(
		const Graph & graph,
		const std::string & start,
		const std::string & end);
}