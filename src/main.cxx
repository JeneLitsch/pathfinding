#include <iostream>
#include "pathfinding/dijkstra.hxx"
#include "pathfinding/a_star.hxx"
#include "generate/generate.hxx"


void print_path(const std::vector<stx::vector2i> & path) {
	std::cout << "PATH: ";
	bool first = true;
	for(const auto & step : path) {
		if(!first) std::cout << "->";
		first = false;
		std::cout << step;
	}
	std::cout << "\n";
}

int main() {
	const auto size = stx::size2u{100, 100};
	const auto start = stx::vector2i{0, 0};
	const auto goal = stx::vector2i{size} - stx::vector2i{1,1};

	const auto graph = generate(1337, size);

	const auto path0 = dijkstra(graph, start, goal);
	print_path(path0);
	const auto path1 = a_star(graph, start, goal);
	print_path(path1);

	return 0;
}
