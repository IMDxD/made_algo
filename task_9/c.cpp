#include "cstdio"
#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

struct Node {

  int value;
  int priority;
  size_t tree_size;
  Node* left_child;
  Node* right_child;

  explicit Node(int value, int priority) :
      value(value),
      right_child(nullptr),
      left_child(nullptr),
      priority(priority),
      tree_size(1) {};

  size_t get_left_tree_size() const {
      return left_child == nullptr ? 0 : left_child->tree_size;
  }

  size_t get_right_tree_size() const {
      return right_child == nullptr ? 0 : right_child->tree_size;
  }

  void update_tree_size() {
      this->tree_size = this->get_left_tree_size() + this->get_right_tree_size() + 1;
  }
};

class Treap {

 public:

  Treap() : root(nullptr) {};

  void insert(size_t index, int value) {
      std::pair<Node*, Node*> node_pair = split(root, index);
      Node* new_node = new Node(value, rand());
      Node* left_tree = merge(node_pair.first, new_node);
      root = merge(left_tree, node_pair.second);
  }

  void move(size_t left, size_t right) {
      std::pair<Node*, Node*> node_pair_right = split(root, right);
      std::pair<Node*, Node*> node_pair_left = split(node_pair_right.first, left - 1);
      root = merge(node_pair_left.second, node_pair_left.first);
      root = merge(root, node_pair_right.second);
  }

  void print_tree() {
      print_tree(root);
  }

 private:

  Node* root;

  std::pair<Node*, Node*> split(Node* node_ptr, size_t index) {
      if (node_ptr == nullptr) {
          return {nullptr, nullptr};
      } else if (node_ptr->get_left_tree_size() + 1 == index) {
          Node* right_tree = node_ptr->right_child;
          node_ptr->right_child = nullptr;
          node_ptr->update_tree_size();
          return {node_ptr, right_tree};
      } else if (node_ptr->get_left_tree_size() + 1 > index) {
          std::pair<Node*, Node*> node_pair = split(node_ptr->left_child, index);
          node_ptr->left_child = node_pair.second;
          node_ptr->update_tree_size();
          return {node_pair.first, node_ptr};
      } else {
          std::pair<Node*, Node*> node_pair = split(node_ptr->right_child,
                                                    index - node_ptr->get_left_tree_size() - 1);
          node_ptr->right_child = node_pair.first;
          node_ptr->update_tree_size();
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
          first->update_tree_size();
          return first;
      } else {
          second->left_child = merge(first, second->left_child);
          second->update_tree_size();
          return second;
      }
  }

  void print_tree(Node* node_ptr) {
      if (node_ptr != nullptr) {
          print_tree(node_ptr->left_child);
          cout << node_ptr->value << " ";
          print_tree(node_ptr->right_child);
      }
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    Treap tree = Treap();
    size_t array_size, oper_count;
    cin >> array_size >> oper_count;
    size_t left, right;
    for (size_t i = 0; i < array_size; ++i) {
        tree.insert(i, static_cast<int>(i) + 1);
    }
    for (size_t i = 0; i < oper_count; ++i) {
        cin >> left >> right;
        tree.move(left, right);
    }
    tree.print_tree();
    return 0;
}