#include <iostream>
#include <vector>
using namespace std;

bool check(vector <vector <int>> &graph, int v, vector <int> &color, int c) {
    for(int i = 1; i < graph.size(); i++) {
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

bool colorgraph(vector <vector <int>> &graph, int m, vector <int> &color, int v) {
    if (v == graph.size()) {
        return true;
    }

    for (int c = 0; c < m; c++) {
        if (check(graph, v, color, c)) {
            color[v] = c;

            if (colorgraph(graph, m, color, v + 1)) {
                return true;
            }
            color[v] = -1;
        }
    }
    return false;
}

void solve(vector <int> &color) {
    for (int i = 1; i < color.size(); i++) {
        cout << color[i] << "\n";
    }
}

void initializecolor(vector <vector <int>> &graph, int m) {
    vector <int> color(graph.size(), -1);

    if (!colorgraph(graph, m, color, 1)) {
        cout << "NO";
        return;
    }

    solve(color);
}

int main() {
    int v, e;
    cin >> v >> e;

    vector <vector <int>> graph(v + 1, vector <int> (v + 1, 0));

    int vertex, connected;
    for (int i = 0; i < e; i++) {
        cin >> vertex >> connected;
        graph[vertex][connected] = 1;
        graph[connected][vertex] = 1;
    }

    int m;
    cin >> m;

    initializecolor(graph, m);
    return 0;
}