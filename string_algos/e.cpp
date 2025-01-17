#include "algorithm"
#include "iostream"
#include "set"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::set;
using std::string;
using std::vector;

const char FIRST_LETTER = 'a' - 1;
const uint32_t POWER_CONST = 29;
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
    ssize_t left = 1;
    ssize_t right = min_length + 1;
    string substr;
    while (left < right) {
        bool is_exist = false;
        ssize_t middle = (right + left) / 2;
        set<long long> common_hash;
        for (size_t i = 0; i < str_array[0].size() - middle + 1; ++i) {
            common_hash.insert(get_hash(hash[0], power[0], i, i + middle - 1));
        }
        for (size_t i = 1; i < str_array.size() - 1; ++i) {
            set<long long> tmp_hash;
            for (size_t k = 0; k < str_array[i].size() - middle + 1; ++k) {
                auto pos = common_hash.find(get_hash(hash[i], power[i], k, k + middle - 1));
                if (pos != common_hash.end()) {
                    tmp_hash.insert(*pos);
                }
            }
            common_hash = tmp_hash;
            if (common_hash.empty()) {
                break;
            }
        }
        if (!common_hash.empty()) {
            size_t last = str_array.size() - 1;
            for (size_t i = 0; i < str_array.back().size() - middle + 1; ++i) {
                auto pos = common_hash.find(get_hash(hash[last], power[last], i, i + middle - 1));
                if (pos != common_hash.end()) {
                    substr = str_array.back().substr(i, middle);
                    is_exist = true;
                    break;
                }
            }
        }
        if (is_exist) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    cout << substr << "\n";
    return 0;
}