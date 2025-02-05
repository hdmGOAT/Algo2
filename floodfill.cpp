#include <iostream>
#include <vector>
using namespace std;

void floodFill(vector<vector<int>>& grid, int x, int y, int newColor, int originalColor) {

    int rows = grid.size(); // 1 instruction O(1)
    int cols = grid[0].size(); // 1 instruction O(1)

    if (x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] != originalColor) {
        return;
    } // 5 instructions O(1)

    grid[x][y] = newColor; // 1 instruction O(1)


    // TOTAL NUMBER OF RECURSIVE CALLS: BOUNDED BY THE NUMBER OF CELLS IN THE GRID

    // O (m x n) where m is the number of rows and n is the number of columns
    floodFill(grid, x + 1, y, newColor, originalColor); 
    floodFill(grid, x - 1, y, newColor, originalColor);
    floodFill(grid, x, y + 1, newColor, originalColor);
    floodFill(grid, x, y - 1, newColor, originalColor);

    // TOTAL NUMBER OF INSTRUCTIONS: (1 + 1 + 5 + 1) x (m x n) = 8 x (m x n) = O(m x n) 

    // Simplifies into O(n^2) under square matrix conditions
}

void startFloodFill(vector<vector<int>>& grid, int x, int y, int newColor) {
    if (grid.empty() || grid[0].empty()) {
        cout << "Error: Grid is empty!" << endl;
        return;
    }

    int originalColor = grid[x][y];

    if (originalColor != newColor) {
        floodFill(grid, x, y, newColor, originalColor);
    }
}

void printMatrix(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 1, 2, 2},
        {1, 1, 0, 2, 2},
        {1, 0, 0, 2, 2},
        {1, 1, 1, 2, 2}
    };

    cout << "Before Flood Fill:\n";
    printMatrix(grid);

    startFloodFill(grid, 1, 1, 3);

    cout << "\nAfter Flood Fill:\n";
    printMatrix(grid);

    return 0;
}
