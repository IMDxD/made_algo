#include <iostream>
#include <vector>

using namespace std;

vector<int> read_input(const int &array_size, vector<int> &data) {
  int el;
  for (int i = 0; i < array_size; ++i) {
    cin >> el;
    data[i] = el;
  }
  return data;
}

void merge(int start_index,
           int split_index,
           int end_index,
           const vector<int> &array,
           vector<int> &result,
           long long &inverse_count) {
  int i = start_index;
  int j = split_index;
  int step = start_index;
  if (end_index > array.size()) {
    end_index = array.size();
  }
  while (i + j < end_index + split_index) {
    if ((j >= end_index) ||
        (i < split_index && array[i] <= array[j])) {
      result[step] = array[i];
      i++;
    } else {
      result[step] = array[j];
      j++;
      inverse_count += split_index - i;
    }
    step++;
  }
}

int main() {
  int array_size;
  long long inverse_count = 0;
  cin >> array_size;
  vector<int> data(array_size);
  read_input(array_size, data);
  vector<int> temp = data;
  for (int i = 1; i < data.size(); i *= 2) {
    for (int j = 0; j < data.size(); j += 2 * i) {
      merge(j, j + i, j + 2 * i, data, temp, inverse_count);
    }
    data = temp;
  }
  cout << inverse_count << endl;
  return 0;
}