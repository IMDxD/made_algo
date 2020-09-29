#include <iostream>
#include <vector>

using namespace std;

const int VALUE_COUNT = 101;

vector<int> read_input() {
  int el;
  vector<int> data;
  while (cin >> el) {
    data.push_back(el);
  }
  return data;
}

void print_array(const vector<int> &array) {
  for (int i = 0; i < array.size(); ++i) {
    cout << array[i];
    if (i < array.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;
}

int main() {
  vector<int> data = read_input();
  vector<int> count_array(VALUE_COUNT);
  for (int el : data) {
    count_array[el]++;
  }
  int data_index = 0;
  for (int count_index = 0; count_index < count_array.size(); ++count_index) {
    while (count_array[count_index] > 0) {
      data[data_index++] = count_index;
      count_array[count_index]--;
    }
  }
  print_array(data);
  return 0;
}