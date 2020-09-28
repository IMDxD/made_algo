#include <iostream>
#include <cmath>

using namespace std;

const double TOL = 1e-6;
const int LOWER_BOUND = 0;
const int HIGHER_BOUND = 100'000;
const int ITERATION_COUNT = 40;

double function(double x) {
  return x * x + sqrt(x);
}

int main() {
  double equality_value;
  cin >> equality_value;
  double left_x = LOWER_BOUND;
  double right_x = HIGHER_BOUND;
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    double middle_x = (right_x + left_x) / 2;
    double function_value = function(middle_x);
    if (function_value < equality_value) {
      left_x = middle_x;
    } else {
      right_x = middle_x;
    }
  }
  cout << fixed << (right_x + left_x) / 2 << endl;
}
