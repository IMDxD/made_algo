#include "algorithm"
#include "cmath"
#include "cstdio"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::sqrt;
using std::vector;

struct Edge {
  uint32_t number;
  int x;
  int y;

  Edge() : number(0), x(0), y(0) {}
  Edge(uint32_t number, int x, int y) : number(number), x(x), y(y) {};

  double distance(Edge& other) const {
      return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
  }

  bool operator==(const Edge& other) const {
      return this->x == other.x && this->y == other.y;
  }

  bool operator<(const Edge& other) const {
      return this->x < other.x;
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    uint32_t vertices_cnt;
    cin >> vertices_cnt;
    vector<Edge> graph(vertices_cnt);
    int x, y;
    for (uint32_t i = 0; i < vertices_cnt; ++i) {
        cin >> x >> y;
        graph[i] = {i, x, y};
    }
    vector<bool> used(vertices_cnt, false);
    vector<double> path_weights(vertices_cnt, INT32_MAX);
    path_weights[0] = 0;
    Edge cur_vert = graph[0];
    double total_weight = 0;
    for (uint32_t i = 0; i < vertices_cnt; ++i) {
        used[cur_vert.number] = true;
        Edge new_vert = cur_vert;
        double min_distance = INT32_MAX;
        for (auto& vert: graph) {
            if (!used[vert.number]) {
                path_weights[vert.number] = min(path_weights[vert.number],
                                                cur_vert.distance(vert));
                if (path_weights[vert.number] < min_distance) {
                    min_distance = path_weights[vert.number];
                    new_vert = vert;
                }
            }
        }
        if (min_distance == INT32_MAX) {
            break;
        }
        cur_vert = new_vert;
        total_weight += min_distance;
    }
    cout << total_weight << "\n";
    return 0;
}