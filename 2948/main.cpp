#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums,
                                                int limit) {

    std::vector<std::pair<int, int>> indexed;
    std::unordered_map<int, int> m_indexMap;

    for (int i = 0; i < ( int )nums.size(); i++) {
        indexed.push_back(std::make_pair(nums[i], i));
    }

    std::sort(indexed.begin(), indexed.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.first < b.first;
              });

    std::vector<std::vector<std::pair<int, int>>> sets;
    sets.push_back({indexed[0]});
    m_indexMap[nums[indexed[0].second]] = 0;

    for (int i = 1; i < ( int )nums.size(); i++) {
        if (std::abs(indexed[i].first - indexed[i - 1].first) <= limit) {
            m_indexMap[nums[indexed[i].second]] = sets.size() - 1;
            sets.back().push_back(indexed[i]);

        } else {
            sets.push_back({indexed[i]});
            m_indexMap[nums[indexed[i].second]] = sets.size() - 1;
        }
    }

    std::vector<int> result;

    for (int i = 0; i < ( int )nums.size(); i++) {
        int bucket = m_indexMap[nums[i]];
        result.push_back(sets[bucket].at(0).first);
        sets[bucket].erase(sets[bucket].begin());
    }

    return result;
}

int main() {
    std::vector<int> values = {5, 9, 35, 60, 73, 91, 61, 57, 87, 76};
    int limit = 11;

    if (lexicographicallySmallestArray(values, limit) != std::vector<int>{}) {
    }

    return 0;
}