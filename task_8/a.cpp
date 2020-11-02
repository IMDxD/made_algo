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
      if (root == nullptr) {
          root = new Node(value);
          return;
      }
      Node* cur_node_ptr = root;
      Node* prev_node_ptr = nullptr;
      while (cur_node_ptr != nullptr && cur_node_ptr->value != value) {
          prev_node_ptr = cur_node_ptr;
          if (cur_node_ptr->value > value) {
              cur_node_ptr = cur_node_ptr->left_child;
          } else if (cur_node_ptr->value < value) {
              cur_node_ptr = cur_node_ptr->right_child;
          }
      }
      if (cur_node_ptr == nullptr && prev_node_ptr->value > value) {
          prev_node_ptr->left_child = new Node(value);
      } else if (cur_node_ptr == nullptr) {
          prev_node_ptr->right_child = new Node(value);
      }
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

  void remove(int value) {
      Node* cur_node_ptr = root;
      Node* prev_node_ptr = nullptr;
      while (cur_node_ptr != nullptr && cur_node_ptr->value != value) {
          prev_node_ptr = cur_node_ptr;
          if (cur_node_ptr->value > value) {
              cur_node_ptr = cur_node_ptr->left_child;
          } else if (cur_node_ptr->value < value) {
              cur_node_ptr = cur_node_ptr->right_child;
          }
      }
      if (cur_node_ptr != nullptr) {
          if (prev_node_ptr == nullptr) {
              root = nullptr;
          } else if (prev_node_ptr->value > value) {
              prev_node_ptr->left_child = remove_node(cur_node_ptr);
              if (prev_node_ptr->left_child != cur_node_ptr){
                  delete cur_node_ptr;
              }
          } else {
              prev_node_ptr->right_child = remove_node(cur_node_ptr);
              if (prev_node_ptr->left_child != cur_node_ptr){
                  delete cur_node_ptr;
              }
          }
      }
  };

  Node* remove_node(Node* node_ptr) {
      if (node_ptr->left_child == nullptr && node_ptr->right_child == nullptr) {
          return nullptr;
      }
      if (node_ptr->left_child == nullptr) {
          return node_ptr->right_child;
      } else if (node_ptr->right_child == nullptr) {
          return node_ptr->left_child;
      } else {
          Node* replace_node = find_max(node_ptr->left_child);
          node_ptr->value = replace_node->value;
          Node* to_delete = replace_node->left_child;
          *replace_node = *replace_node->left_child;
          delete to_delete;
          return node_ptr;
      }
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

  static Node* find_max(Node* cur_ptr) {
      while (cur_ptr->right_child != nullptr) {
          cur_ptr = cur_ptr->right_child;
      }
      return cur_ptr;
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