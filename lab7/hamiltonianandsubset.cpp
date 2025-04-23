#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
using namespace std;

// --- Hamiltonian Path Section ---
const int NUM_EXPERIMENTS = 4;
bool adjMatrix[NUM_EXPERIMENTS][NUM_EXPERIMENTS] = {
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {0, 1, 1, 0}
};

bool isValidHamiltonianPath(const vector<int>& path, int numNodes) {
    if (path.size() != numNodes) return false;
    vector<bool> visited(numNodes, false);

    for (int i = 0; i < numNodes - 1; ++i) {
        if (!adjMatrix[path[i]][path[i + 1]]) return false;
        if (visited[path[i]]) return false;
        visited[path[i]] = true;
    }
    if (visited[path.back()]) return false;
    return true;
}

void testHamiltonianPathSimulation(int numTries = 5) {
    vector<int> nodes(NUM_EXPERIMENTS);
    iota(nodes.begin(), nodes.end(), 0);

    cout << "--- Hamiltonian Path Simulation ---\n";
    for (int i = 0; i < numTries; ++i) {
        random_shuffle(nodes.begin(), nodes.end());
        cout << "Try " << i + 1 << ": ";
        for (int x : nodes) cout << x << " ";

        if (isValidHamiltonianPath(nodes, NUM_EXPERIMENTS)) {
            cout << "-> Valid Path\n";
        } else {
            cout << "-> Invalid Path\n";
        }
    }
    cout << endl;
}

// --- Subset Sum Section ---
const int BUDGETS[] = {15, 20, 35, 30, 10};
const int NUM_BUDGETS = sizeof(BUDGETS) / sizeof(BUDGETS[0]);
const int TARGET_BUDGET = 65;

bool doesSubsetSumMatch(const vector<int>& subsetIndices, const int budgets[], int target) {
    int total = 0;
    for (int idx : subsetIndices) total += budgets[idx];
    return total == target;
}

void testSubsetSumSimulation(int numTries = 10) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> binary(0, 1);

    cout << "--- Subset Sum Simulation ---\n";
    for (int i = 0; i < numTries; ++i) {
        vector<int> subset;
        for (int j = 0; j < NUM_BUDGETS; ++j) {
            if (binary(gen)) subset.push_back(j);
        }

        cout << "Try " << i + 1 << ": Subset { ";
        int sum = 0;
        for (int idx : subset) {
            cout << idx << "(" << BUDGETS[idx] << ") ";
            sum += BUDGETS[idx];
        }
        cout << "} -> Total: " << sum << " ";

        if (sum == TARGET_BUDGET) {
            cout << "-> Matches Target Budget\n";
        } else {
            cout << "-> Does Not Match\n";
        }
    }
    cout << endl;
}

int main() {
    testHamiltonianPathSimulation();
    testSubsetSumSimulation();
    return 0;
}