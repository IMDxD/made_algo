#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;
using std::vector;

vector<int> zfunction(const string& data) {
    vector<int> z(data.size(), 0);
    int left = 0;
    int right = 0;
    for (int i = 1; i < data.size(); ++i) {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < data.size() && data[z[i]] == data[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > right) {
            left = i;
            right = z[i] + i;
        }
    }
    return z;
}

int main() {
    string data;
    cin >> data;
    vector<int> z = zfunction(data);
    for (size_t i = 1; i < z.size(); ++i) {
        cout << z[i] << " ";
    }
    cout << "\n";
    return 0;
}
