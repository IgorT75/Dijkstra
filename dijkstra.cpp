#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <exception>

using namespace std;

void printVec(const vector<size_t>& v) {
	printf("%zu: ", v.size());
	for (size_t i : v)
		printf("%zu, ", i);
	printf("\n");
}

class Graph
{
	vector<vector<size_t>> _topo;
	map<pair<size_t, size_t>, size_t> _weights;

	size_t findMin(const vector<size_t>& costs, const vector<bool>& visited) const {
		size_t minCost = INT_MAX;
		for (size_t node = 0; node < _topo.size(); ++node) {
			if (visited[node]) continue;
			minCost = std::min(minCost, costs[node]);
		}
		return minCost;
	}

public:
	Graph(vector<vector<size_t>> graph, map<pair<size_t, size_t>, size_t> weights) :
		_topo(std::move(graph)), _weights(std::move(weights)) {}

	vector<size_t> dijkstra(size_t beg) const
	{
		const size_t nodes = _topo.size();
		if (beg >= nodes) throw exception("No such a node.");

		vector<size_t> costs(nodes, INT_MAX);
		costs[beg] = 0;
		vector<bool> visited(nodes, false);



		return costs;
	}
};

int main()
{
	const vector<vector<size_t>> topo{
	{ 1 },
	{ 5, 7 },
	{ 1, 3 },
	{  },
	{ 2, 3, 5 },
	{ 0, 6 },
	{ 2, 4 } };

	const map<pair<size_t, size_t>, size_t> weights {
		{ {0, 1}, 2},
		{ {1, 5}, 3},
		{ {1, 6}, 7},
		{ {2, 1}, 5},
		{ {2, 3}, 4},
		{ {4, 2}, 2},
		{ {4, 3}, 1},
		{ {4, 5}, 6},
		{ {5, 0}, 1},
		{ {5, 6}, 2},
		{ {6, 2}, 3},
		{ {6, 4}, 4},
	};

	Graph g { topo, weights };
	auto costs = g.dijkstra(0);

	return 0;
}