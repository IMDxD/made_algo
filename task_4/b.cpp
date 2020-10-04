#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;

char ZERO_CHAR = '0';
int INITIAL_SIZE = 4;

class PostfixStack {

 private:
  int *array_ptr;

  void ensure_capacity(int new_capacity) {
    int *new_array = new int[new_capacity];
    for (size_t i = 0; i < size; i++) {
      *(new_array + i) = *(array_ptr + i);
    }
    delete[] array_ptr;
    array_ptr = new_array;
    capacity = new_capacity;
  }

 public:
  int size;
  int capacity;

  PostfixStack() : array_ptr(new int[INITIAL_SIZE]), size(0), capacity(INITIAL_SIZE) {}

  void push(const int &element) {
    *(array_ptr + size) = element;
    size++;
    if (size == capacity) {
      ensure_capacity(capacity * 2);
    }
  }

  int pop() {
    size--;
    int return_value = *(array_ptr + size);
    if (size >= INITIAL_SIZE && size == capacity / 4) {
      ensure_capacity(capacity / 2);
    }
    return return_value;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string operation_string;
  std::getline(cin, operation_string);
  PostfixStack postfix_stack;
  int left_operand;
  int right_operand;
  for (char operation_val: operation_string) {
    if (operation_val == '+') {
      right_operand = postfix_stack.pop();
      left_operand = postfix_stack.pop();
      postfix_stack.push(left_operand + right_operand);
    } else if (operation_val == '*') {
      right_operand = postfix_stack.pop();
      left_operand = postfix_stack.pop();
      postfix_stack.push(left_operand * right_operand);
    } else if (operation_val == '-') {
      right_operand = postfix_stack.pop();
      left_operand = postfix_stack.pop();
      postfix_stack.push(left_operand - right_operand);
    } else if (operation_val >= ZERO_CHAR && operation_val <= '9') {
      postfix_stack.push((int) (operation_val - ZERO_CHAR));
    }
  }
  cout << postfix_stack.pop() << "\n";
  return 0;
}