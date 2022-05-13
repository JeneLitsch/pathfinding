#include <iostream>
#include "minos/Graph.hxx"
#include "minos/dijkstra.hxx"


void print_path(const auto & path) {
	std::cout << "PATH: ";
	bool first = true;
	for(const auto & step : path) {
		if(!first) std::cout << "->";
		first = false;
		std::cout << "( " << step << " )";
	}
	std::cout << "\n";
}

int main() {
	minos::Graph graph;
	graph.insert("a", "b", 5);
	graph.insert("a", "c", 4);
	graph.insert("b", "d", 10);
	graph.insert("c", "d", 10);
	graph.insert("c", "e", 2);
	graph.insert("e", "d", 1);

	std::vector<std::string> path0 = minos::dijkstra_fast(graph, "a", "d");
	std::vector<std::string> path1 = minos::dijkstra_full(graph, "a", "d");
	print_path(path0);
	print_path(path1);

	return 0;
}
