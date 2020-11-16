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

void printVecIdx(const vector<size_t>& v) {
	printf("[%zu]:\n", v.size());
	for (size_t i = 0, n = v.size(); i < n; ++i)
		printf("%zu: %zu\n", i, v[i]);
}

class Graph
{
	vector<vector<size_t>> _topo;
	map<pair<size_t, size_t>, size_t> _weights;
	vector<size_t> _parents;

	size_t findMin(const vector<size_t>& costs, const vector<bool>& visited) const {
		size_t minCost = INT_MAX, minIdx = INT_MAX;
		for (size_t idx = 0; idx < _topo.size(); ++idx) {
			if (visited[idx]) continue;
			if (costs[idx] < minCost) {
				minCost = costs[idx];
				minIdx = idx;
			}
		}
		return minIdx;
	}

public:
	Graph(vector<vector<size_t>> graph, map<pair<size_t, size_t>, size_t> weights) :
		_topo(std::move(graph)), _weights(std::move(weights)) {}

	vector<size_t> parents() const { return _parents; }

	vector<size_t> dijkstra(size_t beg)
	{
		const size_t nodes = _topo.size();
		if (beg >= nodes) throw exception("No such a node.");

		vector<size_t> costs(nodes, INT_MAX);
		costs[beg] = 0;
		vector<bool> visited(nodes, false);
		_parents = vector<size_t>(nodes, INT_MAX);

		for (size_t i = 0, n = costs.size(); i < n; ++i) {
			size_t minNode = findMin(costs, visited);
			if (minNode == INT_MAX) continue;

			visited[minNode] = true;
			for (size_t adjNode : _topo[minNode]) {
				if (visited[adjNode]) continue;
				
				const size_t newCost = costs[minNode] + _weights[{ minNode, adjNode }];
				if (newCost < costs[adjNode]) {
					costs[adjNode] = newCost;
					_parents[adjNode] = minNode;
				}
			}
		}

		return costs;
	}
};

int main()
{
	const vector<vector<size_t>> topo{
		{ 1 },
		{ 5, 6 },
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
	const vector<size_t> costs = g.dijkstra(4);

	printVecIdx(costs);

	const auto spg = g.parents();
	printVecIdx(spg);

	return 0;
}
