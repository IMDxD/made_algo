#include "algorithm"
#include "cmath"
#include "iostream"
#include "queue"
#include "vector"

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::queue;
using std::vector;

struct Edge {
  size_t from;
  size_t to;
  int flow;
  int used_flow;
  size_t neighbor;

  Edge(size_t from, size_t to, int flow, int used_flow, size_t neighbor) :
      from(from),
      to(to),
      flow(flow),
      used_flow(used_flow),
      neighbor(neighbor) {};
};

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertex_cnt, edge_cnt;
    cin >> vertex_cnt >> edge_cnt;
    vector<vector<Edge*>> graph(vertex_cnt);
    vector<Edge*> edges;
    size_t from, to;
    int flow;
    int max_capacity = 0;
    for (size_t i = 0; i < edge_cnt; ++i) {
        cin >> from >> to >> flow;
        --from;
        --to;
        Edge* new_edge = new Edge(from, to, flow, 0, graph[to].size());
        graph[from].push_back(new_edge);
        edges.push_back(new_edge);
        Edge* new_reverse_edge = new Edge(to, from, flow, 0, graph[from].size() - 1);
        graph[to].push_back(new_reverse_edge);
        max_capacity = max(max_capacity, flow);
    }

    int result = 0;
    int cur_power = std::floor(std::log2(max_capacity));
    while (cur_power >= 0) {
        queue<size_t> edge_order;
        edge_order.push(0);
        size_t cur_vertex = 0;
        vector<bool> used(vertex_cnt, false);
        vector<Edge*> vertex_path(vertex_cnt);
        used[0] = true;
        int delta = std::pow(2, cur_power);
        while (!edge_order.empty() && cur_vertex != vertex_cnt - 1) {
            cur_vertex = edge_order.front();
            edge_order.pop();
            for (auto edge: graph[cur_vertex]) {
                if (!used[edge->to] && edge->used_flow < edge->flow && edge->flow - edge->used_flow >= delta) {
                    edge_order.push(edge->to);
                    used[edge->to] = true;
                    vertex_path[edge->to] = edge;
                }
            }
        }
        if (cur_vertex == vertex_cnt - 1) {
            cur_vertex = vertex_cnt - 1;
            result += delta;
            while (cur_vertex != 0) {
                Edge* edge = vertex_path[cur_vertex];
                edge->used_flow += delta;
                graph[edge->to][edge->neighbor]->used_flow -= delta;
                cur_vertex = edge->from;
            }
        } else {
            --cur_power;
        }
    }
    cout << result << "\n";
    for (auto edge: edges) {
        cout << edge->used_flow << "\n";
    }
    return 0;
}