#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;

const size_t OPER_CNT = 1'000'000;
const unsigned A = 7;
const unsigned P = 2'000'003;

unsigned modulo(int value, unsigned m) {
  int mod = value % (int) m;
  if (mod < 0) {
    mod += m;
  }
  return mod;
}

class Set {
 private:

  vector<int> array;
  unsigned p;
  unsigned a;
  int null_value = INT32_MAX;

  int hash_function(int value) const {
    return modulo(value * this->a, this->p) % this->array.size();
  }

 public:
  Set(size_t new_size, int new_a, unsigned new_p) {
    this->array = vector<int>(new_size * 2, this->null_value);
    this->a = new_a;
    this->p = new_p;
  }

  bool contains(int value) {
    size_t index = this->hash_function(value);
    while (this->array[index] != this->null_value) {
      if (this->array[index] == value) {
        return true;
      } else {
        index = (index + 1) % this->array.size();
      }
    }
    return false;
  }

  void put(int value) {
    size_t index = this->hash_function(value);
    while (!(this->array[index] == null_value || this->array[index] == value)) {
      index = (index + 1) % this->array.size();
    }
    if (this->array[index] != value) {
      this->array[index] = value;
    }
  }

  void remove(int value) {
    size_t index = this->hash_function(value);
    size_t step = 0;
    while (this->array[index] != this->null_value && step < this->array.size()) {
      if (this->array[index] == value) {
        this->array[index] = this->null_value;
        size_t next_index = (index + 1) % this->array.size();
        size_t swap_index = index;
        while (this->array[next_index] != this->null_value) {
          int next_hash = hash_function(this->array[next_index]);
          if (next_hash > next_index || next_hash <= index) {
            swap(this->array[swap_index], this->array[next_index]);
            swap_index = next_index;
          }
          ++next_index;
        }
        break;
      }
      index = (index + 1) % this->array.size();
      ++step;
    }

  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Set hashset = Set(OPER_CNT, A, P);
  string oper;
  int value;
  while (cin >> oper >> value) {
    if (oper == "insert") {
      hashset.put(value);
    } else if (oper == "exists") {
      if (hashset.contains(value)) {
        cout << "true\n";
      } else {
        cout << "false\n";
      }
    } else {
      hashset.remove(value);
    }
  }
  return 0;
}
