#include "algorithm"
#include "cstdio"
#include "iostream"
#include "set"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::pair;
using std::set;
using std::vector;

struct Edge {

  uint32_t from;
  uint32_t to;
  uint32_t weight;

  Edge(uint32_t from, uint32_t to, uint32_t weight) : from(from), to(to), weight(weight) {};
};

const pair<uint32_t, uint32_t> FIRST_VERT_INFO = {0, 0};

int main() {
    std::ios::sync_with_stdio(false);
    uint32_t vertices_cnt, egdes_cnt;
    cin >> vertices_cnt >> egdes_cnt;
    vector<vector<Edge>> graph(vertices_cnt);
    uint32_t first_ver, second_ver, ver_weight;
    for (uint32_t i = 0; i < egdes_cnt; ++i) {
        cin >> first_ver >> second_ver >> ver_weight;
        --first_ver;
        --second_ver;
        graph[first_ver].push_back({first_ver, second_ver, ver_weight});
        graph[second_ver].push_back({second_ver, first_ver, ver_weight});
    }
    set<pair<uint32_t, uint32_t>> vert_order;
    vector<uint32_t> path_weights(vertices_cnt, UINT32_MAX);
    vector<bool> used(vertices_cnt, false);
    path_weights[0] = 0;
    vert_order.insert(FIRST_VERT_INFO);
    while (!vert_order.empty()) {
        auto cur_iter = vert_order.begin();
        auto cur_vert = (*cur_iter).second;
        vert_order.erase(cur_iter);
        used[cur_vert] = true;
        for (auto& edge: graph[cur_vert]) {
            if (!used[edge.to]) {
                vert_order.erase({path_weights[edge.to], edge.to});
                path_weights[edge.to] = min(path_weights[edge.to], path_weights[cur_vert] + edge.weight);
                vert_order.insert({path_weights[edge.to], edge.to});
            }
        }
    }
    for (auto& weight: path_weights) {
        cout << weight << " ";
    }
    cout << "\n";
}