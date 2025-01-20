#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using Node = std::pair<int, int>;

class Solution {
   public:
    static int minCost(std::vector<std::vector<int>>& grid) {
        std::vector<Node> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int M = grid.size();
        const int N = grid[0].size();

        auto isValid = [&](int x, int y) {
            return x >= 0 && x < M && y >= 0 && y < N;
        };

        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::vector<std::vector<int>> distances(M,
                                                std::vector<int>(N, INT_MAX));

        distances[0][0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();

            int x = node / N, y = node % N;

            if (x == M - 1 && y == N - 1) {
                return cost;
            }

            for (int k = 0; k < ( int )directions.size(); ++k) {
                int nx = x + directions[k].first;
                int ny = y + directions[k].second;
                int add_cost = (grid[x][y] == k + 1) ? 0 : 1;

                if (isValid(nx, ny) && cost + add_cost < distances[nx][ny]) {
                    distances[nx][ny] = cost + add_cost;
                    pq.push({distances[nx][ny], nx * N + ny});
                }
            }
        }

        return 0;
    }
};

int main() {

    // std::vector<std::vector<int>> grid{
    //     {1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};

    std::vector<std::vector<int>> grid{{1, 1, 3}, {3, 2, 2}, {1, 1, 4}};
    std::cout << Solution::minCost(grid);

    return 0;
}