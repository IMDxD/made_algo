#include "cstdio"
#include "iostream"
#include "queue"
#include "vector"

using std::cin;
using std::cout;
using std::queue;
using std::vector;

struct Edge {

  size_t from;
  size_t to;
  long long weight;

  Edge(size_t from, size_t to, long long weight) : from(from), to(to), weight(weight) {};
};

void update_negative_cycle_weight(vector<vector<Edge>>& graph, vector<long long>& weights, size_t cur_weight) {
    queue<size_t> coor_queue;
    coor_queue.push(cur_weight);
    while (!coor_queue.empty()) {
        size_t cur_vert = coor_queue.front();
        coor_queue.pop();
        weights[cur_vert] = INT64_MIN;;
        for (auto vert_edge: graph[cur_vert]) {
            if (weights[vert_edge.to] != INT64_MIN) {
                coor_queue.push(vert_edge.to);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertices_cnt, egdes_cnt, start_vert;
    cin >> vertices_cnt >> egdes_cnt >> start_vert;
    --start_vert;
    vector<vector<Edge>> graph(vertices_cnt);
    size_t first_ver, second_ver;
    long long ver_weight;
    for (uint32_t i = 0; i < egdes_cnt; ++i) {
        cin >> first_ver >> second_ver >> ver_weight;
        --first_ver;
        --second_ver;
        graph[first_ver].emplace_back(first_ver, second_ver, ver_weight);
    }
    vector<int16_t> path(vertices_cnt, INT16_MAX);
    vector<long long> weights(vertices_cnt, INT64_MAX);
    weights[start_vert] = 0;
    for (size_t i = 0; i < vertices_cnt; ++i) {
        for (auto& edges: graph) {
            for (auto edge: edges) {
                if (weights[edge.to] > weights[edge.from] + edge.weight && weights[edge.from] < INT64_MAX) {
                    weights[edge.to] = weights[edge.from] + edge.weight;
                }
            }
        }
    }
    for (auto& edges: graph) {
        for (auto& edge: edges) {
            if (weights[edge.to] > weights[edge.from] + edge.weight &&
                weights[edge.from] < INT64_MAX &&
                weights[edge.to] != INT64_MIN) {
                update_negative_cycle_weight(graph, weights, edge.to);
            }
        }
    }
    for (auto w: weights) {
        if (w == INT64_MAX) {
            cout << "*" << "\n";
        } else if (w == INT64_MIN) {
            cout << "-" << "\n";
        } else {
            cout << w << "\n";
        }
    }
    return 0;
}