#include <iostream>
#include <vector>
#include <utility> 
#include <tuple>
#include <algorithm>

using namespace std;

// global variables
int lines;
int stations;
int edges;
vector<vector<pair<int, int>>> metro_graph;

int bfs(int start, int start_line) {
    vector<int> visited(stations, 0);
    vector<int> line_changes(stations, 0);
    vector<pair<int, int>> queue; 
    int max_value = 0; 
    visited[start] = 1;
    queue.push_back({start, start_line}); 

    while (!queue.empty()) {
        pair<int, int> current = queue[0];
        queue.erase(queue.begin());
        int node = current.first;
        int current_line = current.second;

        for (pair<int, int> edge : metro_graph[node]) {
            int next = edge.first; 
            int next_line = edge.second; 

            // If the neighboring station has not been visited
            if (!visited[next]) {
                visited[next] = 1;
                // If the current line is different from the previous line, it's a line change
                line_changes[next] = line_changes[node] + (current_line != next_line ? 1 : 0);
                max_value = max(max_value, line_changes[next]); 
                queue.push_back({next, next_line});
            }
        }
    }

    // Check if any station is unreachable
    for (int i = 0; i < stations; i++) {
        if (!visited[i]) {
            return -1;
        }
    }
    
    return max_value;
}

vector<tuple<int, int>> node;

int main() {
    int max_value = 0;
    cin >> stations >> edges >> lines;

    metro_graph.resize(stations);
    node.resize(lines);

    // store the edges
    for (int i = 0; i < edges; i++) {
        int st1;
        pair<int, int> edge;

        cin >> st1 >> edge.first >> edge.second;

        metro_graph[st1 - 1].push_back({edge.first - 1, edge.second});
        metro_graph[edge.first - 1].push_back({st1 - 1, edge.second});

        // if we don't have line - 1 nodes yet and we ain't got a node for that line
        if ((int) node.size() < lines - 2 && node[edge.second - 1] == make_tuple(0, 0)) {
            node.push_back({st1 - 1, edge.second});
        }
    }

    for (tuple<int, int> random_node : node) { 

        int tmp = bfs(get<0>(random_node), get<1>(random_node));

        if (tmp == -1) {
            cout << -1 << endl;
            return 0;
        }

        max_value = max(max_value, tmp);
    }
    
    cout << max_value - 1<< endl;
    return 0;
}