#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {

    int v;
    vector<vector<int>> adj;

public:

    Graph(int vertices) {
        v = vertices;
        adj.resize(v, vector<int>(v, 0));
    }

    void addEdge(int u, int w) {
        adj[u][w] = 1;
        adj[w][u] = 1;     // Undirected graph
    }

    void bfs(int start) {

        vector<bool> visited(v, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal: ";

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            cout << node << " ";

            #pragma omp parallel for
            for(int i = 0; i < v; i++) {

                if(adj[node][i] == 1 && !visited[i]) {

                    #pragma omp critical
                    {
                        if(!visited[i]) {
                            visited[i] = true;
                            q.push(i);
                        }
                    }
                }
            }
        }
    }
};

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):\n";

    for(int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    g.bfs(start);

    return 0;
}