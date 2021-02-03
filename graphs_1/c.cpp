#include "algorithm"
#include "cstdio"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;

void dfs_sort(size_t vertex,
              const vector<vector<size_t>>& graph,
              vector<bool>& used,
              vector<size_t>& order) {
    used[vertex] = true;
    for (size_t edge_vertex: graph[vertex]) {
        if (not used[edge_vertex]) {
            dfs_sort(edge_vertex, graph, used, order);
        }
    }
    order.push_back(vertex);
}

bool dfs_cycle(size_t vertex,
               const vector<vector<size_t>>& graph,
               vector<size_t>& colors) {
    colors[vertex] = 1;
    bool is_cycle = false;
    for (size_t edge_vertex: graph[vertex]) {
        if (colors[edge_vertex] == 0) {
            is_cycle = is_cycle || dfs_cycle(edge_vertex, graph, colors);
        }
        if (colors[edge_vertex] == 1) {
            is_cycle = true;
        }
    }
    colors[vertex] = 2;
    return is_cycle;
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
    }
    vector<size_t> colors(vertices_cnt, 0);
    bool is_cycle = false;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (colors[i] == 0) {
            is_cycle = is_cycle || dfs_cycle(i, graph, colors);
        }
    }
    if (is_cycle) {
        cout << -1 << "\n";
    } else {
        vector<bool> used(vertices_cnt, false);
        vector<size_t> order;
        for (size_t i = 0; i < graph.size(); ++i) {
            if (not used[i]) {
                dfs_sort(i, graph, used, order);
            }
        }
        for (ssize_t i = order.size() - 1; i >= 0; --i) {
            cout << order[i] + 1 << " ";
        }
        cout << "\n";
    }
}