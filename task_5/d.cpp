#include "algorithm"
#include "iostream"
#include "list"
#include "string"
#include "vector"

using std::none_of;
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::string;
using std::swap;
using std::vector;

const size_t OPER_CNT = 100'000;
const unsigned A = 7;
const unsigned P = 200'003;


class Map {
 private:

  vector<list<pair<string, string>>> array;
  unsigned p;
  unsigned a;

  unsigned hash_function(string& key) const {
    unsigned res = 0;
    for (char c: key) {
      res = (res * this->a + c) % this->p;
    }
    return res % this->array.size();
  }

 public:
  Map(size_t new_size, int new_a, unsigned new_p) {
    this->array = vector<list<pair<string, string>>>(new_size * 2);
    this->a = new_a;
    this->p = new_p;
  }

  void put(string& key, string& value) {
    size_t index = this->hash_function(key);
    while (!(this->array[index].empty() || this->array[index].front().first == key)) {
      index = (index + 1) % this->array.size();
    }
    pair<string, string> item = {key, value};
    if (none_of(this->array[index].begin(), this->array[index].end(),
                [item](auto x) {return x == item;})){
      this->array[index].push_back({key, value});
    }
  }

  void rebase(size_t swap_index) {
    size_t next_index = (swap_index + 1) % this->array.size();
    while (!this->array[next_index].empty()) {
      string key = this->array[next_index].front().first;
      unsigned next_hash = hash_function(key);
      if (next_hash > next_index || next_hash <= swap_index) {
        swap(this->array[swap_index], this->array[next_index]);
        swap_index = next_index;
      }
      ++next_index;
    }
  }

  void remove(string& key, string& value) {
    size_t index = this->hash_function(key);
    unsigned step = 0;
    while (!this->array[index].empty() && step < this->array.size()) {
      if (this->array[index].front().first == key){
        this->array[index].remove({key, value});
        if (this->array[index].empty()) {
          rebase(index);
        }
        break;
      }
      index = (index + 1) % this->array.size();
      step++;
    }
  }

  void remove_all(string& key) {
    size_t index = this->hash_function(key);
    unsigned step = 0;
    while (!this->array[index].empty() && step < this->array.size()) {
      if (this->array[index].front().first == key){
        this->array.erase(this->array.begin() + index);
        rebase(index);
        break;
      }
      index = (index + 1) % this->array.size();
      step++;
    }
  }

  void print(string& key) {
    size_t index = this->hash_function(key);
    while (!(this->array[index].empty() || this->array[index].front().first == key)) {
      index = (index + 1) % this->array.size();
    }
    cout << this->array[index].size();
    for (auto& el: this->array[index]){
      cout << " " << el.second;
    }
    cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Map multi_map = Map(OPER_CNT, A, P);
  string oper;
  string key;
  string value;
  while (cin >> oper) {
    cin >> key;
    if (oper == "put") {
      cin >> value;
      multi_map.put(key, value);
    } else if (oper == "get") {
      multi_map.print(key);
    } else if (oper == "delete") {
      cin >> value;
      multi_map.remove(key, value);
    } else {
      multi_map.remove_all(key);
    }
  }
  return 0;
}
