#include "cstdio"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;

size_t DEFAULT_COLOR = 0;

void dfs(size_t vertex, const vector<vector<size_t>>& graph, vector<size_t>& used, size_t color) {
    used[vertex] = color;
    for (size_t edge_vertex: graph[vertex]) {
        if (used[edge_vertex] == DEFAULT_COLOR) {
            dfs(edge_vertex, graph, used, color);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertices_cnt, egdes_cnt;
    cin >> vertices_cnt >> egdes_cnt;
    vector<vector<size_t>> graph(vertices_cnt);
    size_t first_ver, second_ver;
    for (size_t i = 0; i < egdes_cnt; ++i) {
        cin >> first_ver >> second_ver;
        --first_ver;
        --second_ver;
        graph[first_ver].push_back(second_ver);
        graph[second_ver].push_back(first_ver);
    }
    vector<size_t> used(vertices_cnt, DEFAULT_COLOR);
    size_t color = DEFAULT_COLOR;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (used[i] == DEFAULT_COLOR) {
            ++color;
            dfs(i, graph, used, color);
        }
    }
    cout << color << "\n";
    for (auto c: used) {
        cout << c << " ";
    }
    cout << "\n";
}