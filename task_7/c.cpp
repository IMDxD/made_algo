#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;


size_t f_i(size_t i){
    return i & (i + 1);
}

int get_sum(const vector<int>& sum_array, size_t l, size_t r){
    if (l == 0) {
        return sum_array[r];
    } else {
        return sum_array[r] - sum_array[l - 1];
    }
}

int get_t_i(const vector<int>& sum_array, size_t i){
    size_t lb = f_i(i);
    return get_sum(sum_array, lb, i);
}
