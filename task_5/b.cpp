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
  Node* next_node;

  Node(string& new_key, string& new_value) : key(new_key), value(new_value), next_node(nullptr) {};
};

class LinkedList {
 private:
  Node* first_node;
  Node* last_node;

 public:
  LinkedList() : first_node(nullptr), last_node(nullptr) {};

  void add(string& key, string& value) {
    Node* new_node = new Node(key, value);
    if (this->first_node == nullptr) {
      this->first_node = new_node;
      this->last_node = new_node;
    } else {
      Node* cur = first_node;
      bool found = false;
      while (cur != nullptr) {
        if (cur->key == key) {
          cur->value = value;
          found = true;
          break;
        }
        cur = cur->next_node;
      }
      if (!found) {
        this->last_node->next_node = new_node;
        this->last_node = new_node;
      }
    }
  }

  string get(const string& key) {
    Node* cur = this->first_node;
    while (cur != nullptr) {
      if (cur->key == key) {
        return cur->value;
      }
      cur = cur->next_node;
    }
    return "";
  }

  void remove(const string& key) {
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
        delete cur;
        break;
      }
      prev = cur;
      cur = cur->next_node;
    }
  }
};

class Map {
 private:

  vector<LinkedList> array;
  unsigned p;
  unsigned a;

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
  }

  string get(string& key) {
    size_t index = this->hash_function(key);
    return this->array[index].get(key);
  }

  void put(string& key, string& value) {
    size_t index = this->hash_function(key);
    this->array[index].add(key, value);
  }

  void remove(string& key) {
    size_t index = this->hash_function(key);
    this->array[index].remove(key);
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
    } else {
      dict.remove(key);
    }
  }
  return 0;
}
