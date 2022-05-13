#include "Graph.hxx"

namespace minos {
	void Graph::insert(const std::string & from, const std::string & to, int cost) {
		auto & node_from = this->nodes[from];
		this->nodes[to];
		node_from.transitions.insert_or_assign(to, cost);
	}

	const Graph::Node & Graph::operator[](const std::string & key) const {
		return this->nodes.at(key);
	}
}