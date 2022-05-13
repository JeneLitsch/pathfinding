#pragma once
#include <unordered_map>
#include <optional>
#include <string>
#include <vector>

namespace minos {
	class Graph {
	public:
		struct Node {
			std::unordered_map<std::string, int> transitions;
		};

		void insert(const std::string & from, const std::string & to, int cost);

		const Node & operator[](const std::string & key) const;

		auto begin() const {
			return nodes.begin();
		}

		auto end() const {
			return nodes.end();
		}

		auto cbegin() const {
			return nodes.cbegin();
		}

		auto cend() const {
			return nodes.cend();
		}

	private:
		std::unordered_map<std::string, Node> nodes;
	};
}