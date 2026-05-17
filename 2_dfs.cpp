#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {

    vector<vector<int> > adj;
    vector<int> visited;
    int v;

public:

    Graph(int vertices) {

        v = vertices;

        adj.resize(v, vector<int>(v,0));
        visited.resize(v,0);
    }

    void addEdge(int u, int w) {

        adj[u][w] = 1;
        adj[w][u] = 1;
    }

    void dfs(int node) {

        cout << node << " ";
        visited[node] = 1;

        #pragma omp parallel for
        for(int i=0;i<v;i++) {

            if(adj[node][i]==1 && !visited[i]) {

                #pragma omp critical
                {
                    if(!visited[i]) {
                        visited[i]=1;
                        dfs(i);
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

    for(int i=0;i<edges;i++) {

        int u,v;
        cin >> u >> v;

        g.addEdge(u,v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "\nDFS Traversal: ";

    g.dfs(start);

    return 0;
}