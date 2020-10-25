#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::vector;

class FenfikTree {

 public:
  explicit FenfikTree(vector<long long>& prefix_sum) {
      t_array.resize(prefix_sum.size());
      for (size_t i = 0; i < prefix_sum.size(); ++i) {
          size_t lb = f_i(i);
          if (lb == 0) {
              t_array[i] = prefix_sum[i];
          } else {
              t_array[i] = prefix_sum[i] - prefix_sum[lb - 1];
          }
      }
  };

  long long rsq(size_t l, size_t r) {
      if (l == 0) {
          return get(r);
      }
      return get(r) - get(l - 1);
  }

  void add(size_t index, long long val) {
      while (index < t_array.size()) {
          t_array[index] += val;
          index = index | (index + 1);
      }
  }

 private:
  vector<long long> t_array;

  static size_t f_i(size_t i) {
      return i & (i + 1);
  }

  long long get(ssize_t index) {
      long long res = 0;
      while (index >= 0) {
          res += t_array[index];
          index = f_i(index) - 1;
      }
      return res;
  }
};

int main() {
    size_t n;
    cin >> n;
    vector<long long> prefix_sum(n);
    vector<long long> array(n);
    cin >> array[0];
    prefix_sum[0] = array[0];
    for (size_t i = 1; i < n; ++i) {
        cin >> array[i];
        prefix_sum[i] = prefix_sum[i - 1] + array[i];
    }
    FenfikTree tree(prefix_sum);
    string oper;
    size_t index;
    long long oper_val;
    while (cin >> oper) {
        cin >> index >> oper_val;
        if (oper == "sum") {
            cout << tree.rsq(index - 1, oper_val - 1) << "\n";
        } else {
            tree.add(index - 1, oper_val - array[index - 1]);
            array[index - 1] = oper_val;
        }
    }
    return 0;
}