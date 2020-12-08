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
  size_t from;
  size_t to;
  int flow;
  int used_flow;
  bool used_path;
  size_t neighbor;

  Edge(size_t from, size_t to, int flow, int used_flow, size_t neighbor) :
      from(from),
      to(to),
      flow(flow),
      used_flow(used_flow),
      used_path(false),
      neighbor(neighbor) {};
};

int find_max_flow(size_t vertex_cnt, size_t start, size_t end, vector<vector<Edge*>>& graph) {
    int result = 0;
    bool path_exist = true;
    while (path_exist) {
        queue<size_t> edge_order;
        edge_order.push(start);
        size_t cur_vertex = start;
        vector<bool> used(vertex_cnt, false);
        vector<Edge*> vertex_path(vertex_cnt);
        used[start] = true;
        while (!edge_order.empty() && cur_vertex != end) {
            cur_vertex = edge_order.front();
            edge_order.pop();
            for (auto edge: graph[cur_vertex]) {
                if (!used[edge->to] && edge->used_flow < edge->flow && edge->flow - edge->used_flow > 0) {
                    edge_order.push(edge->to);
                    used[edge->to] = true;
                    vertex_path[edge->to] = edge;
                }
            }
        }
        if (cur_vertex == end) {
            ++result;
            while (cur_vertex != start) {
                Edge* edge = vertex_path[cur_vertex];
                edge->used_flow += 1;
                graph[edge->to][edge->neighbor]->used_flow -= 1;
                cur_vertex = edge->from;
            }
        } else {
            path_exist = false;
        }
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertex_cnt, edge_cnt, start, end;
    cin >> vertex_cnt >> edge_cnt >> start >> end;
    --start;
    --end;
    vector<vector<Edge*>> graph(vertex_cnt);
    vector<Edge*> edges;
    size_t from, to;
    for (size_t i = 0; i < edge_cnt; ++i) {
        cin >> from >> to;
        --from;
        --to;
        Edge* new_edge = new Edge(from, to, 1, 0, graph[to].size());
        graph[from].push_back(new_edge);
        edges.push_back(new_edge);
        Edge* new_reverse_edge = new Edge(to, from, 0, 0, graph[from].size() - 1);
        graph[to].push_back(new_reverse_edge);
    }
    int path_cnt = find_max_flow(vertex_cnt, start, end, graph);
    if (path_cnt > 1) {
        cout << "YES" << "\n";
        for (size_t i = 0; i < 2; ++i) {
            queue<uint32_t> edge_order;
            edge_order.push(start);
            uint32_t cur_vertex = start;
            vector<Edge*> vertex_path(vertex_cnt);
            vector<bool> used(vertex_cnt, false);
            used[start] = true;
            while (!edge_order.empty() && cur_vertex != end) {
                cur_vertex = edge_order.front();
                edge_order.pop();
                for (auto edge: graph[cur_vertex]) {
                    if (!used[edge->to] && edge->used_flow == 1 && !edge->used_path) {
                        edge_order.push(edge->to);
                        used[edge->to] = true;
                        vertex_path[edge->to] = edge;
                    }
                }
            }
            list<size_t> path;
            path.push_front(cur_vertex);
            while (cur_vertex != start) {
                Edge* edge = vertex_path[cur_vertex];
                edge->used_path = true;
                cur_vertex = edge->from;
                path.push_front(cur_vertex);
            }
            for (auto el: path) {
                cout << el + 1 << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "NO" << "\n";
    }
    return 0;
}