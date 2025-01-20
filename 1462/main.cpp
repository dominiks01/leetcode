#include <limits.h>
#include <stdlib.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<bool> checkIfPrerequisite(
    int numCourses, std::vector<std::vector<int>>& prerequisites,
    std::vector<std::vector<int>>& queries) {

    std::vector<std::vector<int>> graphAdjList(numCourses, std::vector<int>());
    std::vector<int> indegree(numCourses);

    for (auto& it: prerequisites) {
        graphAdjList[it[0]].push_back(it[1]);
        indegree[it[1]]++;
    }

    std::queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    std::unordered_map<int, std::unordered_set<int>> mp;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto neigh: graphAdjList[current]) {

            mp[neigh].insert(current);
            for (auto x: mp[current]) {// propagate order.
                mp[neigh].insert(x);
            }

            indegree[neigh]--;
            if (indegree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }

    std::vector<bool> res;
    for (auto q: queries) {
        res.push_back(mp[q[1]].count(q[0]));
    }
    return res;
};

int main() {
    std::vector<std::vector<int>> prerequisites = {};
    std::vector<std::vector<int>> queries = {{1, 0}, {0, 1}};

    for (auto it:
         checkIfPrerequisite(prerequisites.size(), prerequisites, queries)) {
        std::cout << it << " ";
    }

    return 0;
}