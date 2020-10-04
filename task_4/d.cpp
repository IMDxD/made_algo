#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;

struct Operation{
  int value;
  int push_count;
  int operation_count;
};

class Heap {

 private:
  int push_count;
  int operation_count;
  vector<Operation> array;
  vector<int> operation_to_index_array;

  void sift_up(int index) {

    while (index > 0 && array[index].value < array[(index - 1) / 2].value) {
      Operation left_value = array[index];
      Operation right_value = array[(index - 1) / 2];
      swap(left_value, right_value);
      swap(operation_to_index_array[left_value.operation_count],
           operation_to_index_array[right_value.operation_count]);
      index = (index - 1) / 2;
    }
  }

 public:
  void push(int element) {
    push_count++;
    operation_count++;
    array.push_back({element, push_count, operation_count});
    int index = array.size() - 1;
    operation_to_index_array.push_back(index);
    sift_up(index);
  }

  void decrease_key(int operation_number, int value) {
    operation_count++;
    operation_to_index_array.push_back(-1);
    int heap_index = operation_to_index_array[operation_number];
    array[heap_index].value -= value;
    sift_up(heap_index);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Heap heap;
  string operation;
  int operation_value_first;
  int operation_value_second;

  while (cin >> operation) {
    if (operation == "push") {
      cin >> operation_value_first;
      heap.push(operation_value_first);
    } else if (operation == "decrease-key") {
      cin >> operation_value_first >> operation_value_second;
      heap.decrease_key(operation_value_first, operation_value_second);
    }
  }
  return 0;
}