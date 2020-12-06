#include "cstdio"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::pair;
using std::string;
using std::swap;
using std::vector;

class NSIS {

 private:
  vector<uint32_t> rank_array;
  vector<uint32_t> parent_array;
  vector<uint32_t> exp_array;

  pair<uint32_t, uint32_t> get(uint32_t index, uint32_t add_exp) {
      if (this->parent_array[index] != index) {
          pair<uint32_t, uint32_t> clan_exp = this->get(parent_array[index], add_exp);
          this->exp_array[index] += clan_exp.second;
          this->parent_array[index] = clan_exp.first;
          add_exp = this->exp_array[index];
      }
      return {this->parent_array[index], add_exp};
  }

  uint32_t get(uint32_t index) {
      return this->get(index, 0).first;
  }

 public:
  explicit NSIS(uint32_t array_size) :
      rank_array(array_size, 0),
      exp_array(array_size, 0),
      parent_array(array_size) {
      for (uint32_t i = 0; i < array_size; ++i) {
          this->parent_array[i] = i;
      }
  }

  void add(uint32_t index, uint32_t exp) {
      uint32_t clan = this->get(index);
      this->exp_array[clan] += exp;
  }

  uint32_t get_exp(uint32_t index) {
      uint32_t exp = 0;
      while (index != this->parent_array[index]) {
          exp += this->exp_array[index];
          index = this->parent_array[index];
      }
      exp += this->exp_array[index];
      return exp;
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
          this->exp_array[left] -= this->exp_array[right];
          this->parent_array[left] = right;
      }
  }

};

int main() {
    std::ios::sync_with_stdio(false);
    uint32_t array_size, query_cnt;
    cin >> array_size >> query_cnt;
    NSIS nsis(array_size);
    string oper_name;
    uint32_t oper_first, oper_second;
    for (size_t i = 0; i < query_cnt; ++i) {
        cin >> oper_name;
        if (oper_name == "add") {
            cin >> oper_first >> oper_second;
            nsis.add(oper_first - 1, oper_second);
        } else if (oper_name == "join") {
            cin >> oper_first >> oper_second;
            nsis.join(oper_first - 1, oper_second - 1);
        } else {
            cin >> oper_first;
            cout << nsis.get_exp(oper_first - 1) << "\n";
        }
    }
    return 0;
}