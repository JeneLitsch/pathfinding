#include "dijkstra.hxx"
#include <queue>
#include <iostream>
#include "stdxx/algorithm.hxx"

namespace minos {
	namespace {
		struct Entry {
			std::string at;
			std::optional<std::string> prev;
			// nullopt means infinite
			std::int64_t cost;
		};



		using List = std::vector<Entry>;



		constexpr std::int64_t infinite = std::numeric_limits<std::int64_t>::max();



		bool less(const Entry & l, const Entry & r) {
			return l.cost < r.cost;
		}


	
		List make_list(const Graph & graph, const std::string & s) {
			List list;
			for(const auto & [name, node] : graph) {
				if(name == s) {
					list.push_back(Entry{name, std::nullopt, 0});
				}
				else {
					list.push_back(Entry{name, std::nullopt, infinite});
				}
			}

			return list;
		}



		const Entry * find_prev(
			const std::vector<Entry> & list, 
			const Entry * entry) {
			for(const auto & e : list) {
				if(!entry->prev) return nullptr;
				if(entry->prev == e.at) {
					return &e;
				}
			}
			return nullptr;
		}



		Entry * find_entry(
			std::vector<Entry> & list,
			const std::string & name) {
			
			for(Entry & entry : list) {
				if(entry.at == name) return &entry;
			}
			return nullptr;
		}



		std::vector<std::string> trace_path(
			const std::vector<Entry> & list, 
			const Entry * entry) {
			std::vector<std::string> path;
			while (entry) {
				path.push_back(entry->at);
				entry = find_prev(list, entry);
			}
			auto [begin, end] = stx::whole(path);
			std::reverse(begin, end);
			return path;
		}



		void update_distance(
			const Entry & current,
			Entry & neighbor,
			int cost) {
			
			const auto new_cost = current.cost + cost;
			if(new_cost < neighbor.cost) {
				neighbor.cost = new_cost;
				neighbor.prev = current.at;
			}
		}



		void update_neighbors(
			const Entry & current,
			const Graph & graph,
			List & list) {

			const auto & node = graph[current.at];
			for(const auto & [to, cost] : node.transitions) {
				if(auto neighbor = find_entry(list, to)) {
					update_distance(current, *neighbor, cost);
				}
			}
		}
	}


	
	std::vector<std::string> dijkstra_fast(
		const Graph & graph,
		const std::string & s,
		const std::string & e) {
		
		List list = make_list(graph, s);
		auto [begin, end] = stx::whole(list);

		while(begin != end) {
			std::sort(begin, end, less);
			auto & entry = *(begin++);

			if(entry.at == e) {
				return trace_path(list, &entry);
			}

			update_neighbors(entry, graph, list);
		}
		return {};
	}


	std::vector<std::string> dijkstra_full(
		const Graph & graph,
		const std::string & s,
		const std::string & e) {
		
		List list = make_list(graph, s);
		auto [begin, end] = stx::whole(list);

		while(begin != end) {
			std::sort(begin, end, less);
			auto & current = *(begin++);
			update_neighbors(current, graph, list);
		}
		if(auto current = find_entry(list, e)) {
			return trace_path(list, current);
		}
		return {};
	}
}