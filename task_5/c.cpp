#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;

const size_t OPER_CNT = 100'000;
const unsigned A = 7;
const unsigned P = 200'003;

struct Node {
 public:
  string key;
  string value;
  Node* prev_map_node;
  Node* next_map_node;
  Node* next_node;

  Node(string& new_key, string& new_value, Node* new_prev_map_node) :
      key(new_key), value(new_value), next_node(nullptr),
      prev_map_node(new_prev_map_node), next_map_node(nullptr) {};
};

class LinkedList {
 private:
  Node* first_node;
  Node* last_node;

 public:
  LinkedList() : first_node(nullptr), last_node(nullptr) {};

  Node* add(string& key, string& value, Node* prev_node) {
    if (this->first_node == nullptr) {
      Node* new_node = new Node(key, value, prev_node);
      this->first_node = new_node;
      this->last_node = new_node;
    } else {
      Node* cur = this->first_node;
      while (cur != nullptr) {
        if (cur->key == key) {
          cur->value = value;
          return nullptr;
        }
        cur = cur->next_node;
      }
      Node* new_node = new Node(key, value, prev_node);
      this->last_node->next_node = new_node;
      this->last_node = new_node;
    }
    return this->last_node;
  }

  Node* get(const string& key) {
    Node* cur = this->first_node;
    while (cur != nullptr) {
      if (cur->key == key) {
        return cur;
      }
      cur = cur->next_node;
    }
    return nullptr;
  }

  Node* remove(const string& key) {
    Node* cur = this->first_node;
    Node* prev = nullptr;
    while (cur != nullptr) {
      if (cur->key == key) {
        if (prev != nullptr) {
          prev->next_node = cur->next_node;
        } else {
          this->first_node = cur->next_node;
          if (this->last_node == cur) {
            this->last_node = nullptr;
          }
        }
        return cur;
      }
      prev = cur;
      cur = cur->next_node;
    }
    return nullptr;
  }
};

class Map {
 private:

  vector<LinkedList> array;
  unsigned p;
  unsigned a;
  Node* last_node;

  unsigned hash_function(string& value) const {
    unsigned res = 0;
    for (char c: value) {
      res = (res * this->a + c) % this->p;
    }
    return res % this->array.size();
  }

 public:
  Map(size_t new_size, int new_a, unsigned new_p) {
    this->array = vector<LinkedList>(new_size * 2);
    this->a = new_a;
    this->p = new_p;
    this->last_node = nullptr;
  }

  string get(string key) {
    size_t index = this->hash_function(key);
    Node* gotten_node = this->array[index].get(key);
    if (gotten_node == nullptr) {
      return "";
    }
    return gotten_node->value;
  }

  string next(string key) {
    size_t index = this->hash_function(key);
    Node* gotten_node = this->array[index].get(key);
    if (gotten_node == nullptr || gotten_node->next_map_node == nullptr) {
      return "";
    }
    return gotten_node->next_map_node->value;
  }

  string prev(string key) {
    size_t index = this->hash_function(key);
    Node* gotten_node = this->array[index].get(key);
    if (gotten_node == nullptr || gotten_node->prev_map_node == nullptr) {
      return "";
    }
    return gotten_node->prev_map_node->value;
  }

  void put(string& key, string& value) {
    size_t index = this->hash_function(key);
    Node* added_node = this->array[index].add(key, value, this->last_node);
    if (added_node != nullptr) {
      if (this->last_node != nullptr && this->last_node->key != key) {
        this->last_node->next_map_node = added_node;
      }
      this->last_node = added_node;
    }
  }

  void remove(string key) {
    size_t index = this->hash_function(key);
    Node* deleted_node = this->array[index].remove(key);
    if (deleted_node != nullptr) {
      if (deleted_node->next_map_node != nullptr) {
        deleted_node->next_map_node->prev_map_node = deleted_node->prev_map_node;
      }
      if (deleted_node->prev_map_node != nullptr) {
        deleted_node->prev_map_node->next_map_node = deleted_node->next_map_node;
      }
      if (deleted_node == this->last_node) {
        this->last_node = deleted_node->prev_map_node;
      }
      delete deleted_node;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Map dict = Map(OPER_CNT, A, P);
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
