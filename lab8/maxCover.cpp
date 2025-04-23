#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <random>
using namespace std;

vector<set<int>> greedyMaxCoverage(set<int> universe, const vector<set<int>>& subsets, int k) {
    set<int> covered;
    vector<set<int>> selected;
    vector<bool> used(subsets.size(), false);

    for (int i = 0; i < k; ++i) {
        int bestSetIdx = -1;
        int maxNew = 0;

        for (int j = 0; j < subsets.size(); ++j) {
            if (used[j]) continue;
            int newCover = count_if(subsets[j].begin(), subsets[j].end(), [&](int x) { return !covered.count(x); });
            if (newCover > maxNew) {
                maxNew = newCover;
                bestSetIdx = j;
            }
        }

        if (bestSetIdx == -1) break;
        used[bestSetIdx] = true;
        selected.push_back(subsets[bestSetIdx]);
        for (int x : subsets[bestSetIdx]) covered.insert(x);
    }

    return selected;
}

int bruteForceMaxCoverage(const set<int>& universe, const vector<set<int>>& subsets, int k) {
    int m = subsets.size();
    int maxCovered = 0;

    for (int mask = 1; mask < (1 << m); ++mask) {
        if (__builtin_popcount(mask) != k) continue;
        set<int> covered;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                for (int x : subsets[i]) covered.insert(x);
            }
        }
        maxCovered = max(maxCovered, static_cast<int>(covered.size()));
    }
    return maxCovered;
}

void printCoverageResults(const vector<set<int>>& result, const set<int>& universe, const vector<set<int>>& subsets, int k) {
    set<int> unionResult;
    for (auto& s : result) for (int x : s) unionResult.insert(x);

    cout << "Greedy Max Coverage Result (" << unionResult.size() << " elements):\n";
    for (auto& s : result) {
        cout << "{";
        for (int x : s) cout << x << ", ";
        cout << "}\n";
    }
    cout << "Total Covered Elements: " << unionResult.size() << "\n";

    if (universe.size() <= 20 && subsets.size() <= 20) {
        int optimal = bruteForceMaxCoverage(universe, subsets, k);
        double ratio = static_cast<double>(unionResult.size()) / optimal;
        cout << "Optimal Max Coverage: " << optimal << "\n";
        cout << "Approximation Ratio: " << ratio << "\n";
    }
    cout << "\n";
}

void testMaximumCoverage() {
    cout << "--- Lab 2: Maximum Coverage Problem (Input 1) ---\n";
    set<int> U1 = {1,2,3,4,5,6,7,8};
    vector<set<int>> S1 = {
        {1,2,3}, {2,4,6}, {3,5,7}, {4,6,8}, {1,7,8}
    };
    int k1 = 2;
    auto result1 = greedyMaxCoverage(U1, S1, k1);
    printCoverageResults(result1, U1, S1, k1);

    cout << "--- Lab 2: Maximum Coverage Problem (Input 2) ---\n";
    set<int> U2;
    for (int i = 1; i <= 20; ++i) U2.insert(i);

    vector<set<int>> S2;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sizeDist(5, 8);
    uniform_int_distribution<> elemDist(1, 20);

    for (int i = 0; i < 10; ++i) {
        set<int> subset;
        while (subset.size() < sizeDist(gen)) {
            subset.insert(elemDist(gen));
        }
        S2.push_back(subset);
    }

    int k2 = 3;
    auto result2 = greedyMaxCoverage(U2, S2, k2);
    printCoverageResults(result2, U2, S2, k2);
}

int main() {
    testMaximumCoverage();
    return 0;
}