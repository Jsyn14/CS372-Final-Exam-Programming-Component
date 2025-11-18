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
