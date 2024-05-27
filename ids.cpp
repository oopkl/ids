#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Define the cities and their connections
map<string, map<string, int>> graph = {
    {"A", {{"B", 2}, {"C", 4}}},
    {"B", {{"A", 2}, {"D", 3}, {"E", 1}}},
    {"C", {{"A", 4}, {"F", 5}}},
    {"D", {{"B", 3}, {"G", 7}}},
    {"E", {{"B", 1}, {"G", 2}}},
    {"F", {{"C", 5}, {"G", 1}}},
    {"G", {{"D", 7}, {"E", 2}, {"F", 1}}}
};

// Heuristic function (estimated distance to goal "G")
map<string, int> heuristic = {
    {"A", 6}, {"B", 4}, {"C", 3}, {"D", 4}, {"E", 2}, {"F", 1}, {"G", 0}
};

bool depthLimitedSearch(const string &current, const string &goal, int limit, vector<string> &path, map<string, bool> &visited) {
    if (current == goal) {
        path.push_back(current);
        return true;
    }

    if (limit <= 0) {
        return false;
    }

    visited[current] = true;

    for (const auto &neighbor : graph[current]) {
        string next = neighbor.first;
        if (!visited[next]) {
            if (depthLimitedSearch(next, goal, limit - 1, path, visited)) {
                path.push_back(current);
                return true;
            }
        }
    }

    visited[current] = false;
    return false;
}

vector<string> iterativeDeepeningSearch(const string &start, const string &goal) {
    for (int depth = 0; ; depth++) {
        vector<string> path;
        map<string, bool> visited;
        if (depthLimitedSearch(start, goal, depth, path, visited)) {
            reverse(path.begin(), path.end());
            return path;
        }
    }
}

int main() {
    string start = "A";
    string goal = "G";

    vector<string> path = iterativeDeepeningSearch(start, goal);

    if (!path.empty()) {
        cout << "Path from " << start << " to " << goal << ":\n";
        for (const string &city : path) {
            cout << city << " -> ";
        }
        cout << "Goal reached.\n";
    } else {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}
