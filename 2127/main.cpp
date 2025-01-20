#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

void dfs(int node, int start, std::vector<std::vector<int>>& adj,
         std::vector<bool>& visited, std::vector<int>& depth_tracker, int depth,
         int& max_cycle_length) {

    if (visited[node]) {
        if (node == start) {
            max_cycle_length =
                std::max(max_cycle_length, depth - depth_tracker[node]);
        }
        return;
    }

    visited[node] = true;
    depth_tracker[node] = depth;

    for (int neighbor: adj[node]) {
        dfs(neighbor, start, adj, visited, depth_tracker, depth + 1,
            max_cycle_length);
    }

    visited[node] = false;
    depth_tracker[node] = -1;
}

int maximumInvitations(std::vector<int>& favorite) {
    std::vector<std::vector<int>> adjList(favorite.size(), std::vector<int>());

    for (int i = 0; i < ( int )favorite.size(); i++) {
        adjList.at(i).push_back(favorite.at(i));
    }

    int max_cycle_length = -1;

    for (int i = 0; i < ( int )favorite.size(); i++) {
        std::vector<bool> visited(favorite.size(), false);
        std::vector<int> depth_tracker(favorite.size(), -1);
        dfs(i, i, adjList, visited, depth_tracker, 0, max_cycle_length);
    }

    return max_cycle_length;
}

int main() {
    std::vector<int> values = {1, 0, 0, 2, 1, 4, 7, 8, 9, 6, 7, 10, 8};
    std::cout << maximumInvitations(values);

    return 0;
}