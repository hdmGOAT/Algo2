// Lab 1: Minimum Set Cover - Greedy Algorithm
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

vector<set<int>> greedySetCover(const set<int>& universe, const vector<set<int>>& subsets) {
    set<int> remaining = universe;
    vector<set<int>> selected;
    vector<bool> used(subsets.size(), false);

    while (!remaining.empty()) {
        int bestSetIdx = -1;
        int maxCover = 0;

        for (int i = 0; i < subsets.size(); ++i) {
            if (used[i]) continue;
            int cover = count_if(subsets[i].begin(), subsets[i].end(), [&](int x) { return remaining.count(x); });
            if (cover > maxCover) {
                maxCover = cover;
                bestSetIdx = i;
            }
        }

        if (bestSetIdx == -1) break;

        used[bestSetIdx] = true;
        selected.push_back(subsets[bestSetIdx]);
        for (int x : subsets[bestSetIdx]) remaining.erase(x);
    }

    return selected;
}

int optimalSetCoverSize(const set<int>& universe, const vector<set<int>>& subsets) {
    int m = subsets.size();
    int bestSize = m + 1;

    for (int mask = 1; mask < (1 << m); ++mask) {
        set<int> covered;
        int count = 0;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                ++count;
                for (int x : subsets[i]) covered.insert(x);
            }
        }
        if (covered == universe) bestSize = min(bestSize, count);
    }
    return bestSize;
}

void testMinimumSetCover() {
    cout << "--- Lab 1: Minimum Set Cover (Input 1) ---\n";
    set<int> U1 = {1,2,3,4,5};
    vector<set<int>> S1 = {{1,2,3}, {2,4}, {3,4}, {4,5}};
    auto greedyResult1 = greedySetCover(U1, S1);

    cout << "Greedy Set Cover Result (" << greedyResult1.size() << " sets):\n";
    for (auto& s : greedyResult1) {
        cout << "{";
        for (int x : s) cout << x << ", ";
        cout << "}\n";
    }
    int optimal1 = optimalSetCoverSize(U1, S1);
    double ratio1 = static_cast<double>(greedyResult1.size()) / optimal1;
    cout << "Optimal Set Cover Size: " << optimal1 << "\n";
    cout << "Approximation Ratio: " << ratio1 << "\n\n";

    cout << "--- Lab 1: Minimum Set Cover (Input 2) ---\n";
    set<int> U2 = {1,2,3,4,5,6,7,8,9,10};
    vector<set<int>> S2 = {
        {1,2,3,4},
        {3,4,5,6},
        {5,6,7,8},
        {7,8,9,10},
        {1,9,10}
    };
    auto greedyResult2 = greedySetCover(U2, S2);

    cout << "Greedy Set Cover Result (" << greedyResult2.size() << " sets):\n";
    for (auto& s : greedyResult2) {
        cout << "{";
        for (int x : s) cout << x << ", ";
        cout << "}\n";
    }
    int optimal2 = optimalSetCoverSize(U2, S2);
    double ratio2 = static_cast<double>(greedyResult2.size()) / optimal2;
    cout << "Optimal Set Cover Size: " << optimal2 << "\n";
    cout << "Approximation Ratio: " << ratio2 << "\n";
}

int main() {
    testMinimumSetCover();
    return 0;
}
