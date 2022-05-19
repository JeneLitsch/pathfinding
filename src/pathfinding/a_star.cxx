#include "a_star.hxx"
#include <queue>
#include <iostream>
#include "stdxx/algorithm.hxx"

namespace {
	struct Entry {
		stx::vector2i at;
		std::optional<stx::vector2i> prev;
		// nullopt means infinite
		std::int64_t g_cost;
		std::int64_t f_cost;

		friend bool operator<(const Entry & l, const Entry & r) {
			return l.f_cost < r.f_cost;
		}

		static Entry start(const stx::vector2i & at) {
			return Entry{at, std::nullopt, 0, 0};
		}

		static Entry unknown(const stx::vector2i & at) {
			return Entry{at, std::nullopt, infinite, infinite};
		}
	};
}



std::vector<stx::vector2i> a_star(
	const stx::grid2<int> & graph,
	const stx::vector2i & s,
	const stx::vector2i & e) {

	auto h = [&e](const stx::vector2i & current) {
		return stx::hypot(e - current);
	};
	
	std::vector<Entry> list = init_entries<Entry>(graph, s);
	auto [begin, end] = stx::whole(list);

	while(begin != end) {
		std::sort(begin, end);
		auto & current = *(begin++);

		if(current.at == e) {
			return trace_path(list, &current);
		}

		for_all_neighbors(current, list, [&] (auto & neighbor) {
			const auto new_g_cost = current.g_cost + graph[neighbor.at];
			if(new_g_cost < neighbor.g_cost) {
				neighbor.g_cost = new_g_cost;
				neighbor.f_cost = new_g_cost + h(neighbor.at);
				neighbor.prev = current.at;
			}
		});
	}
	return {};
}