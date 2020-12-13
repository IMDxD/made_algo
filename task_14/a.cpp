#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::vector;

const char FIRST_LETTER = 'a';
const unsigned POWER_CONST = 7;
const unsigned MODULE = 2'000'000'003;

unsigned get_hash(const vector<int>& hash_array,
                  const vector<int>& power_array,
                  size_t left,
                  size_t right) {
    if (left > 0) {
        return (hash_array[right] - hash_array[left - 1] * power_array[right - left + 1] % MODULE
            + MODULE) % MODULE;
    } else {
        return hash_array[right];
    }
}

int main() {
    string data;
    cin >> data;
    size_t query_cnt;
    cin >> query_cnt;
    size_t first_left, first_right, second_left, second_right;
    vector<int> hash(data.size());
    vector<int> power(data.size());
    hash[0] = data[0] - FIRST_LETTER + 1;
    power[0] = 1;
    for (size_t i = 1; i < data.size(); ++i) {
        hash[i] = (hash[i - 1] * POWER_CONST + data[i] - FIRST_LETTER + 1) % MODULE;
        power[i] = (power[i - 1] * POWER_CONST) % MODULE;
    }
    for (size_t i = 0; i < query_cnt; ++i) {
        cin >> first_left >> first_right >> second_left >> second_right;
        if (first_right - first_left == second_right - second_left &&
            get_hash(hash, power, first_left - 1, first_right - 1) ==
                get_hash(hash, power, second_left - 1, second_right - 1)) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
    return 0;
}