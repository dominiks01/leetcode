#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
    int V, E;
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    std::vector<std::pair<int, int>> result;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        this->edges = {};
        this->result = {};
    }

    void addEdge(int u, int v, int w) {
        edges.emplace_back(w, std::make_pair(u, v));
    }

    std::vector<std::pair<int, int>> kruskalMST();
};

struct DisjoinSet {
    int *parent{nullptr}, *rank{nullptr};
    int n;

    DisjoinSet(int n) {
        this->parent = new int[n + 1];
        this->rank = new int[n + 1];
        this->n = n;

        for (int i = 0; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }

        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
        }

        if (rank[x] == rank[y]) rank[y]++;
    }
};

std::vector<std::pair<int, int>> Graph::kruskalMST() {
    std::sort(edges.begin(), edges.end());
    DisjoinSet dj(V);

    std::vector<std::pair<int, std::pair<int, int>>>::iterator it;
    std::vector<std::pair<int, int>> nonMstEdges;

    for (it = edges.begin(); it != edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = dj.find(u);
        int set_v = dj.find(v);

        if (set_u != set_v) {
            result.emplace_back(u, v);
            dj.merge(set_u, set_v);
        } else {
            nonMstEdges.emplace_back(u, v);
        }
    }

    return nonMstEdges;
}

class Solution {
   public:
    std::vector<int> findRedundantConnection(
        std::vector<std::vector<int>>& edges) {
        const int V = edges.size(), E = edges.size();
        Graph g(V, E);

        for (int i = 0; i < ( int )edges.size(); i++) {
            g.addEdge(edges[i][0], edges[i][1], i);
        }

        for (auto it: g.kruskalMST()) {
            return {it.first, it.second};
        }

        return {};
    }
};

int main() {
    std::vector<std::vector<int>> graph = {{1, 2}, {1, 3}, {2, 3}};

    Solution s;
    for (auto it: s.findRedundantConnection(graph)) {
        std::cout << it << "\n";
    }

    return 0;
}