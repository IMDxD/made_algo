#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::swap;
using std::string;
using std::pair;
using std::vector;

class Heap {

 private:
  int oper_count;
  vector<pair<int, int>> heap_array;
  vector<int> index_array;

  void sift_up(int index) {

    while (index > 0 && heap_array[index] < heap_array[(index - 1) / 2]) {
      swap(heap_array[index], heap_array[(index - 1) / 2]);
      swap(index_array[heap_array[index].second - 1],
           index_array[heap_array[(index - 1) / 2].second - 1]);
      index = (index - 1) / 2;
    }
  }

  void sift_down(int index) {
    int swap_index = 2 * index + 1;
    bool swapped = true;
    while (swap_index < heap_array.size() && swapped) {
      swapped = false;
      if (swap_index + 1 < heap_array.size() && heap_array[swap_index + 1] < heap_array[swap_index]) {
        swap_index++;
      }
      if (heap_array[swap_index] < heap_array[index]) {
        swapped = true;
        swap(heap_array[index], heap_array[swap_index]);
        swap(index_array[heap_array[index].second - 1],
             index_array[heap_array[swap_index].second - 1]);
        index = swap_index;
        swap_index = 2 * index + 1;
      }
    }
  }

 public:
  Heap() : oper_count(0), heap_array(0), index_array(0) {}
  void push(int element) {
    oper_count++;
    pair<int, int> element_pair = {element, oper_count};
    heap_array.push_back(element_pair);
    int index = (int) heap_array.size() - 1;
    index_array.push_back(index);
    sift_up(index);
  }

  void decrease_key(int oper_number, int value) {
    oper_count++;
    index_array.push_back(-1);
    int heap_index = index_array[oper_number - 1];
    if (heap_index < heap_array.size()) {
      int old_value = heap_array[heap_index].first;
      heap_array[heap_index].first = value;
      if (old_value > value) {
        sift_up(heap_index);
      } else if (old_value < value) {
        sift_down(heap_index);
      }
    }
  }

  void extract_min() {
    oper_count++;
    index_array.push_back(-1);
    if (heap_array.empty()) {
      cout << "*\n";
    } else {
      cout << heap_array[0].first << " " << heap_array[0].second << "\n";
      swap(heap_array[0], heap_array[heap_array.size() - 1]);
      swap(index_array[heap_array[0].second - 1],
           index_array[heap_array[heap_array.size() - 1].second - 1]);
      heap_array.pop_back();
      sift_down(0);
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Heap heap;
  string operation;
  int value_first;
  int value_second;
  while (cin >> operation) {
    if (operation == "push") {
      cin >> value_first;
      heap.push(value_first);
    } else if (operation == "decrease-key") {
      cin >> value_first >> value_second;
      heap.decrease_key(value_first, value_second);
    } else {
      heap.extract_min();

    }
  }
  return 0;
}