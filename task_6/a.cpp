#include "algorithm"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;
using std::min;
using std::max;


int main(){
  size_t column_count;
  size_t jump_range;
  cin >> column_count >> jump_range;
  vector<int> column_cost(column_count, 0);
  vector<int> result_cost(column_count, INT32_MIN + 1);
  result_cost[0] = 0;
  vector<size_t> jumped_columns(column_count, 0);
  for (size_t i = 1; i < column_count - 1; ++i){
    cin >> column_cost[i];
  }
  for (size_t i = 1; i < column_count; ++i){
    size_t jumps_back = min(jump_range, i);
    size_t column = i;
    for (size_t j = 1; j <= jumps_back; ++j){
      if (result_cost[i] < result_cost[i - j]){
        result_cost[i] = result_cost[i - j];
        column = i - j;
      }
    }
    result_cost[i] += column_cost[i];
    jumped_columns[i] = column + 1;
  }
  jumped_columns.push_back(column_count);
  cout << result_cost.back() << "\n";

  size_t col = jumped_columns.size() - 1;
  vector<size_t> pathway;
  while (col > 0){
    pathway.push_back(jumped_columns[col]);
    col = jumped_columns[col] - 1;
  }
  cout << pathway.size() - 1 << "\n";
  for (size_t i = pathway.size() - 1; i > 0; --i){
    cout << pathway[i] << " ";
  }
  cout << pathway[0];
  cout << "\n";
  return 0;
}