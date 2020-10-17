#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;


int main(){
  string first;
  string second;
  cin >> first >> second;
  vector<vector<unsigned>> oper_matrix(first.size() + 1);
  for (auto& v: oper_matrix){
    v.resize(second.size() + 1);
  }
  oper_matrix[0][0] = 0;
  for (size_t j = 1; j <= second.size(); ++j){
    oper_matrix[0][j] = oper_matrix[0][j - 1] + 1;
  }
  for (size_t i = 1; i <= first.size(); ++i){
    oper_matrix[i][0] = oper_matrix[i - 1][0] + 1;
    for (size_t j = 1; j <= second.size(); ++j){
      if (first[i - 1] == second[j - 1]){
        oper_matrix[i][j] = oper_matrix[i - 1][j - 1];
      } else {
        oper_matrix[i][j] = min(min(oper_matrix[i][j - 1],
                                    oper_matrix[i - 1][j]), oper_matrix[i - 1][j - 1]) + 1;
      }
    }
  }
  cout << oper_matrix[first.size()][second.size()] << "\n";
  return 0;
}