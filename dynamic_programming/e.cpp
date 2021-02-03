#include "algorithm"
#include "iostream"
#include "list"
#include "vector"

using std::cin;
using std::cout;
using std::max;
using std::list;
using std::pair;
using std::string;
using std::vector;

int main() {
  ssize_t dinners_count;
  cin >> dinners_count;
  vector<int> dinner_values(dinners_count);
  int total_sum = 0;
  size_t max_disc_cnt = 0;
  for (size_t i = 0; i < dinners_count; ++i) {
    cin >> dinner_values[i];
    total_sum += dinner_values[i];
    max_disc_cnt += dinner_values[i] > 100;
  }
  vector<vector<int>> dp(dinners_count);

  for (size_t i = 0; i < dinners_count; ++i) {
    dp[i].resize(max_disc_cnt + 1, 0);
  }
  size_t step;
  size_t cur_disc_cnt = 0;
  for (size_t i = 0; i < dinners_count; ++i) {
    int cost = dinner_values[i];
    if (cur_disc_cnt > 0) {
      step = cur_disc_cnt;
      step += cost > 100;
      for (size_t j = 0; j < step; ++j) {
        if (cost > 100) {
          if (j == 0) {
            dp[i][0] = dp[i - 1][1] + cost;
          } else if (j > 0 && j + 1 <= cur_disc_cnt) {
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j + 1] + cost);
          } else {
            dp[i][j] = dp[i - 1][j - 1];
          }
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + 1] + cost);
        }
      }
    }
    cur_disc_cnt += cost > 100;
  }
  int max_disc = 0;
  size_t max_index = 0;
  for (size_t j = 0; j < max_disc_cnt; ++j) {
    if (dp[dinners_count - 1][j] >= max_disc) {
      max_disc = dp[dinners_count - 1][j];
      max_index = j;
    }
  }
  list<size_t> days;
  ssize_t col = max_index;
  ssize_t row = dinners_count - 1;
  size_t coupon_spent = 0;
  size_t coupon_left = max_disc_cnt;
  while (row > 0 && col >= 0 && dp[row][col] > 0) {
    if (dp[row][col] == dp[row - 1][col]) {
      --row;
    } else if (col > 0 && dp[row][col] == dp[row - 1][col - 1]) {
      --row;
      --col;
    } else {
      days.push_front(row + 1);
      coupon_spent += 1;
      coupon_left -= 1;
      coupon_left -= dinner_values[row] > 100;
      ++col;
      --row;
    }
  }
  cout << total_sum - max_disc << "\n";
  cout << coupon_left << " " << coupon_spent << "\n";
  for (
    auto& v: days) {
    cout << v << "\n";
  }
  return 0;
}