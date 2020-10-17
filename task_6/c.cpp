#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;

int main() {
  size_t array_size;
  cin >> array_size;
  vector<int> array(array_size);
  vector<int> result(array_size, 1);
  vector<int> path(array_size, 0);
  size_t max_subarray_size = 0;
  size_t max_subarray_index = 0;
  for (size_t i = 0; i < array_size; ++i){
    cin >> array[i];
  }
  for (size_t i = 1; i < array_size; ++i){
    for (size_t j = 0; j < i; ++j){
      if (array[i] > array[j] && result[j] + 1 > result[i]){
        result[i] = result[j] + 1;
        path[i] = j;
      }
    }
    if (result[i] > max_subarray_size){
      max_subarray_size = result[i];
      max_subarray_index = i;
    }
  }
  cout << max_subarray_size << "\n";
  vector<int> subarray(max_subarray_size);
  size_t step = max_subarray_size;
  size_t index = max_subarray_index;
  while (step > 0){
    subarray[step - 1] = array[index];
    index = path[index];
    --step;
  }
  for (size_t j = 0; j < subarray.size(); ++j){
    cout << subarray[j];
    if (j < subarray.size() - 1){
      cout << " ";
    }
  }
  cout << "\n";
  return 0;
}