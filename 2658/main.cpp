#include <limits.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;
using Matrix = std::vector<std::vector<int>>;

using Point = std::pair<int, int>;
using Matrix = std::vector<std::vector<int>>;

class Solution {
   public:
    int findMaxFish(std::vector<std::vector<int>>& grid) {

        const int M = grid.size();
        const int N = grid.at(0).size();
        std::vector<Point> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int K = directions.size();
        int result{0};

        auto isValid = [&](int y, int x) {
            return y >= 0 && y < M && x >= 0 && x < N && grid[y][x] != 0;
        };

        std::stack<std::pair<int, int>> q;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] != 0) {

                    int act = 0;
                    q.emplace(i, j);

                    while (!q.empty()) {
                        auto point = q.top();
                        q.pop();

                        if (grid[point.first][point.second] == 0) {
                            continue;
                        } else {
                            act += grid[point.first][point.second];
                            grid[point.first][point.second] = 0;
                        }

                        act += grid[point.first][point.second];

                        for (int k = 0; k < K; k++) {

                            Point p{point.first + directions.at(k).first,
                                    point.second + directions.at(k).second};

                            if (isValid(p.first, p.second)) {
                                q.emplace(p.first, p.second);
                            }
                        }
                    }

                    result = std::max(result, act);
                }
            }
        }

        return result;
    }
};

int main() {

    std::vector<std::vector<int>> grid = {{8, 6}, {2, 6}};

    Solution s;

    std::cout << s.findMaxFish(grid);
    return 0;
}