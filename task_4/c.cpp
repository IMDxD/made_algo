#include "iostream"

using std::cin;
using std::cout;

int INITIAL_SIZE = 4;

class QueueArray {

 private:
  int *array_ptr;
  int begin;
  int end;
  int capacity;

  void ensure_capacity(int new_capacity) {
    int *new_array = new int[new_capacity];
    for (size_t i = 0; i < capacity; i++) {
      *(new_array + i) = *(array_ptr + (begin + i) % capacity);
    }
    delete[] array_ptr;
    array_ptr = new_array;
    begin = 0;
    end = capacity;
    capacity = new_capacity;
  }

 public:

  QueueArray() : array_ptr(new int[INITIAL_SIZE]), begin(0), end(0), capacity(INITIAL_SIZE) {}

  void push(const int &element) {
    *(array_ptr + end) = element;
    end = (end + 1) % capacity;
    if (end == begin) {
      ensure_capacity(capacity * 2);
    }
  }

  int pop() {
    int return_value = *(array_ptr + begin);
    begin = (begin + 1) % capacity;
    if (size() >= INITIAL_SIZE && size() == capacity / 4) {
      ensure_capacity(capacity / 2);
    }
    return return_value;
  }

  int size() const {
    if (end >= begin) {
      return end - begin;
    } else {
      return capacity - begin + end;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  QueueArray queue_array;
  int operation_count;
  char operation;
  int operation_value;
  cin >> operation_count;
  for (size_t i = 0; i < operation_count; ++i) {
    cin >> operation;
    if (operation == '+') {
      cin >> operation_value;
      queue_array.push(operation_value);
    } else {
      cout << queue_array.pop() << "\n";
    }
  }
  return 0;
}