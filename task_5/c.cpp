#include "iostream"
#include "list"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::list;
using std::string;
using std::swap;
using std::vector;

const size_t INITIAL_SIZE = 4098;
const size_t MAX_SIZE = 2'000'002;

struct Node {
 public:
  string key;
  string value;
  Node* prev_map_node;
  Node* next_map_node;

  Node(string& new_key, string& new_value, Node* new_prev_map_node) :
      key(new_key), value(new_value), prev_map_node(new_prev_map_node),
      next_map_node(nullptr) {};
};

class Map {
 private:

  vector<list<Node*>>* array;
  size_t size_;
  const unsigned P = 2'000'003;
  const unsigned A = 7;
  Node* last_node;

  unsigned hash_function(string& value) const {
    unsigned res = 0;
    for (char c: value) {
      res = (res * this->A + c) % this->P;
    }
    return res % this->array->size();
  }

  void rehash(size_t new_size) {
    vector<list<Node*>>* old_array = this->array;
    this->array = new vector<list<Node*>>(new_size);
    this->size_ = 0;
    for (auto& chain: *old_array) {
      for (auto& el: chain) {
        this->put(el);
      }
    }
    old_array->clear();
    delete old_array;
  }

 public:
  Map() : array(new vector<list<Node*>>(INITIAL_SIZE)), last_node(nullptr), size_(0) {};

  string get(string key) {
    size_t index = this->hash_function(key);
    list<Node*>* chain = &(*this->array)[index];
    for (auto& el: *chain) {
      if (el->key == key) {
        return el->value;
      }
    }
    return "none";
  }

  string next(string key) {
    size_t index = this->hash_function(key);
    list<Node*> chain = (*this->array)[index];
    for (auto& el: chain) {
      if (el->key == key && el->next_map_node != nullptr) {
        return el->next_map_node->value;
      }
    }
    return "none";
  }

  string prev(string key) {
    size_t index = this->hash_function(key);
    list<Node*> chain = (*this->array)[index];
    for (auto& el: chain) {
      if (el->key == key && el->prev_map_node != nullptr) {
        return el->prev_map_node->value;
      }
    }
    return "none";
  }

  void put(string& key, string& value) {
    Node* node = new Node(key, value, last_node);
    put(node);
  }

  void put(Node* node) {
    if (this->size_ == this->array->size() / 2 && this->array->size() < MAX_SIZE) {
      size_t new_size = std::max(this->array->size() * 2, MAX_SIZE);
      this->rehash(new_size);
    }
    size_t index = this->hash_function(node->key);
    list<Node*>* chain = &(*this->array)[index];
    for (auto& el: *chain) {
      if (el->key == node->key) {
        el->value = node->value;
        return;
      }
    }
    chain->push_back(node);
    if (last_node != nullptr) {
      this->last_node->next_map_node = node;
    }
    this->last_node = node;
  }

  void remove(string key) {
    size_t index = this->hash_function(key);
    size_t i = 0;
    auto* chain = &(*this->array)[index];
    auto it = chain->begin();
    for (auto el: *chain) {
      if (el->key == key) {
        Node* deleted_node = el;
        if (deleted_node->next_map_node != nullptr) {
          deleted_node->next_map_node->prev_map_node = deleted_node->prev_map_node;
        }
        if (deleted_node->prev_map_node != nullptr) {
          deleted_node->prev_map_node->next_map_node = deleted_node->next_map_node;
        }
        if (deleted_node == this->last_node) {
          this->last_node = deleted_node->prev_map_node;
        }
        advance(it, i);
        chain->erase(it);
        --this->size_;
        if (this->size_ == this->array->size() / 8 && this->array->size() > INITIAL_SIZE) {
          size_t new_size = std::min(this->array->size() / 8, INITIAL_SIZE);
          this->rehash(new_size);
        }
        delete deleted_node;
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
      if (value.empty()) {
        cout << "none" << "\n";
      } else {
        cout << value << "\n";
      }
    } else if (oper == "next") {
      value = dict.next(key);
      if (value.empty()) {
        cout << "none" << "\n";
      } else {
        cout << value << "\n";
      }
    } else if (oper == "prev") {
      value = dict.prev(key);
      if (value.empty()) {
        cout << "none" << "\n";
      } else {
        cout << value << "\n";
      }
    } else {
      dict.remove(key);
    }
  }
  return 0;
}
