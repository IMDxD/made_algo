#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;


int lower_bound(const vector<int> &array, int value) {
  int left_index = -1;
  int right_index = array.size();

  while (left_index < right_index - 1) {
    int middle_index = (right_index + left_index) / 2;
    if (array[middle_index] >= value) {
      right_index = middle_index;
    } else {
      left_index = middle_index;
    }
  }
  return right_index;
}

int main() {
  int array_size;
  ios::sync_with_stdio(false);
  cin >> array_size;
  vector<int> array(array_size);
  for (size_t i = 0; i < array_size; ++i) {
    cin >> array[i];
  }
  sort(array.begin(), array.end());
  int query_size;
  cin >> query_size;
  int lower_value;
  int higher_value;
  for (size_t i = 0; i < query_size; ++i) {
    cin >> lower_value >> higher_value;
    cout << lower_bound(array, higher_value + 1) - lower_bound(array, lower_value) << "\n";
  }
  return 0;
}