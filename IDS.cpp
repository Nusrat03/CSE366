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
vector <int> dfsCosts;
vector <int> verticesTraversedToReach;
vector <int> parents;
int verticesTraversed = 0;

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

void depthFirstSearch(vector <vector <int>> &graph, vector <vector <int>> &costs, int source, int cost, int limit) {
    colours[source] = GREY;
    dfsCosts[source] += cost;
    verticesTraversedToReach[source] = verticesTraversed;
    verticesTraversed++;

    if (limit <= 0) {
        return;
    }

    for (int i = 0; i < graph[source].size(); i++) {
        int neighbour = graph[source][i];
        if (colours[neighbour] == WHITE) {
            parents[neighbour] = source;
            depthFirstSearch(graph, costs, neighbour, dfsCosts[source] + costs[source][i], limit - 1);
        }
    }

    colours[source] = BLACK;
}

void ids(vector <vector <int>> &graph, vector <vector <int>> &costs, int source, int destination, int max_limit) {
    for (int i = 0; i <= max_limit; i++) {
        depthFirstSearch(graph, costs, source, 0, i);

        if (colours[destination] != WHITE) {
            cout << "Iterative depth " << i << endl;
            cout << dfsCosts[destination] << endl;
            printPaths(destination, source);

            cout << verticesTraversedToReach[destination] << endl;

            break;
        }

        fill(colours.begin(), colours.end(), WHITE);
        fill(dfsCosts.begin(), dfsCosts.end(), 0);
        fill(verticesTraversedToReach.begin(), verticesTraversedToReach.end(), 0);
        fill(parents.begin(), parents.end(), -1);
    }
}

int main() {
    int vertices, edges;

    cin >> vertices >> edges;

    vector <vector <int>> graph(vertices + 1);
    vector <vector <int>> costs(vertices + 1);
    colours.resize(vertices + 1, WHITE);
    dfsCosts.resize(vertices + 1, 0);
    verticesTraversedToReach.resize(vertices + 1, 0);
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

    ids(graph, costs, source, destination, 500);

    return 0;
}