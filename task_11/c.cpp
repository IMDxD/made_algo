#include "cstdio"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::vector;

const int MAX_VAL = 100'000;

int main() {
    std::ios::sync_with_stdio(false);
    size_t vert_cnt;
    cin >> vert_cnt;
    vector<vector<int>> weights(vert_cnt);
    vector<vector<size_t>> path(vert_cnt);
    for (size_t i = 0; i < vert_cnt; ++i) {
        weights[i].resize(vert_cnt);
        path[i].resize(vert_cnt);
        for (size_t j = 0; j < vert_cnt; ++j) {
            cin >> weights[i][j];
            if (weights[i][j] == MAX_VAL) {
                weights[i][j] = INT32_MAX;
            }
            path[i][j] = j;
        }
    }
    ssize_t negative_cycle_start = -1;
    for (size_t k = 0; k < vert_cnt; ++k) {
        for (size_t i = 0; i < vert_cnt; ++i) {
            for (size_t j = 0; j < vert_cnt; ++j) {
                if (weights[i][k] + weights[k][j] < weights[i][j] &&
                    weights[i][k] < INT32_MAX &&
                    weights[k][j] < INT32_MAX) {
                    weights[i][j] = weights[i][k] + weights[k][j];
                    path[i][j] = path[i][k];
                    if (i == j && weights[i][j] < 0) {
                        negative_cycle_start = i;
                        break;
                    }
                }
            }
            if (negative_cycle_start > -1) {
                break;
            }
        }
        if (negative_cycle_start > -1) {
            break;
        }
    }

    if (negative_cycle_start > -1) {
        cout << "YES" << "\n";
        vector<size_t> cycle_path;
        size_t cur_vert = path[negative_cycle_start][negative_cycle_start];
        cycle_path.push_back(negative_cycle_start);
        while (cur_vert != negative_cycle_start) {
            cycle_path.push_back(cur_vert);
            cur_vert = path[cur_vert][negative_cycle_start];
        }
        cout << cycle_path.size() << "\n";
        for (auto v: cycle_path) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    } else {
        cout << "NO" << "\n";
    }
    return 0;
}