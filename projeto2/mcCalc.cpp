#include <climits>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

// Global variables
int lines;
int stations;
int edges;
vector<vector<pair<int, int>>> metro_graph;
vector<tuple<int, int>> node;

int bfs(int start, int start_line) {
    vector<int> visited(stations, 0);
    vector<int> line_changes(stations, INT_MAX); 

    // Priority queue stores {line_changes, current_station, current_line}, sorted by line_changes
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> queue;

    queue.push({0, start, start_line});
    line_changes[start] = 0;

    while (!queue.empty()) {
        tuple <int, int, int> top = queue.top();
        queue.pop();

        int current_changes = get<0>(top);
        int node = get<1>(top);
        int current_line = get<2>(top);

        // If already visited with fewer changes, skip
        if (current_changes > line_changes[node]) continue;

        visited[node] = 1;

        for (pair<int, int> edge : metro_graph[node]) {
            int next = edge.first;
            int next_line = edge.second;

            int new_changes = current_changes + (current_line != next_line ? 1 : 0);

            // Update if we find a path with fewer line changes
            if (new_changes < line_changes[next]) {
                line_changes[next] = new_changes;
                queue.push({new_changes, next, next_line});
            }
        }
    }

    // Check if any station is unreachable
    for (int i = 0; i < stations; i++) {
        if (!visited[i]) {
            return -1;
        }
    }

    return *max_element(line_changes.begin(), line_changes.end());
}

int main() {
    int max_value = 0;
    cin >> stations >> edges >> lines;

    if (lines == 0) {
        cout << -1 << endl;
        return 0;
    }

    if (edges == 0) {
        cout << -1 << endl;
        return 0;
    }

    metro_graph.resize(stations);
    // Initialize with -1 to signify uninitialized nodes
    node.resize(lines - 1, make_tuple(-1, -1)); 

    // Store the edges
    for (int i = 0; i < edges; i++) {
        int st1;
        pair<int, int> edge;

        cin >> st1 >> edge.first >> edge.second;

        metro_graph[st1 - 1].push_back({edge.first - 1, edge.second});
        metro_graph[edge.first - 1].push_back({st1 - 1, edge.second});

        // Ensure we only add one node per line
        if (node[edge.second - 1] == make_tuple(-1, -1)) {
            node[edge.second - 1] = make_tuple(st1 - 1, edge.second);
        }
    }

    for (tuple<int, int> random_node : node) {
        if (get<0>(random_node) != -1) { 
            int tmp = bfs(get<0>(random_node), get<1>(random_node));

            if (tmp == -1) {
                cout << -1 << endl;
                return 0;
            }

            max_value = max(max_value, tmp);
        }
    }

    cout << max_value << endl;
    return 0;
}