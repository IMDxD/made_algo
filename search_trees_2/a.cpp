#include "cstdio"
#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

struct Node {

  int value;
  int priority;
  Node* left_child;
  Node* right_child;

  explicit Node(int value, int priority, Node* left, Node* right) :
      value(value),
      right_child(right),
      left_child(left),
      priority(priority) {};
};

class Treap {

 public:

  Treap() : root(nullptr) {};

  void insert(int value) {
      if (!exist(value)) {
          root = insert(value, rand(), root);
      }
  }

  void remove(int value) {
      root = remove(value, root);
  }

  bool exist(int value) {
      Node* cur_node_ptr = root;
      while (cur_node_ptr != nullptr && cur_node_ptr->value != value) {
          if (cur_node_ptr->value > value) {
              cur_node_ptr = cur_node_ptr->left_child;
          } else {
              cur_node_ptr = cur_node_ptr->right_child;
          }
      }
      return cur_node_ptr != nullptr;
  }

  Node* next(int value) {
      Node* cur_node = root;
      Node* res = nullptr;
      while (cur_node != nullptr) {
          if (cur_node->value > value) {
              res = cur_node;
              cur_node = cur_node->left_child;
          } else {
              cur_node = cur_node->right_child;
          }
      }
      return res;
  }

  Node* prev(int value) {
      Node* cur_node = root;
      Node* res = nullptr;
      while (cur_node != nullptr) {
          if (cur_node->value < value) {
              res = cur_node;
              cur_node = cur_node->right_child;
          } else {
              cur_node = cur_node->left_child;
          }
      }
      return res;
  }

 private:

  Node* root;

  std::pair<Node*, Node*> split(Node* node_ptr, int value) {
      if (node_ptr == nullptr) {
          return {nullptr, nullptr};
      } else if (node_ptr->value > value) {
          std::pair<Node*, Node*> node_pair = split(node_ptr->left_child, value);
          node_ptr->left_child = node_pair.second;
          return {node_pair.first, node_ptr};
      } else {
          std::pair<Node*, Node*> node_pair = split(node_ptr->right_child, value);
          node_ptr->right_child = node_pair.first;
          return {node_ptr, node_pair.second};
      }
  }

  Node* merge(Node* first, Node* second) {
      if (first == nullptr) {
          return second;
      } else if (second == nullptr) {
          return first;
      } else if (first->priority > second->priority) {
          first->right_child = merge(first->right_child, second);
          return first;
      } else {
          second->left_child = merge(first, second->left_child);
          return second;
      }
  }

  Node* insert(int value, int priority, Node* node_ptr) {
      if (node_ptr == nullptr || node_ptr->priority < priority) {
          std::pair<Node*, Node*> node_pair = split(node_ptr, value);
          Node* new_node = new Node(value, priority, node_pair.first, node_pair.second);
          return new_node;
      } else if (value < node_ptr->value) {
          node_ptr->left_child = insert(value, priority, node_ptr->left_child);
      } else if (value > node_ptr->value) {
          node_ptr->right_child = insert(value, priority, node_ptr->right_child);
      }
      return node_ptr;
  }

  Node* remove(int value, Node* node_ptr) {
      if (node_ptr == nullptr) {
          return nullptr;
      } else if (value < node_ptr->value) {
          node_ptr->left_child = remove(value, node_ptr->left_child);
      } else if (value > node_ptr->value) {
          node_ptr->right_child = remove(value, node_ptr->right_child);
      } else {
          Node* new_node = merge(node_ptr->left_child, node_ptr->right_child);
          delete node_ptr;
          node_ptr = new_node;
      }
      return node_ptr;
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    Treap tree = Treap();
    int oper_value;
    string oper_name;
    while (cin >> oper_name) {
        cin >> oper_value;
        if (oper_name == "insert") {
            tree.insert(oper_value);
        } else if (oper_name == "delete") {
            tree.remove(oper_value);
        } else if (oper_name == "next") {
            Node* res = tree.next(oper_value);
            if (res == nullptr) {
                cout << "none\n";
            } else {
                cout << res->value << "\n";
            }
        } else if (oper_name == "prev") {
            Node* res = tree.prev(oper_value);
            if (res == nullptr) {
                cout << "none\n";
            } else {
                cout << res->value << "\n";
            }
        } else {
            bool exist = tree.exist(oper_value);
            if (exist) {
                cout << "true" << "\n";
            } else {
                cout << "false" << "\n";
            }
        }
    }
    return 0;
}