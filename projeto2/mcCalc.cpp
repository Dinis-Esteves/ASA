#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility> 
#include <algorithm>

using namespace std;

// global variables
int num_lines;
int num_stations;
int edges;
vector<int> chosen_ones;
vector<vector<pair<int, int>>> metro_lines;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

int bfs(int start, int start_line) {
    vector<int> visited(num_stations, 0);  // Visited nodes
    vector<int> line_changes(num_stations, 0);  // Number of line changes to each station
    vector<pair<int, int>> queue; 
    int max_value = 0; 

    visited[start] = 1;
    queue.push_back({start, start_line}); 

    while (!queue.empty()) {
        pair<int, int> current = queue[0];
        queue.erase(queue.begin());
        int node = current.first;
        int current_line = current.second;

        for (pair<int, int> edge : metro_lines[node]) {
            int next = edge.first; 
            int next_line = edge.second; 

            // If the neighboring station has not been visited
            if (!visited[next]) {
                visited[next] = 1;
                // If the current line is different from the previous line, it's a line change
                line_changes[next] = line_changes[node] + (current_line != next_line ? 1 : 0);
                max_value = max(max_value, line_changes[next]);  // Update the maximum number of line changes
                queue.push_back({next, next_line});  // Add the next station with its line to the queue
            }
        }
    }

    return max_value;
}

int main() {
    int max_value = 0;
    cin >> num_stations >> edges >> num_lines;

    metro_lines.resize(num_stations);
    chosen_ones.resize(num_lines);

    // store the edges
    for (int i = 0; i < edges; i++) {
        int st1;
        pair<int, int> edge;

        cin >> st1 >> edge.first >> edge.second;

        metro_lines[st1 - 1].push_back({edge.first - 1, edge.second});  // Adjusting for 0-based indexing
        metro_lines[edge.first - 1].push_back({st1 - 1, edge.second});  // Adjusting for 0-based indexing
    }

    // debug - print the edges
    for (int i = 0; i < num_stations; i++) {
        cout << "Station " << i + 1 << ": ";
        for (pair<int, int> edge : metro_lines[i]) {
            cout << edge.first + 1 << " " << edge.second << " | ";  // Adjusting for 1-based indexing
        }
        cout << endl;
    }

    unordered_set<pair<int, int>, pair_hash> unique_nodes;

    for (int i = 0; i < num_stations; i++) {
        // Skip stations with no edges
        if (metro_lines[i].empty()) {
            cout << "-1" << endl;
            return 0;
        }

        // Check if all edges belong to the same line
        int default_line = metro_lines[i][0].second; // Line number of the first edge
        bool is_one_line = true;

        for (const pair<int, int>& edge : metro_lines[i]) {
            if (edge.second != default_line) {
                is_one_line = false;
                break;
            }
        }

        // Add the (station, line) tuple to the set if it belongs to only one line
        if (is_one_line) {
            unique_nodes.insert({i, default_line}); // Use 0-based station index
        }
    }

    // Debugging: Print the unique nodes
    cerr << "Nodes belonging to only one line: ";
    for (const auto& node : unique_nodes) {
        cerr << "(" << node.first + 1 << ", " << node.second << ") "; // Adjust for 1-based index
    }
    cerr << endl;

    // Check if there are any unique nodes
    if (!unique_nodes.empty()) {
        // Remove the first element from the unordered_set
        auto it = unique_nodes.begin();
        pair<int, int> random_node = *it;
        
        // Remove the node from the set (pop the node)
        unique_nodes.erase(it);

        // Apply BFS on the selected node
        max_value = bfs(random_node.first, random_node.second);

        cout << max_value << endl;
    }

    return 0;
}
