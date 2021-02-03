#include <iostream>
#include <vector>

using namespace std;

const int LOWER_BOUND = 0;
const int HIGHER_BOUND = 1000'000'011;

int calc_paper_count(int seconds, int first_xerox_speed, int second_xerox_speed, int min_xerox_speed) {
  if (seconds >= min_xerox_speed) {
    seconds -= min_xerox_speed;
    return seconds / first_xerox_speed + seconds / second_xerox_speed + 1;
  } else {
    return 0;
  }
}

int main() {
  int need_paper;
  int first_xerox_speed;
  int second_xerox_speed;
  cin >> need_paper >> first_xerox_speed >> second_xerox_speed;
  int min_xerox_speed = min(first_xerox_speed, second_xerox_speed);
  int right_time = HIGHER_BOUND;
  int left_time = LOWER_BOUND;
  while (left_time < right_time - 1) {
    int middle_time = (right_time + left_time) / 2;
    int paper_count = calc_paper_count(middle_time, first_xerox_speed, second_xerox_speed, min_xerox_speed);
    if (paper_count >= need_paper) {
      right_time = middle_time;
    } else {
      left_time = middle_time;
    }
  }
  cout << right_time << endl;
  return 0;
}