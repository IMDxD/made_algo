#include <iostream>
#include <cstdio>

using namespace std;

int closest_value(const int *array, int value, int array_size) {
  int left_index = -1;
  int right_index = array_size;

  while (left_index < right_index - 1) {
    int middle_index = (right_index + left_index) / 2;
    if (array[middle_index] == value) {
      left_index = middle_index;
      break;
    } else if (array[middle_index] < value) {
      left_index = middle_index;
    } else {
      right_index = middle_index;
    }
  }

  if (right_index == array_size ||
      (left_index > -1 && (value - array[left_index] <= array[right_index] - value))) {
    return array[left_index];
  } else {
    return array[right_index];
  }
}

int main() {
  size_t array_size, query_size;
  ios::sync_with_stdio(false);
  cin >> array_size >> query_size;
  int array[array_size];
  int query;
  for (size_t i = 0; i < array_size; ++i) {
    cin >> array[i];
  }
  for (size_t i = 0; i < query_size; ++i) {
    cin >> query;
    cout << closest_value(array, query, array_size) << "\n";
  }
  return 0;
}