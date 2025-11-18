#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<vector<int>> floydWarshall(const vector<vector<int>>& W)
{
    int n = W.size();
    vector<vector<int>> D = W;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (D[i][k] != numeric_limits<int>::max() &&
                    D[k][j] != numeric_limits<int>::max() &&
                    D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    return D;
}

int main() {
    const int INF = numeric_limits<int>::max();

    vector<vector<int>> W = {
        {0,   3,   INF, 5},
        {2,   0,   INF, 4},
        {INF, 1,   0,   INF},
        {INF, INF, 2,   0}
    };

    vector<vector<int>> D = floydWarshall(W);

    cout << "All-pairs shortest path matrix:\n";
    for (int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D[i].size(); j++) {
            if (D[i][j] == INF)
                cout << "INF ";
            else
                cout << D[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
