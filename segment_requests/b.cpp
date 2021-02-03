#include "algorithm"
#include "cmath"
#include "cstdio"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::vector;

const int MOD = 16714589;
const int MUL = 23;
const int ADD = 21563;

int next_a(int value) {
    long long res = value * MUL + ADD;
    res = res % MOD;
    if (res < 0) {
        res += MOD;
    }
    return static_cast<int>(res);
}

size_t next_u(int answer, size_t prev_u, size_t i, size_t n) {
    long long res = 17 * prev_u + 751 + answer + 2 * i;
    res = res % n;
    if (res < 0) {
        res += n;
    }
    return static_cast<size_t>(res) + 1;
}

size_t next_v(int answer, size_t prev_v, size_t i, size_t n) {
    long long res = 13 * prev_v + 593 + answer + 5 * i;
    res = res % n;
    if (res < 0) {
        res += n;
    }
    return static_cast<size_t>(res) + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t n, m;
    int a;
    cin >> n >> m;
    cin >> a;
    vector<int> array(n);
    array[0] = a;
    for (size_t i = 1; i < n; ++i) {
        array[i] = next_a(array[i - 1]);
    }
    vector<vector<int>> min_table(n);
    vector<size_t> min_power_index(n + 1);
    min_power_index[0] = 0;
    for (size_t i = 1; i <= n; ++i) {
        min_power_index[i] = min_power_index[i - 1];
        if ((1u << (min_power_index[i] + 1)) <= i) {
            min_power_index[i]++;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        min_table[i].resize(min_power_index.back() + 1);
        min_table[i][0] = array[i];
    }
    int two_pow = 2;
    for (size_t j = 1; j <= min_power_index.back(); ++j) {
        for (size_t i = 0; i + two_pow - 1 < n; ++i) {
            min_table[i][j] = min(min_table[i][j - 1], min_table[i + two_pow / 2][j - 1]);
        }
        two_pow *= 2;
    }
    size_t u, v;
    cin >> u >> v;
    size_t l, r;
    size_t answer = 0;
    int k;
    for (size_t i = 0; i < m; ++i) {
        l = u - 1;
        r = v - 1;
        if (l > r) {
            std::swap(l, r);
        }
        if (r - l == 0) {
            answer = array[l];
        } else {
            k = min_power_index[r - l + 1];
            answer = min(min_table[l][k], min_table[r - pow(2, k) + 1][k]);
        }
        if (i < m - 1) {
            u = next_u(answer, u, i + 1, n);
            v = next_v(answer, v, i + 1, n);
        }
    }
    cout << u << " " << v << " " << answer << "\n";
    return 0;
}