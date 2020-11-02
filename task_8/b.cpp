#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

struct Node {

  int value;
  Node* left_child;
  Node* right_child;
  size_t height;

  explicit Node(int value) : value(value), right_child(nullptr), left_child(nullptr), height(1) {};
};

class AVL {

 public:

  AVL() : root(nullptr) {};

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
      if (prev_node_ptr->height == 1){
          update_height(value, 1);
      }
      balance(cur_node_ptr, prev_node_ptr);
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
          remove_node(cur_node_ptr, prev_node_ptr);
      }
  };

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

  void update_height(int value, size_t addition){
      Node* cur_node_ptr = root;
      while (cur_node_ptr != nullptr && cur_node_ptr->value != value) {
          cur_node_ptr->height += addition;
          if (cur_node_ptr->value > value) {
              cur_node_ptr = cur_node_ptr->left_child;
          } else {
              cur_node_ptr = cur_node_ptr->right_child;
          }
      }
  }

  void remove_node(Node* node_ptr, Node* prev_node_ptr) {
      int update_value = node_ptr->value;
      if (node_ptr->left_child == nullptr && node_ptr->right_child == nullptr) {
          if (prev_node_ptr == nullptr) {
              root = nullptr;
          } else if (prev_node_ptr->value > node_ptr->value) {
              prev_node_ptr->left_child = nullptr;
          } else {
              prev_node_ptr->right_child = nullptr;
          }
          if (prev_node_ptr->left_child == nullptr && prev_node_ptr->right_child == nullptr){
              update_height(update_value, -1);
          }
      } else if (node_ptr->left_child == nullptr) {
          *node_ptr = *node_ptr->right_child;
          update_height(update_value, -1);
      } else if (node_ptr->right_child == nullptr) {
          *node_ptr = *node_ptr->left_child;
          update_height(update_value, -1);
      } else {
          Node* replace_node = node_ptr->left_child;
          Node* prev_replace_node = nullptr;
          while (replace_node->right_child != nullptr) {
              prev_replace_node = replace_node;
              replace_node = replace_node->right_child;
          }
          node_ptr->value = replace_node->value;
          if (prev_replace_node != nullptr) {
              prev_replace_node->right_child = replace_node->left_child;
              --prev_replace_node->height;
              update_height(prev_replace_node->value, -1);
          } else {
              node_ptr->left_child = nullptr;
          }
      }
      balance(prev_node_ptr);
  }

  void balance(Node* node_ptr){
      size_t left_child_height = node_ptr->left_child == nullptr ? 0: node_ptr->left_child->height;
      size_t right_child_height = node_ptr->right_child == nullptr ? 0: node_ptr->right_child->height;
      if (left_child_height - right_child_height == -2){
          small_rotate_right(node_ptr, node_ptr);
      }
  }

  void small_rotate_right(Node* node_ptr, Node* prev_node_ptr){

  }

};

int main() {
    AVL tree = AVL();
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