#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> reversed(graph.size(), std::vector<int>{});
    std::vector<int> degreein{};
    std::vector<int> result{};
    const int V = graph.size();

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < ( int )graph[i].size(); j++) {
            reversed[graph[i][j]].push_back(i);
        }
    }

    for (const auto& it: graph) {
        degreein.push_back(it.size());
    };

    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (degreein[i] == 0) {
            q.push(i);
            result.push_back(i);
        }
    }

    while (!q.empty()) {
        int act = q.front();
        q.pop();

        for (auto& it: reversed[act]) {
            degreein[it]--;
            if (degreein[it] == 0) {
                result.push_back(it);
                q.push(it);
            }
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}

int main() {
    std::vector<std::vector<int>> test = {{1, 2}, {2, 3}, {5}, {0},
                                          {5},    {},     {}};

    for (const auto& i: eventualSafeNodes(test)) {
        std::cout << i << " ";
    }

    return 0;
}
