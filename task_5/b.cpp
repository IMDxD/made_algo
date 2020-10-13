#include "iostream"
#include "list"
#include "string"
#include "vector"

using std::advance;
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::string;
using std::vector;

template<class T1, class T2>
using dict = vector<list<pair<T1, T2>>>;

const size_t INITIAL_SIZE = 4098;
const size_t MAX_SIZE = 2'000'002;

class Map {
 private:

  dict<string, string>* array;
  size_t size_;
  const unsigned P = 2'000'003;
  const unsigned A = 7;

  unsigned hash_function(string& value) const {
    unsigned res = 0;
    for (char c: value) {
      res = (res * this->A + c) % this->P;
    }
    return res % this->array->size();
  }

  void rehash(size_t new_size) {
    dict<string, string>* old_array = this->array;
    this->array = new dict<string, string>(new_size);
    this->size_ = 0;
    for (auto& chain: *old_array) {
      for (auto& el: chain) {
        this->put(el.first, el.second);
      }
    }
    old_array->clear();
    delete old_array;
  }

 public:
  Map() : array(new dict<string, string>(INITIAL_SIZE)), size_(0) {};

  string get(string& key) {
    size_t index = this->hash_function(key);
    list<pair<string, string>> chain = (*this->array)[index];
    for (auto& el: chain) {
      if (el.first == key) {
        return el.second;
      }
    }
    return "none";
  }

  void put(string& key, string& value) {
    if (this->size_ == this->array->size() / 2 && this->array->size() < MAX_SIZE) {
      size_t new_size = std::max(this->array->size() * 2, MAX_SIZE);
      this->rehash(new_size);
    }
    size_t index = this->hash_function(key);
    list<pair<string, string>>* chain = &(*this->array)[index];
    bool found = false;
    for (auto& el: *chain) {
      if (el.first == key) {
        el.second = value;
        found = true;
        break;
      }
    }
    if (!found) {
      chain->push_back({key, value});
      ++this->size_;
    }
  }

  void remove(string& key) {
    size_t index = this->hash_function(key);
    auto* chain = &(*this->array)[index];
    auto it = chain->begin();
    size_t i = 0;
    for (auto& el: *chain) {
      if (el.first == key) {
        advance(it, i);
        chain->erase(it);
        --this->size_;
        if (this->size_ == this->array->size() / 8 && this->array->size() > INITIAL_SIZE) {
          size_t new_size = std::min(this->array->size() / 8, INITIAL_SIZE);
          this->rehash(new_size);
        }
        break;
      }
      ++i;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Map dict = Map();
  string oper;
  string key;
  string value;
  while (cin >> oper) {
    cin >> key;
    if (oper == "put") {
      cin >> value;
      dict.put(key, value);
    } else if (oper == "get") {
      value = dict.get(key);
      cout << value << "\n";
    } else {
      dict.remove(key);
    }
  }
  return 0;
}
