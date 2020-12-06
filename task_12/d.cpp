#include "algorithm"
#include "cstdio"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::sort;
using std::swap;
using std::vector;

class NSIS {

 private:
  vector<uint32_t> rank_array;
  vector<uint32_t> parent_array;

 public:
  explicit NSIS(uint32_t array_size) :
      rank_array(array_size, 0),
      parent_array(array_size) {
      for (uint32_t i = 0; i < array_size; ++i) {
          this->parent_array[i] = i;
      }
  }

  uint32_t get(uint32_t index) {
      if (this->parent_array[index] != index) {
          this->parent_array[index] = this->get(parent_array[index]);
      }
      return this->parent_array[index];
  }

  void join(uint32_t left, uint32_t right) {
      left = this->get(left);
      right = this->get(right);
      if (left != right) {
          if (this->rank_array[left] > this->rank_array[right]) {
              swap(left, right);
          }
          if (this->rank_array[left] == this->rank_array[right]) {
              ++this->rank_array[right];
          }
          this->parent_array[left] = right;
      }
  }
};

struct Edge {

  uint32_t from;
  uint32_t to;
  uint32_t weight;

  Edge(uint32_t from, uint32_t to, uint32_t weight) :
      from(from),
      to(to),
      weight(weight) {};

  Edge() : from(0), to(0), weight(0) {};

  bool operator<(const Edge& other) const {
      return this->weight < other.weight;
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    size_t vertices_cnt, edges_cnt;
    cin >> vertices_cnt >> edges_cnt;
    vector<Edge> graph(edges_cnt);
    uint32_t from, to, weight;
    NSIS nsis(vertices_cnt);
    for (size_t i = 0; i < edges_cnt; ++i) {
        cin >> from >> to >> weight;
        --from;
        --to;
        graph[i] = {from, to, weight};
    }
    sort(graph.begin(), graph.end());
    uint64_t total_weight = 0;
    for (auto& edge: graph) {
        if (nsis.get(edge.from) != nsis.get(edge.to)) {
            total_weight += edge.weight;
            nsis.join(edge.from, edge.to);
        }
    }
    cout << total_weight << "\n";
    return 0;
}