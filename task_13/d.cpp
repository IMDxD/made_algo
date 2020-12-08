#include "iostream"
#include "list"
#include "queue"
#include "vector"

using std::cin;
using std::cout;
using std::list;
using std::queue;
using std::vector;

struct Edge {
  uint32_t from;
  uint32_t to;
  bool is_used;

  Edge(uint32_t from, uint32_t to) :
      from(from),
      to(to),
      is_used(false) {};
};

int main() {
    std::ios::sync_with_stdio(false);
    uint32_t vertex_cnt, edge_cnt, start_vertex, end_vertex;
    cin >> vertex_cnt >> edge_cnt >> start_vertex >> end_vertex;
    --start_vertex;
    --end_vertex;
    vector<vector<Edge*>> graph(vertex_cnt);
    vector<list<uint32_t>> paths(2);
    vector<Edge*> edges;
    uint32_t from, to;
    for (uint32_t i = 0; i < edge_cnt; ++i) {
        cin >> from >> to;
        --from;
        --to;
        Edge* new_edge = new Edge(from, to);
        graph[from].push_back(new_edge);
        edges.push_back(new_edge);
    }
    for (size_t i = 0; i < 2; ++i) {
        queue<uint32_t> edge_order;
        edge_order.push(start_vertex);
        uint32_t cur_vertex = start_vertex;
        vector<bool> used(vertex_cnt, false);
        vector<Edge*> vertex_path(vertex_cnt);
        used[start_vertex] = true;
        while (!edge_order.empty() && cur_vertex != end_vertex) {
            cur_vertex = edge_order.front();
            edge_order.pop();
            for (auto edge: graph[cur_vertex]) {
                if (!used[edge->to] && !edge->is_used) {
                    edge_order.push(edge->to);
                    used[edge->to] = true;
                    vertex_path[edge->to] = edge;
                }
            }
        }
        if (cur_vertex == end_vertex) {
            paths[i].push_front(cur_vertex);
            while (cur_vertex != start_vertex) {
                Edge* edge = vertex_path[cur_vertex];
                edge->is_used = true;
                cur_vertex = edge->from;
                paths[i].push_front(cur_vertex);
            }
        } else {
            break;
        }
    }
    if (!paths[1].empty()) {
        cout << "YES" << "\n";
        for (auto& path: paths) {
            for (auto vertex: path) {
                cout << vertex + 1 << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "NO" << "\n";
    }
    return 0;
}