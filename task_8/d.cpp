#include <cstdio>
#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

const int MOD = 1'000'000'000;

struct Node {

  int value;
  Node* left_child;
  Node* right_child;
  size_t height;
  long long tree_sum;

  explicit Node(int value) : value(value), right_child(nullptr), left_child(nullptr), height(1), tree_sum(value) {};

  Node(Node& copy) = default;

  void update() {
      size_t left_child_height = get_left_height();
      size_t right_child_height = get_right_height();
      long long left_tree_sum = get_left_tree_sum();
      long long right_tree_sum = get_right_tree_sum();
      height = std::max(left_child_height, right_child_height) + 1;
      tree_sum = left_tree_sum + right_tree_sum + value;
  }

  size_t get_left_height() const {
      return left_child == nullptr ? 0 : left_child->height;
  }

  long long get_left_tree_sum() const {
      return left_child == nullptr ? 0 : left_child->tree_sum;
  }

  size_t get_right_height() const {
      return right_child == nullptr ? 0 : right_child->height;
  }

  long long get_right_tree_sum() const {
      return right_child == nullptr ? 0 : right_child->tree_sum;
  }
};

class AVL {

 public:

  AVL() : root(nullptr) {};

  void insert(int value) {
      root = insert(value, root);
      root->update();
  }

  long long sum(int l, int r) {
      long long left_sum = higher_sum(l, root, 0, true);
      long long right_sum = higher_sum(r, root, 0, false);
      return left_sum - right_sum;
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

  long long higher_sum(int border, Node* node_ptr, long long add, bool is_left) {
      if (node_ptr == nullptr) {
          return add;
      } else if (node_ptr->value == border) {
          return add + is_left * node_ptr->value + node_ptr->get_right_tree_sum();
      } else if (node_ptr->value > border) {
          return higher_sum(border, node_ptr->left_child,
                            node_ptr->get_right_tree_sum() + node_ptr->value + add, is_left);
      } else {
          return higher_sum(border, node_ptr->right_child, add, is_left);
      }
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    AVL tree = AVL();
    int oper_value;
    int oper_value_second;
    char oper;
    char last_oper;
    long long last_oper_result;
    size_t operation_count;
    cin >> operation_count;
    for (size_t i = 0; i < operation_count; ++i) {
        cin >> oper >> oper_value;
        if (oper == '+') {
            if (last_oper == '?') {
                oper_value = static_cast<int>((last_oper_result + oper_value) % MOD);
            }
            tree.insert(oper_value);
        } else {
            cin >> oper_value_second;
            last_oper_result = tree.sum(oper_value, oper_value_second);
            cout << last_oper_result << "\n";
        }
        last_oper = oper;
    }
    return 0;
}