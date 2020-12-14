#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::vector;

const char FIRST_LETTER = 'a' - 1;
const uint32_t POWER_CONST = 19;
const uint32_t MODULE = 2'000'003;

long long get_hash(const vector<long long>& hash_array,
                   const vector<long long>& power_array,
                   uint32_t left,
                   uint32_t right) {
    if (left > 0) {
        return (hash_array[right] - (hash_array[left - 1] * power_array[right - left + 1]) % MODULE
            + MODULE) % MODULE;
    } else {
        return hash_array[right];
    }
}

int main() {
    string data;
    cin >> data;
    uint32_t query_cnt;
    cin >> query_cnt;
    uint32_t first_left, first_right, second_left, second_right;
    vector<long long> hash(data.size());
    vector<long long> power(data.size());
    hash[0] = data[0] - FIRST_LETTER;
    power[0] = 1;
    for (uint32_t i = 1; i < data.size(); ++i) {
        hash[i] = (hash[i - 1] * POWER_CONST + data[i] - FIRST_LETTER) % MODULE;
        power[i] = (power[i - 1] * POWER_CONST) % MODULE;
    }
    for (uint32_t i = 0; i < query_cnt; ++i) {
        cin >> first_left >> first_right >> second_left >> second_right;
        if (get_hash(hash, power, first_left - 1, first_right - 1) ==
            get_hash(hash, power, second_left - 1, second_right - 1)) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
    return 0;
}