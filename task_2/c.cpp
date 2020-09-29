#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;
const char FIRST_CHAR = 'a';

vector<string> read_input(int array_size) {
  vector<string> data(array_size);
  string el;
  for (int i = 0; i < array_size; ++i) {
    cin >> el;
    data[i] = el;
  }
  return data;
}

void print_array(const vector<string> &array) {
  for (int i = 0; i < array.size(); ++i) {
    cout << array[i] << endl;
  }
}

vector<string> digit_sort_phase(const vector<string> &array, int phase) {
  vector<int> count_array(ALPHABET_SIZE);
  vector<int> index_array(ALPHABET_SIZE);
  for (string s : array) {
    int index = s[s.size() - phase] - FIRST_CHAR;
    count_array[index]++;
  }
  index_array[0] = 0;
  for (int i = 1; i < index_array.size(); ++i) {
    index_array[i] = index_array[i - 1] + count_array[i - 1];
  }
  vector<string> temp(array.size());
  for (string s : array) {
    int index = s[s.size() - phase] - FIRST_CHAR;
    temp[index_array[index]++] = s;
  }
  return temp;
}

int main() {
  int string_count, string_length, phase_count;
  cin >> string_count >> string_length >> phase_count;
  vector<string> data = read_input(string_count);
  for (int i = 1; i <= phase_count; ++i) {
    data = digit_sort_phase(data, i);
  }
  print_array(data);
  return 0;
}