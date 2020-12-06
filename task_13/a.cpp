#include "algorithm"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::min;
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

int push_flow(size_t vertex, size_t end, int cur_flow, vector<vector<Edge>>& graph, vector<bool>& used) {
    used[vertex] = true;
    if (vertex == end) {
        return cur_flow;
    }
    for (auto& edge: graph[vertex]) {
        if (!used[edge.to] && edge.used_flow < edge.flow) {
            int next_flow = min(cur_flow, edge.flow - edge.used_flow);
            int delta = push_flow(edge.to, end, next_flow, graph, used);
            if (delta > 0) {
                edge.used_flow += delta;
                graph[edge.to][edge.neighbor].used_flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertex_cnt, edge_cnt;
    cin >> vertex_cnt >> edge_cnt;
    vector<vector<Edge>> graph(vertex_cnt);
    size_t from, to;
    int flow;
    for (size_t i = 0; i < edge_cnt; ++i) {
        cin >> from >> to >> flow;
        --from;
        --to;
        graph[from].emplace_back(from, to, flow, 0, graph[to].size());
        graph[to].emplace_back(to, from, flow, 0, graph[from].size() - 1);
    }
    vector<bool> used;
    int result = 0;
    while (true) {
        used.assign(vertex_cnt, false);
        int delta = push_flow(0, vertex_cnt - 1, INT32_MAX, graph, used);
        if (delta > 0) {
            result += delta;
        } else {
            break;
        }
    }
    cout << result << "\n";
    return 0;
}