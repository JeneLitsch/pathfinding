#pragma once
#include "stdxx/vector.hxx"
#include "stdxx/algorithm.hxx"


constexpr std::int64_t infinite = std::numeric_limits<std::int64_t>::max();


template<typename Entry>
std::vector<stx::vector2i> trace_path(
	const std::vector<Entry> & list, 
	const Entry * entry) {
	std::vector<stx::vector2i> path;
	while (true) {
		path.push_back(entry->at);
		if(!entry->prev) {
			break;
		}
		for(const auto & e : list) {
			if(entry->prev == e.at) {
				entry = &e;
				break;
			}
		}
	}
	auto [begin, end] = stx::whole(path);
	std::reverse(begin, end);
	return path;
}



template <typename Entry>
void for_all_neighbors(
	const Entry & current,
	std::vector<Entry> & list,
	const auto & fx) {


	const auto neighbors = std::array {
		current.at + stx::vector2i{-1,-1},
		current.at + stx::vector2i{ 0,-1},
		current.at + stx::vector2i{ 1,-1},
		current.at + stx::vector2i{-1, 0},
		current.at + stx::vector2i{ 1, 0},
		current.at + stx::vector2i{-1, 1},
		current.at + stx::vector2i{ 0, 1},
		current.at + stx::vector2i{ 1, 1},
	};
	
	for(const auto & to : neighbors) {
		for(Entry & neighbor : list) {
			if(neighbor.at == to) {
				fx(neighbor);
			}
		}
	}
}



template <typename Entry>
std::vector<Entry> init_entries(
	const stx::grid2<int> & graph,
	const stx::vector2i & s) {
	std::vector<Entry> list;
	for(unsigned x = 0; x < graph.size().x; ++x) {
		for(unsigned y = 0; y < graph.size().y; ++y) {
			stx::vector2i at{static_cast<int>(x), static_cast<int>(y)};
			if(at == s) {
				list.push_back(Entry::start(at));
			}
			else {
				list.push_back(Entry::unknown(at));
			}
		}
	}
	return list;
}