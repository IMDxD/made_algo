#include "cstdio"
#include "iostream"
#include "set"
#include "vector"

using std::cin;
using std::cout;
using std::set;
using std::vector;

size_t DEFAULT_COLOR = 0;

void dfs_color(size_t vertex, const vector<vector<size_t>>& graph, vector<size_t>& colors, size_t color) {
    colors[vertex] = color;
    for (size_t edge_vertex: graph[vertex]) {
        if (colors[edge_vertex] == DEFAULT_COLOR) {
            dfs_color(edge_vertex, graph, colors, color);
        }
    }
}

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

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertices_cnt, egdes_cnt;
    cin >> vertices_cnt >> egdes_cnt;
    vector<vector<size_t>> graph(vertices_cnt);
    vector<vector<size_t>> graph_reverse(vertices_cnt);
    size_t first_ver, second_ver;
    for (size_t i = 0; i < egdes_cnt; ++i) {
        cin >> first_ver >> second_ver;
        --first_ver;
        --second_ver;
        graph[first_ver].push_back(second_ver);
        graph_reverse[second_ver].push_back(first_ver);
    }

    vector<bool> used(vertices_cnt, false);
    vector<size_t> order;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (not used[i]) {
            dfs_sort(i, graph_reverse, used, order);
        }
    }

    vector<size_t> colors(vertices_cnt, DEFAULT_COLOR);
    size_t color = DEFAULT_COLOR;
    for (ssize_t i = order.size() - 1; i >= 0; --i) {
        if (colors[order[i]] == DEFAULT_COLOR) {
            ++color;
            dfs_color(order[i], graph, colors, color);
        }
    }

    set<std::pair<size_t, size_t>> strong_edges;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (auto el: graph[i]) {
            if (colors[i] < colors[el]) {
                strong_edges.insert({colors[i], colors[el]});
            } else if (colors[i] > colors[el]) {
                strong_edges.insert({colors[el], colors[i]});
            }
        }
    }
    cout << strong_edges.size() << "\n";
}