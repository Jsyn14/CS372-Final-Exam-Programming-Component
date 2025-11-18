#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Stand-alone Dijkstra function
vector<int> dijkstra(const vector<vector<pair<int,int>>>& graph, int source)
{
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);

    using Node = pair<int,int>; // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] == numeric_limits<int>::max()) continue;
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

// Test harness main()
int main() {
    vector<vector<pair<int,int>>> graph(5);

    auto add_edge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    add_edge(0, 1, 4);
    add_edge(0, 2, 1);
    add_edge(2, 1, 2);
    add_edge(1, 3, 1);
    add_edge(2, 3, 5);
    add_edge(3, 4, 3);

    int source = 0;
    vector<int> dist = dijkstra(graph, source);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < (int)dist.size(); ++i) {
        cout << "to " << i << " = ";
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "INF";
        } else {
            cout << dist[i];
        }
        cout << '\\n';
    }

    return 0;
}
