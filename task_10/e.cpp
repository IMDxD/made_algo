#include "algorithm"
#include "cstdio"
#include "iostream"
#include "set"
#include "vector"

using std::cin;
using std::cout;
using std::set;
using std::vector;

void dfs(size_t vertex,
         const vector<vector<size_t>>& graph,
         vector<size_t>& up,
         vector<size_t>& tin,
         size_t& step,
         set<size_t>& is_articulation,
         bool is_root) {
    ++step;
    up[vertex] = step;
    tin[vertex] = step;
    size_t count = 0;
    for (size_t edge_vertex: graph[vertex]) {
        if (up[edge_vertex] > 0) {
            up[vertex] = std::min(up[vertex], tin[edge_vertex]);
        } else {
            dfs(edge_vertex, graph, up, tin, step, is_articulation, false);
            ++count;
            up[vertex] = std::min(up[vertex], up[edge_vertex]);
            if (up[edge_vertex] >= tin[vertex] && !is_root) {
                is_articulation.insert(vertex);
            }
        }
    }
    if (is_root && count > 1) {
        is_articulation.insert(vertex);
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
    set<size_t> is_articulation;
    vector<size_t> up(vertices_cnt, 0);
    vector<size_t> tin(vertices_cnt, 0);
    size_t step = 0;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (up[i] == 0) {
            dfs(i, graph, up, tin, step, is_articulation, true);
        }
    }
    cout << is_articulation.size() << "\n";
    for (auto el: is_articulation) {
        cout << el + 1 << " ";
    }
    cout << "\n";
}