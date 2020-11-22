#include "algorithm"
#include "cstdio"
#include "iostream"
#include "string"
#include "map"
#include "vector"

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

string STARTED_NAME = "polycarp";

void dfs(const string& vertex, map<string, vector<string>>& graph, map<string, size_t>& step_cnt, size_t step) {
    step_cnt[vertex] = step;
    for (string& edge_vertex: graph[vertex]) {
        if (step_cnt[edge_vertex] < step + 1) {
            dfs(edge_vertex, graph, step_cnt, step + 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t repo_cnt;
    cin >> repo_cnt;
    map<string, vector<string>> graph;
    string from, to;
    for (size_t i = 0; i < repo_cnt; ++i) {
        cin >> to >> from >> from;
        std::transform(to.begin(), to.end(), to.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        std::transform(from.begin(), from.end(), from.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        graph[from].push_back(to);
    }
    map<string, size_t> step_cnt;
    for (std::pair<string, vector<string>> vert_edges: graph) {
        step_cnt[vert_edges.first] = 0;
    }
    dfs(STARTED_NAME, graph, step_cnt, 1);
    size_t max_cnt = 0;
    for (std::pair<string, size_t> step_pair: step_cnt) {
        max_cnt = std::max(max_cnt, step_pair.second);
    }
    cout << max_cnt << "\n";
}