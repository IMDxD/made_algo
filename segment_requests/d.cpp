#include "cmath"
#include <cstdio>
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

class SegmentTree {

 public:
  explicit SegmentTree(vector<long long> a) {
      added_size = 1;
      while (added_size < a.size()) {
          added_size *= 2;
      }
      segment_array.resize(2 * added_size - 1, {INT64_MAX, INT64_MAX, 0});
      for (size_t i = 0; i < a.size(); ++i) {
          segment_array[i + added_size - 1] = {a[i], INT64_MAX, 0};
      }
      long long min_val;
      for (ssize_t i = added_size - 2; i >= 0; --i) {
          min_val = min(segment_array[2 * i + 1].get_value(), segment_array[2 * i + 2].get_value());
          segment_array[i] = {min_val, INT64_MAX, 0};
      }
  }

  void set(size_t left, size_t right, long long value) {
      set(0, 0, added_size - 1, left, right, value);
  }

  void update(size_t left, size_t right, long long value) {
      update(0, 0, added_size - 1, left, right, value);
  }

  long long rmq(size_t left, size_t right) {
      return rmq(0, 0, added_size - 1, left, right);
  }

 private:
  struct ArrayValue {
    long long value;
    long long setted;
    long long updated;

    long long get_value() const {
        if (this->setted != INT64_MAX) {
            return this->setted + this->updated;
        } else {
            return this->value + this->updated;
        }
    }

    void set_value(ArrayValue& other) {
        if (other.setted != INT64_MAX) {
            this->setted = other.setted;
            this->updated = 0;
        }
        this->updated += other.updated;
    }

    void update_value() {
        if (this->setted != INT64_MAX) {
            this->value = this->setted;
        }
        this->value += this->updated;
        this->setted = INT64_MAX;
        this->updated = 0;
    }
  };
  vector<ArrayValue> segment_array;
  size_t added_size;

  void set(size_t index, size_t left_array, size_t right_array,
           size_t left_query, size_t right_query, long long value) {
      push(index, left_array, right_array);
      if (left_array >= left_query && right_array <= right_query) {
          segment_array[index].setted = value;
          segment_array[index].updated = 0;
      } else if (left_array <= right_query && right_array >= left_query) {
          size_t middle_array = (left_array + right_array) / 2;
          set(2 * index + 1, left_array, middle_array, left_query, right_query, value);
          set(2 * index + 2, middle_array + 1, right_array, left_query, right_query, value);
          long long min_val = min(segment_array[2 * index + 1].get_value(), segment_array[2 * index + 2].get_value());
          segment_array[index] = {min_val, INT64_MAX, 0};
      }
  };

  void update(size_t index, size_t left_array, size_t right_array,
              size_t left_query, size_t right_query, long long value) {
      push(index, left_array, right_array);
      if (left_array >= left_query && right_array <= right_query) {
          segment_array[index].updated += value;
      } else if (left_array <= right_query && right_array >= left_query) {
          size_t middle_array = (left_array + right_array) / 2;
          update(2 * index + 1, left_array, middle_array, left_query, right_query, value);
          update(2 * index + 2, middle_array + 1, right_array, left_query, right_query, value);
          long long min_val = min(segment_array[2 * index + 1].get_value(), segment_array[2 * index + 2].get_value());
          segment_array[index] = {min_val, INT64_MAX, 0};
      }
  };

  void push(size_t index, size_t left, size_t right) {
      if (left == right) {
          segment_array[index].update_value();
      } else {
          segment_array[2 * index + 1].set_value(segment_array[index]);
          segment_array[2 * index + 2].set_value(segment_array[index]);
          segment_array[index].update_value();
      }
  }

  long long rmq(size_t index, size_t left_array, size_t right_array,
                size_t left_query, size_t right_query) {
      push(index, left_array, right_array);
      if (left_array > right_query || right_array < left_query) {
          return INT64_MAX;
      } else if (left_array >= left_query && right_array <= right_query) {
          return segment_array[index].get_value();
      } else {
          size_t middle_array = (left_array + right_array) / 2;
          return min(rmq(2 * index + 1, left_array, middle_array, left_query, right_query),
                     rmq(2 * index + 2, middle_array + 1, right_array, left_query, right_query));
      }
  }
};

int main() {
    std::ios::sync_with_stdio(false);
    size_t n;
    cin >> n;
    vector<long long> array(n);
    cin >> array[0];
    for (size_t i = 1; i < n; ++i) {
        cin >> array[i];
    }
    SegmentTree tree(array);
    string oper;
    size_t index_left;
    size_t index_right;
    long long oper_val;
    while (cin >> oper) {
        cin >> index_left >> index_right;
        if (oper == "min") {
            cout << tree.rmq(index_left - 1, index_right - 1) << "\n";
        } else if (oper == "set") {
            cin >> oper_val;
            tree.set(index_left - 1, index_right - 1, oper_val);
        } else {
            cin >> oper_val;
            tree.update(index_left - 1, index_right - 1, oper_val);
        }
    }
    return 0;
}