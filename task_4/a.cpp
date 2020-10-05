#include "iostream"

using std::cin;
using std::cout;
using std::min;

class Node {
 public:
  int value;
  Node *next_node_pointer;
  Node *min_pointer;
  Node(int new_value, Node *new_pointer, Node *new_min_node_pointer) :
      value(new_value),
      next_node_pointer(new_pointer),
      min_pointer(new_min_node_pointer) {}
};

class MinStack {
 public:
  Node *head_pointer;
  Node *min_node_pointer;

  MinStack() : head_pointer(nullptr), min_node_pointer(nullptr) {}

  void push(int element) {
    Node *new_node = new Node(element, head_pointer, min_node_pointer);
    head_pointer = new_node;
    if (min_node_pointer == nullptr || element < (*min_node_pointer).value) {
      min_node_pointer = new_node;
    }
  }

  void pop() {
    Node *prev_head_pointer = head_pointer;
    head_pointer = (*prev_head_pointer).next_node_pointer;
    min_node_pointer = (*prev_head_pointer).min_pointer;
    free(prev_head_pointer);
  }
  
  int minimum() const {
    return (*min_node_pointer).value;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  MinStack min_stack;
  int number_of_operation;
  cin >> number_of_operation;
  int operation_code;
  int operation_value;
  for (size_t i = 0; i < number_of_operation; ++i) {
    cin >> operation_code;
    if (operation_code == 1) {
      cin >> operation_value;
      min_stack.push(operation_value);
    } else if (operation_code == 2) {
      min_stack.pop();
    } else {
      cout << min_stack.minimum() << "\n";
    }
  }
  return 0;
}

