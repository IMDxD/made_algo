#include "algorithm"
#include "cmath"
#include <cstdio>
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::vector;

const int MOD_ARRAY = static_cast<int>(pow(2, 16));
const int MOD_SEGMENT = static_cast<int>(pow(2, 30));

long long modulus(long long value, int mod) {
    long long res = value % mod;
    if (res < 0) {
        res += mod;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t n;
    int a, x, y;
    cin >> n;
    cin >> x >> y >> a;
    vector<long long> sum_array(n);
    sum_array[0] = a;
    long long cur_value = a;
    for (size_t i = 1; i < n; ++i) {
        cur_value = modulus(cur_value * x + y, MOD_ARRAY);
        sum_array[i] = cur_value + sum_array[i - 1];
    }

    size_t m;
    int b, z, t;
    cin >> m;
    cin >> z >> t >> b;
    vector<long long> segment_array(2 * m);
    cur_value = b;
    for (size_t i = 0; i < 2 * m; ++i) {
        segment_array[i] = cur_value % n;
        cur_value = modulus(cur_value * z + t, MOD_SEGMENT);
    }

    long long total_sum = 0;
    size_t l, r;
    for (size_t i = 0; i < m; i += 1) {
        l = min(segment_array[2 * i + 1], segment_array[2 * i]);
        r = max(segment_array[2 * i + 1], segment_array[2 * i]);
        if (l == 0) {
            total_sum += sum_array[r];
        } else {
            total_sum += sum_array[r] - sum_array[l - 1];
        }
    }
    cout << total_sum << "\n";
    return 0;
}
