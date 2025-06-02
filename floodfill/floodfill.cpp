#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility> 

using namespace std;

vector<string> fileReader(string fileName) {
    vector<string> Grid;
    string temp;

    ifstream InputFile(fileName);

    while(getline(InputFile, temp)) {
        Grid.push_back(temp);
    }
    

    InputFile.close();

    return Grid;
}

struct Click {
    int x;
    int y;
};

void bfs(int i, int j, int n, vector<string>& grid) {
    queue<pair<int, int>> q;
    q.push({i, j});

    while(!q.empty() ) {
        pair<int, int> point = q.front();
        q.pop();
        int x = point.first;
        int y = point.second;

        if(x < 0 || y < 0 || x >= n || y >= n) {
            continue;
        }

        if(grid[x][y] != '#') {
            if(grid[x][y] != '$') {
                grid[x][y] = '$';
                if(x > 0) {
                    q.push({x - 1, y});
                }
                if(x < (n - 1)) {
                    q.push({x + 1, y});
                }
                if(y > 0) {
                    q.push({x, y - 1});
                }
                if(y < (n - 1)) {
                    q.push({x, y + 1});
                }
            }
        }
    }
}

int main() {
    Click c;
    cin >> c.x >> c.y;

    vector<string> grid = fileReader("grid.txt");

    int n = grid.size();

    int x_start = --c.x;
    int y_start = --c.y;
    bfs(x_start, y_start, n, grid);

    for(int row = 0; row < n; ++row) {
        cout << grid[row] << endl;
    }

    return 0;
}