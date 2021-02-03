#include "algorithm"
#include "cstdio"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::max;
using std::string;
using std::swap;
using std::vector;

class NSIS {

 private:
  vector<uint32_t> rank_array;
  vector<uint32_t> parent_array;
  vector<uint32_t> min_array;
  vector<uint32_t> max_array;
  vector<uint32_t> count_array;

 public:
  explicit NSIS(uint32_t array_size) :
      rank_array(array_size, 0),
      parent_array(array_size),
      min_array(array_size),
      max_array(array_size),
      count_array(array_size, 1) {
      for (uint32_t i = 0; i < array_size; ++i) {
          this->parent_array[i] = i;
          this->min_array[i] = i;
          this->max_array[i] = i;
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
          this->min_array[right] = min(this->min_array[left], this->min_array[right]);
          this->max_array[right] = max(this->max_array[left], this->max_array[right]);
          this->count_array[right] = this->count_array[right] + this->count_array[left];
      }
  }

  void print_info(uint32_t index) {
      uint32_t parent_index = this->get(index);
      uint32_t min_value = this->min_array[parent_index];
      uint32_t max_value = this->max_array[parent_index];
      uint32_t count = this->count_array[parent_index];
      cout << min_value + 1 << " " << max_value + 1 << " " << count << "\n";
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    uint32_t array_size;
    cin >> array_size;
    NSIS nsis(array_size);
    string oper_name;
    uint32_t oper_first, oper_second;
    while (cin >> oper_name) {
        if (oper_name == "union") {
            cin >> oper_first >> oper_second;
            nsis.join(oper_first - 1, oper_second - 1);
        } else {
            cin >> oper_first;
            nsis.print_info(oper_first - 1);
        }
    }
    return 0;
}