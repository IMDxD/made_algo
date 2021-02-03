#include "algorithm"
#include "cmath"
#include "iostream"
#include "queue"
#include "vector"

using std::cin;
using std::cout;
using std::max;
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

vector<bool> dfs(size_t vertex, size_t end, vector<vector<Edge*>>& graph, vector<bool>& used) {
    used[vertex] = true;
    if (vertex == end) {
        return used;
    }
    for (auto& edge: graph[vertex]) {
        if (!used[edge->to] && edge->used_flow < edge->flow) {
            used = dfs(edge->to, end, graph, used);
        }
    }
    return used;
}

int find_max_flow(size_t vertex_cnt, int max_capacity, vector<vector<Edge*>>& graph) {
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
    return result;
}

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
    find_max_flow(vertex_cnt, max_capacity, graph);
    vector<bool> used(vertex_cnt, false);
    vector<size_t> min_cut_edges;
    used = dfs(0, vertex_cnt - 1, graph, used);
    int min_cut_capacity = 0;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (used[edges[i]->to] != used[edges[i]->from]) {
            min_cut_capacity += edges[i]->flow;
            min_cut_edges.push_back(i + 1);
        }
    }
    cout << min_cut_edges.size() << " " << min_cut_capacity << "\n";
    for (auto el: min_cut_edges) {
        cout << el << " ";
    }
    cout << "\n";
    return 0;
}