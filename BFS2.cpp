#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

void BFS(vector <vector <int> > &graph, int source) {
    queue <int> qu;
    vector <int> distance(graph.size(), -1);
    vector <int> explorationOrder(graph.size(), -1);
    int order = 1;

    distance[source] = 0;
    explorationOrder[source] = order;
    order++;
    qu.push(source);

    int vertex;

    while (!qu.empty()) {
        vertex = qu.front();
        qu.pop();

        for (int neighbour : graph[vertex]) {
            if (distance[neighbour] == -1) {
                explorationOrder[neighbour] = order;
                distance[neighbour] = 1 + distance[vertex];
                qu.push(neighbour);
                order++;
            }
        }
    }

    cout << endl;

    for (int i = 1; i < explorationOrder.size(); i++) {
        cout << i << " " << explorationOrder[i] << endl;
    }
}

int main() {
    int vertices, edges;

    cin >> vertices >> edges;

    vector <vector <int> > graph(vertices + 1);

    int vertex, neighbour;
    for (int i = 0; i < edges; i++) {
        cin >> vertex >> neighbour;

        graph[vertex].push_back(neighbour);

        if (vertex != neighbour) {
            graph[neighbour].push_back(vertex);
        }
    }

    BFS(graph, 1);

    return 0;
}