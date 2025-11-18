#include <vector>
#include <queue>
#include <limits>

using namespace std;

vector<int> dijkstra(const vector<vector<pair<int,int>>>& graph, int source)
{
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);

    using Node = pair<int,int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            int alt = dist[u] + weight;

            if(alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
