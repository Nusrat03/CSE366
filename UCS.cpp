#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

struct Element {
    int vertex;
    int distance;

    Element(int v, int d) {
        vertex = v;
        distance = d;
    }

    bool operator < (const Element &a) const & {
        return distance < a.distance;
    }

    bool operator > (const Element &a) const & {
        return distance > a.distance;
    }
};

priority_queue <Element, vector <Element>, greater <Element> > pq;

void printPaths(vector <int> &parents, int destination, int source) {
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

void ucs(vector <vector <int>> &graph, vector <vector <int>> &weights, int source, int destination) {
    vector <int> distances(graph.size(), INT32_MAX);
    vector <bool> visited(graph.size(), false);
    vector <int> parents(graph.size(), -1);
    vector <int> final_visited(graph.size(), 0);

    distances[source] = 0;

    pq.push(Element(source, 0));

    int vertex, neighbour, distance;

    while (!pq.empty()) {
        vertex = pq.top().vertex;
        pq.pop();

        if (visited[vertex]) {
            continue;
        }

        int explored_nodes = count(visited.begin(), visited.end(), true);
        final_visited[vertex] = explored_nodes;

        visited[vertex] = true;

        for (int i = 0; i < graph[vertex].size(); i++) {
            neighbour = graph[vertex][i];
            distance = weights[vertex][i];

            if (distances[vertex] + distance < distances[neighbour]) {
                parents[neighbour] = vertex;
                distances[neighbour] = distances[vertex] + distance;
                pq.push(Element(neighbour, distances[neighbour]));
            }

        }
    }

    cout << distances[destination] << endl;
    printPaths(parents, destination, source);
    cout << final_visited[destination] << endl;
}

int main() {
    int vertices, edges;

    cin >> vertices >> edges;

    vector <vector <int>> graph(vertices + 1);
    vector <vector <int>> weights(vertices + 1);

    int vertex, neighbour, distance;

    for (int i = 0; i < edges; i++) {
        cin >> vertex >> neighbour >> distance;

        graph[vertex].push_back(neighbour);
        weights[vertex].push_back(distance);

        if (vertex != neighbour) {
            graph[neighbour].push_back(vertex);
            weights[neighbour].push_back(distance);
        }
    }

    int source, destination;
    cin >> source >> destination;

    ucs(graph, weights, source, destination);

    return 0;
}