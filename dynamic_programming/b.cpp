#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;

int main() {
  size_t column_count;
  size_t row_count;
  cin >> row_count >> column_count;
  vector<vector<int>> cost_matrix(row_count);
  vector<vector<int>> result_matrix(row_count);
  vector<vector<char>> path_matrix(row_count);
  for (size_t i = 0; i < row_count; ++i) {
    cost_matrix[i].resize(column_count);
    result_matrix[i].resize(column_count);
    path_matrix[i].resize(column_count);
    for (size_t j = 0; j < column_count; ++j) {
      cin >> cost_matrix[i][j];
      result_matrix[i][j] = INT32_MIN + 1;
    }
  }
  result_matrix[0][0] = cost_matrix[0][0];
  for (size_t i = 0; i < row_count; ++i) {
    for (size_t j = 0; j < column_count; ++j) {
      if (i == 0 && j > 0) {
        result_matrix[i][j] = result_matrix[i][j - 1] + cost_matrix[i][j];
        path_matrix[i][j] = 'R';
      } else if (j == 0 && i > 0) {
        result_matrix[i][j] = result_matrix[i - 1][j] + cost_matrix[i][j];
        path_matrix[i][j] = 'D';
      } else if (i > 0 && j > 0) {
        if (result_matrix[i - 1][j] >= result_matrix[i][j - 1]) {
          result_matrix[i][j] = result_matrix[i - 1][j] + cost_matrix[i][j];
          path_matrix[i][j] = 'D';
        } else {
          result_matrix[i][j] = result_matrix[i][j - 1] + cost_matrix[i][j];
          path_matrix[i][j] = 'R';
        }
      }
    }
  }
  cout << result_matrix[row_count - 1][column_count - 1] << "\n";
  size_t i = row_count - 1;
  size_t j = column_count - 1;
  vector<char> path(i + j);
  while (i > 0 || j > 0) {
    path[i + j - 1] = path_matrix[i][j];
    if (path_matrix[i][j] == 'R') {
      j -= 1;
    } else {
      i -= 1;
    }
  }
  for (auto c: path) {
    cout << c;
  }
  cout << "\n";
  return 0;
}