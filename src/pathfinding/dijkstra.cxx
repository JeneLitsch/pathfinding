#include "dijkstra.hxx"
#include <queue>
#include <iostream>
#include "stdxx/algorithm.hxx"

namespace {
	struct Entry {
		stx::vector2i at;
		std::optional<stx::vector2i> prev;
		// nullopt means infinite
		std::int64_t cost;

		friend bool operator<(const Entry & l, const Entry & r) {
			return l.cost < r.cost;
		}

		static Entry start(const stx::vector2i & at) {
			return Entry{at, std::nullopt, 0};
		}

		static Entry unknown(const stx::vector2i & at) {
			return Entry{at, std::nullopt, infinite};
		}
	};
}



std::vector<stx::vector2i> dijkstra(
	const stx::grid2<int> & graph,
	const stx::vector2i & s,
	const stx::vector2i & e) {
	
	std::vector<Entry> list = init_entries<Entry>(graph, s);
	auto [begin, end] = stx::whole(list);

	while(begin != end) {
		std::sort(begin, end);
		auto & current = *(begin++);

		if(current.at == e) {
			return trace_path(list, &current);
		}

		for_all_neighbors(current, list, [&] (auto & neighbor) {
			const auto new_cost = current.cost + graph[neighbor.at];
			if(new_cost < neighbor.cost) {
				neighbor.cost = new_cost;
				neighbor.prev = current.at;
			}
		});
	}
	return {};
}