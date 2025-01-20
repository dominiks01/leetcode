#include <cstddef>
#include <cstdio>
#include <iostream>
#include <print>
#include <queue>
#include <utility>
#include <vector>

class Compare {
   public:
    bool operator()(std::pair<int, std::pair<int, int>>& a,
                    std::pair<int, std::pair<int, int>>& b) {
        return a.first >= b.first;
    }
};

class Solution {
   public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {

        const int H = heightMap.size();
        const int W = heightMap[0].size();
        int result = 0;

        std::vector<std::vector<bool>> visited(H, std::vector<bool>(W, false));
        std::vector<std::vector<bool>> marked(H, std::vector<bool>(W, false));

        std::priority_queue<std::pair<int, std::pair<int, int>>,
                            std::vector<std::pair<int, std::pair<int, int>>>,
                            Compare>
            boundaries;

        std::vector<std::pair<int, int>> directions{
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < H; i++) {
            boundaries.push({heightMap[i][0], {i, 0}});
            boundaries.push({heightMap[i][W - 1], {i, W - 1}});
            marked[i][W - 1] = true;
            marked[i][0] = true;
        }

        for (int i = 1; i < W - 1; i++) {
            boundaries.push({heightMap[0][i], {0, i}});
            boundaries.push({heightMap[H - 1][i], {H - 1, i}});
            marked[0][i] = true;
            marked[H - 1][i] = true;
        }

        while (!boundaries.empty()) {
            auto [value, pos] = boundaries.top();
            boundaries.pop();

            for (auto pos_adj: directions) {

                auto new_pos = std::pair<int, int>{pos_adj.first + pos.first,
                                                   pos_adj.second + pos.second};

                if (new_pos.first < 0 || new_pos.first >= H ||
                    new_pos.second < 0 || new_pos.second >= W) {
                    continue;
                }

                if (marked[new_pos.first][new_pos.second] == true) {
                    continue;
                }

                if (visited[new_pos.first][new_pos.second] == true) {
                    continue;
                }

                if (heightMap[new_pos.first][new_pos.second] < value) {
                    result += value - heightMap[new_pos.first][new_pos.second];
                    heightMap[new_pos.first][new_pos.second] = value;
                    marked[new_pos.first][new_pos.second] = true;
                }

                boundaries.push(
                    {heightMap[new_pos.first][new_pos.second], new_pos});
            }

            visited[pos.first][pos.second] = true;
        }

        return result;
    }
};