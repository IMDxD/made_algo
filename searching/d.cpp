#include <iostream>
#include <vector>

using namespace std;

const int LOWER_BOUND = 0;
const int HIGHER_BOUND = 10'000'002;

int calc_rope_count(const vector<int> &rope_array, int rope_size) {
  int count = 0;
  for (int rope_length: rope_array) {
    count += rope_length / rope_size;
  }
  return count;
}

int main() {
  int rope_array_size;
  int house_count;
  cin >> rope_array_size >> house_count;
  vector<int> rope_array(rope_array_size);
  for (size_t i = 0; i < rope_array_size; ++i) {
    cin >> rope_array[i];
  }
  int right_size = HIGHER_BOUND;
  int left_size = LOWER_BOUND;
  while (left_size < right_size - 1) {
    int middle_size = (right_size + left_size) / 2;
    int rope_count = calc_rope_count(rope_array, middle_size);
    if (rope_count >= house_count) {
      left_size = middle_size;
    } else {
      right_size = middle_size;
    }
  }
  cout << left_size << endl;

  return 0;
}