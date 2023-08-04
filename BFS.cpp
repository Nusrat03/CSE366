#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

void BFS(vector <vector <int> > &graph, int source, int destination) {
    queue <int> qu;
    vector <int> distance(graph.size(), -1);
    vector <int> parent(graph.size(), -1);

    distance[source] = 0;
    qu.push(source);

    int vertex;

    while (!qu.empty()) {
        ver = qu.front();
        qu.pop();

        for (int neighbour : graph[vertex]) {
            if (distance[neighbour] == -1) {
                parent[neighbour] = vertex;
                distance[neighbour] = 1 + distance[vertex];
                qu.push(neighbour);
            }
        }
    }

    cout << endl;
    cout << distance[destination] << endl;

    int child = destination;

    vector <string> path_steps;

    while (parent[child] != -1) {
        string step = to_string(parent[child]) + " " + to_string(child);
        path_steps.push_back(step);
        child = parent[child];
    }

    for (int i = path_steps.size() - 1; i >= 0; i--) {
        cout << path_steps[i] << endl;
    }
}

int main() {
    int vertices, edges, source, destination;

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

    cin >> source >> destination;

    BFS(graph, source, destination);

    return 0;
}