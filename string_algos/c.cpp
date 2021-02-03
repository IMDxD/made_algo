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

const string SEPARATOR = " ";

vector<size_t> pfunction(string data) {
    vector<size_t> p(data.size(), 0);
    for (size_t i = 1; i < data.size(); ++i) {
        size_t k = p[i - 1];
        while (k > 0 && data[i] != data[k]) {
            k = p[k - 1];
        }
        if (data[i] == data[k]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}

int main() {
    string data, text;
    cin >> data >> text;
    vector<size_t> p = pfunction(data + SEPARATOR + text);
    vector<size_t> ans;
    for (size_t i = data.size() + 1; i < p.size(); ++i) {
        if (p[i] == data.size()) {
            ans.push_back(i - data.size() * 2 + 1);
        }
    }
    cout << ans.size() << "\n";
    for (auto el: ans) {
        cout << el << " ";
    }
    cout << "\n";
    return 0;
}