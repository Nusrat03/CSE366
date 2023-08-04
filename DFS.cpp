#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

vector <int> colours;
vector <int> dfs_costs;
vector <int> vertices_traversed_to_reach;
vector <int> parents;
int vertices_traversed = 0;
bool has_cycle = false;

void printPaths(int destination, int source) {
    bool unreachable = false;

    stack <int> path;

    while (destination != source) {
        if (destination == -1) {
            unreachable = true;
            break;
        }

        path.push(destination);
        destination = parents[destination];
    }

    if (!unreachable) {
        cout << path.size() + 1 << endl;

        cout << source << endl;
        while (!path.empty()) {
            int top = path.top();
            path.pop();
            cout << top << endl;
        }
    } else {
        cout << "-1" << endl;
    }
}

void depthFirstSearch(vector <vector <int>> &graph, vector <vector <int>> &costs, int source, int cost) {
    colours[source] = GREY;
    dfs_costs[source] += cost;
    vertices_traversed_to_reach[source] = vertices_traversed;
    vertices_traversed++;

    for (int i = 0; i < graph[source].size(); i++) {
        int neighbour = graph[source][i];
        if (colours[neighbour] == WHITE) {
            parents[neighbour] = source;
            depthFirstSearch(graph, costs, neighbour, dfs_costs[source] + costs[source][i]);
        } else if (colours[neighbour] == GREY) {
            has_cycle = true;
        }
    }

    colours[source] = BLACK;
}

int main() {
    int vertices, edges;

    cin >> vertices >> edges;

    vector <vector <int>> graph(vertices + 1);
    vector <vector <int>> costs(vertices + 1);
    colours.resize(vertices + 1, WHITE);
    dfs_costs.resize(vertices + 1, 0);
    vertices_traversed_to_reach.resize(vertices + 1, 0);
    parents.resize(vertices + 1, -1);

    int vertex, neighbour, distance;

    for (int i = 0; i < edges; i++) {
        cin >> vertex >> neighbour >> distance;

        graph[vertex].push_back(neighbour);
        costs[vertex].push_back(distance);

        if (vertex != neighbour) {
            graph[neighbour].push_back(vertex);
            costs[neighbour].push_back(distance);
        }
    }

    int source, destination;
    cin >> source >> destination;

    depthFirstSearch(graph, costs, source, 0);

    cout << dfs_costs[destination] << endl;
    printPaths(destination, source);

    cout << vertices_traversed_to_reach[destination] << endl;

    return 0;
}