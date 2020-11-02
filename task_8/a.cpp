#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

struct Node {

  int value;
  Node* left_child;
  Node* right_child;

  explicit Node(int value) : value(value), right_child(nullptr), left_child(nullptr) {};
};

class BST {

 public:

  BST() : root(nullptr) {};

  void insert(int value) {
      root = insert(value, root);
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

  Node* insert(int value, Node* node_ptr) {
      if (node_ptr == nullptr) {
          Node* new_node = new Node(value);
          return new_node;
      } else if (value < node_ptr->value) {
          node_ptr->left_child = insert(value, node_ptr->left_child);
      } else if (value > node_ptr->value) {
          node_ptr->right_child = insert(value, node_ptr->right_child);
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
      } else if (node_ptr->right_child == nullptr && node_ptr->left_child == nullptr) {
          return nullptr;
      } else if (node_ptr->left_child == nullptr) {
          return node_ptr->right_child;
      } else if (node_ptr->right_child == nullptr) {
          return node_ptr->left_child;
      } else {
          node_ptr->value = find_max(node_ptr->left_child)->value;
          node_ptr->left_child = remove(node_ptr->value, node_ptr->left_child);
      }
      return node_ptr;
  }

  static Node* find_max(Node* node_ptr) {
      while (node_ptr->right_child != nullptr) {
          node_ptr = node_ptr->right_child;
      }
      return node_ptr;
  }
};

int main() {
    BST tree = BST();
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