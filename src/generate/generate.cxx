#include "generate.hxx"
#include <random>

stx::grid2<int> generate(std::int64_t seed, stx::size2u size) {
	stx::grid2<int> graph{size, 0};
	std::mt19937_64 rng(seed);
	for(int & point : graph) {
		int value = rng() % 16;
		if(value == 0) {
			point = 10000;
		}
		else {
			point = value;
		}
	}
	return graph;
}