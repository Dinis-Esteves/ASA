#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Global variables
int lines, edges, stations;
vector<set<int>> metro_lines_sets;
vector<vector<int>> metro_lines_graph;

int bfs(int start, int end) {
    vector<int> queue;
    vector<bool> visited(lines, false);

    queue.push_back(start);
    visited[start] = true;

    vector<int> distance(lines, 0);

    while (!queue.empty()) {
        int current = queue.front();
        queue.erase(queue.begin());

        if (current == end) {
            return distance[current];
        }

        for (int i = 0; i < lines; i++) {
            if ((int)metro_lines_graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;

                distance[i] = distance[current] + 1;

                queue.push_back(i);
            }
        }
    }

    return -1;
}

int main() {
    cin >> stations >> edges     >> lines;

    // Handle edge cases where no connections or lines exist
    if (lines == 0 || edges == 0) {
        cout << -1 << endl;
        return 0;
    }
    
    metro_lines_sets.resize(lines);
    metro_lines_graph.resize(lines, vector<int>(lines, 0)); // Initialize graph matrix with 0s

    for (int i = 0; i < edges; i++) {
        int st1, st2, line;
        cin >> st1 >> st2 >> line;

        metro_lines_sets[line - 1].insert(st1);
        metro_lines_sets[line - 1].insert(st2);
    }

    // Check if any line contains all stations
    for (int i = 0; i < lines; i++) {
        if ((int)metro_lines_sets[i].size() == stations) {
            cout << 0 << endl;
            return 0;
        }
    }

    // Build the graph matrix by checking intersections between line sets
    for (int i = 0; i < lines; i++) {
        for (int j = i + 1; j < lines; j++) {
            set<int> intersection;
            set_intersection(metro_lines_sets[i].begin(), metro_lines_sets[i].end(),
                             metro_lines_sets[j].begin(), metro_lines_sets[j].end(),
                             inserter(intersection, intersection.begin()));

            if (!intersection.empty()) {
                metro_lines_graph[i][j] = 1;
                metro_lines_graph[j][i] = 1;
            }
        }
    }

    // Check for unreachable stations
    set<int> all_reachable_stations;
    for (int i = 0; i < lines; i++) {
        all_reachable_stations.insert(metro_lines_sets[i].begin(), metro_lines_sets[i].end());
    }

    if ((int)all_reachable_stations.size() < stations) {
        cout << -1 << endl;
        return 0;
    }

    int max_path = 0;
    for (int i = 0; i < lines; i++) {
        for (int j = i + 1; j < lines; j++) {
            int path = bfs(i, j);
            if (path == -1) {
                cout << -1 << endl;
                return 0;
            }
            max_path = max(max_path, path);
        }
    }

    cout << max_path << endl;
    return 0;
}