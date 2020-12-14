#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

const char FIRST_LETTER = 'a' - 1;
const uint32_t POWER_CONST = 19;
const uint32_t MODULE = 2'000'003;
const size_t MAX_LENGTH = 10'000;

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
    size_t string_cnt;
    cin >> string_cnt;
    size_t min_length = MAX_LENGTH;
    vector<string> str_array(string_cnt);
    vector<vector<long long>> hash(string_cnt);
    vector<vector<long long>> power(string_cnt);
    for (size_t i = 0; i < string_cnt; ++i) {
        cin >> str_array[i];
        hash[i].resize(str_array[i].size());
        power[i].resize(str_array[i].size());
        hash[i][0] = str_array[i][0] - FIRST_LETTER;
        power[i][0] = 1;
        for (uint32_t j = 1; j < str_array[i].size(); ++j) {
            hash[i][j] = (hash[i][j - 1] * POWER_CONST + str_array[i][j] - FIRST_LETTER) % MODULE;
            power[i][j] = (power[i][j - 1] * POWER_CONST) % MODULE;
        }
        min_length = min(min_length, str_array[i].size());
    }
    size_t left = 0;
    size_t right = min_length + 1;
    string substr;
    while (left < right - 1) {
        size_t middle = (right + left) / 2;
        bool is_exist = true;
        for (size_t j = 0; j < str_array[0].size() - middle + 1; ++j) {
            long long first_hash = get_hash(hash[0], power[0], j, j + middle - 1);
            for (size_t i = 1; i < str_array.size(); ++i) {
                bool has_substr = false;
                for (size_t k = 0; k < str_array[i].size() - middle + 1; ++k) {
                    if (get_hash(hash[i], power[i], k, k + middle - 1) == first_hash) {
                        has_substr = true;
                        break;
                    }
                }
                if (!has_substr) {
                    is_exist = false;
                    break;
                } else {
                    is_exist = true;
                }
            }
            if (is_exist) {
                substr = str_array[0].substr(j, middle);
                break;
            }
        }
        if (is_exist) {
            left = middle;
        } else {
            right = middle;
        }
    }
    cout << substr << "\n";
    return 0;
}