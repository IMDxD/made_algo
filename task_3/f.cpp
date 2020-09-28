#include "iostream"
#include "utility"
#include "cmath"

using namespace std;

const double LOWER_BOUND = -0.01;
const double HIGHER_BOUND = 1.01;
const size_t ITERATION_COUNT = 30;

const pair<double, double> VILLAGE = {0, 1};
const pair<double, double> TARGET = {1, 0};

double way_time(double x_coordinate, double y_coordinate, int village_speed, int forest_speed) {
  double village_path = sqrt(pow(x_coordinate - VILLAGE.first, 2) +
      pow(y_coordinate - VILLAGE.second, 2));
  double forest_path = sqrt(pow(x_coordinate - TARGET.first, 2) +
      pow(y_coordinate - TARGET.second, 2));
  return village_path / village_speed + forest_path / forest_speed;
}

int main() {
  int village_speed;
  int forest_speed;
  double border_y_coordinate;
  cin >> village_speed >> forest_speed;
  cin >> border_y_coordinate;
  double left_border = LOWER_BOUND;
  double right_border = HIGHER_BOUND;
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    double first_border = (2 * left_border + right_border) / 3;
    double second_border = (left_border + 2 * right_border) / 3;
    if (way_time(first_border, border_y_coordinate, village_speed, forest_speed) <
        way_time(second_border, border_y_coordinate, village_speed, forest_speed)) {
      right_border = second_border;
    } else {
      left_border = first_border;
    }
  }
  cout << (right_border + left_border) / 2 << endl;
  return 0;
}