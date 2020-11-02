#include <cstdio>
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
  size_t tree_size;

  explicit Node(int value) : value(value), right_child(nullptr), left_child(nullptr), height(1), tree_size(1) {};

  Node(Node& copy) = default;

  void update() {
      size_t left_child_height = get_left_height();
      size_t right_child_height = get_right_height();
      size_t left_tree_size = get_left_tree_size();
      size_t right_tree_size = get_right_tree_size();
      height = std::max(left_child_height, right_child_height) + 1;
      tree_size = left_tree_size + right_tree_size + 1;
  }

  size_t get_left_height() const {
      return left_child == nullptr ? 0 : left_child->height;
  }

  size_t get_left_tree_size() const {
      return left_child == nullptr ? 0 : left_child->tree_size;
  }

  size_t get_right_height() const {
      return right_child == nullptr ? 0 : right_child->height;
  }

  size_t get_right_tree_size() const {
      return right_child == nullptr ? 0 : right_child->tree_size;
  }
};

class AVL {

 public:

  AVL() : root(nullptr) {};

  void insert(int value) {
      root = insert(value, root);
      root->update();
  }

  void remove(int value) {
      root = remove(value, root);
      if (root != nullptr) {
          root->update();
          balance(root);
      }
  }

  int kmax(size_t k) {
      return kmax(k, root, 0)->value;
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
      node_ptr->update();
      balance(node_ptr);
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
      node_ptr->update();
      balance(node_ptr);
      return node_ptr;
  }

  static Node* find_max(Node* node_ptr) {
      while (node_ptr->right_child != nullptr) {
          node_ptr = node_ptr->right_child;
      }
      return node_ptr;
  }

  static void balance(Node* node_ptr) {
      int height_diff = static_cast<int>(node_ptr->get_left_height()) - static_cast<int>(node_ptr->get_right_height());
      if (height_diff > 1) {
          if (node_ptr->left_child->get_right_height() > node_ptr->left_child->get_left_height()) {
              small_rotate_left(node_ptr->left_child);
          }
          small_rotate_right(node_ptr);
      } else if (height_diff < -1) {
          if (node_ptr->right_child->get_left_height() > node_ptr->right_child->get_right_height()) {
              small_rotate_right(node_ptr->right_child);
          }
          small_rotate_left(node_ptr);
      }
  }

  static void small_rotate_right(Node* node_ptr) {
      Node* tmp = new Node(*node_ptr);
      tmp->left_child = node_ptr->left_child->right_child;
      tmp->update();
      *node_ptr = *node_ptr->left_child;
      node_ptr->right_child = tmp;
      node_ptr->update();
  }

  static void small_rotate_left(Node* node_ptr) {
      Node* tmp = new Node(*node_ptr);
      tmp->right_child = node_ptr->right_child->left_child;
      tmp->update();
      *node_ptr = *node_ptr->right_child;
      node_ptr->left_child = tmp;
      node_ptr->update();
  }

  static Node* kmax(size_t k, Node* node_ptr, size_t add) {
      if (node_ptr->get_right_tree_size() + 1 + add == k) {
          return node_ptr;
      } else if (node_ptr->get_right_tree_size() + 1 + add < k) {
          return kmax(k, node_ptr->left_child, node_ptr->get_right_tree_size() + 1 + add);
      } else {
          return kmax(k, node_ptr->right_child, add);
      }
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    AVL tree = AVL();
    int oper_value;
    int oper;
    size_t operation_count;
    cin >> operation_count;
    for (size_t i = 0; i < operation_count; ++i) {
        cin >> oper >> oper_value;
        if (oper > 0) {
            tree.insert(oper_value);
        } else if (oper < 0) {
            tree.remove(oper_value);
        } else {
            cout << tree.kmax(oper_value) << "\n";
        }
    }
    return 0;
}