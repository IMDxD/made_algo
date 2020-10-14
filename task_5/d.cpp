#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::pair;
using std::string;
using std::swap;
using std::vector;

const size_t INITIAL_SIZE = 16;
const size_t MAX_SIZE = 200'000;

class Set {
 private:

  vector<string>* array;
  size_t size_;
  const unsigned P = 2'000'003;
  const unsigned A = 7;

  unsigned hash_function(string& key) const {
    unsigned res = 0;
    for (char c: key) {
      res = (res * this->A + c) % this->P;
    }
    return res % this->array->size();
  }

  size_t find_index(string& value) {
    size_t index = this->hash_function(value);
    while (!((*this->array)[index].empty() || (*this->array)[index] == value)) {
      index = (index + 1) % this->array->size();
    }
    return index;
  }

  void rehash(size_t new_size) {
    vector<string>* old_array = this->array;
    this->array = new vector<string>(new_size);
    for (auto& el: *old_array) {
      if (!el.empty()) {
        size_t index = this->find_index(el);
        (*this->array)[index] = el;
      }
    }
    delete old_array;
  }

  void restore_hash(size_t swap_index) {
    size_t next_index = (swap_index + 1) % this->array->size();
    while (!(*this->array)[next_index].empty()) {
      size_t next_hash = hash_function((*this->array)[next_index]);
      if (next_hash > next_index || (next_hash <= swap_index && swap_index < next_index)) {
        swap((*this->array)[swap_index], (*this->array)[next_index]);
        swap_index = next_index;
      }
      next_index = (next_index + 1) % this->array->size();
    }
  }

 public:
  Set() : array(new vector<string>(INITIAL_SIZE)), size_(0) {};

  bool empty() const {
    return this->size_ == 0;
  }

  void print() {
    cout << this->size_;
    for (auto& el: *this->array) {
      if (!el.empty()) {
        cout << " " << el;
      }
    }
    cout << "\n";
  }

  void put(string& value) {
    if (this->size_ == this->array->size() / 2 && this->array->size() < MAX_SIZE) {
      size_t new_size = std::min(this->array->size() * 2, MAX_SIZE);
      this->rehash(new_size);
    }
    size_t index = this->find_index(value);
    if ((*this->array)[index] != value) {
      (*this->array)[index] = value;
      ++this->size_;
    }
  }

  void remove(string& value) {
    size_t index = this->hash_function(value);
    size_t step = 0;
    while (!(*this->array)[index].empty() && step < this->array->size()) {
      if ((*this->array)[index] == value) {
        (*this->array)[index] = "";
        restore_hash(index);
        --this->size_;
        if (this->size_ == this->array->size() / 8 && this->array->size() > INITIAL_SIZE) {
          size_t new_size = std::max(this->array->size() / 2, INITIAL_SIZE);
          this->rehash(new_size);
        }
        break;
      }
      index = (index + 1) % this->array->size();
      ++step;
    }
  }
};

class Map {
 private:

  vector<pair<string, Set>*>* array;
  const unsigned P = 2'000'003;
  const unsigned A = 7;

  unsigned hash_function(string& key) const {
    unsigned res = 0;
    for (char c: key) {
      res = (res * this->A + c) % this->P;
    }
    return res % this->array->size();
  }

  size_t find_index(string& key) {
    size_t index = this->hash_function(key);
    while (!((*this->array)[index] == nullptr || (*this->array)[index]->first == key)) {
      index = (index + 1) % this->array->size();
    }
    return index;
  }

  void restore_hash(size_t index) {
    size_t next_index = (index + 1) % this->array->size();
    size_t swap_index = index;
    while ((*this->array)[next_index] != nullptr) {
      size_t next_hash = hash_function((*this->array)[next_index]->first);
      if (next_hash > next_index || (next_hash <= swap_index && swap_index < next_index)) {
        swap((*this->array)[swap_index], (*this->array)[next_index]);
        swap_index = next_index;
      }
      next_index = (next_index + 1) % this->array->size();
    }
  }

 public:
  Map() : array(new vector<pair<string, Set>*>(MAX_SIZE)) {};

  void put(string& key, string& value) {
    size_t index = this->find_index(key);
    if ((*this->array)[index] == nullptr) {
      (*this->array)[index] = new pair<string, Set>;
      (*this->array)[index]->first = key;
      (*this->array)[index]->second.put(value);
    } else {
      (*this->array)[index]->second.put(value);
    }
  }

  void remove(string& key, string& value) {
    size_t index = this->find_index(key);
    if ((*this->array)[index] != nullptr) {
      (*this->array)[index]->second.remove(value);
      if ((*this->array)[index]->second.empty()) {
        delete (*this->array)[index];
        (*this->array)[index] = nullptr;
        restore_hash(index);
      }
    }
  }

  void remove_all(string& key) {
    size_t index = this->find_index(key);
    if ((*this->array)[index] != nullptr) {
      delete (*this->array)[index];
      (*this->array)[index] = nullptr;
      restore_hash(index);
    }
  }

  void print(string& key) {
    size_t index = this->find_index(key);
    if ((*this->array)[index] != nullptr) {
      auto hashset = (*this->array)[index]->second;
      hashset.print();
    } else {
      cout << 0 << "\n";
    }
  }
};

int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(nullptr);
  Map multi_map = Map();
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
