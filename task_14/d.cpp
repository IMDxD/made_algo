#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

const int FIRST_LETTER = 'a';
const size_t ALPHABET_SIZE = 26;

class Trie {

  uint32_t size_;
  vector<vector<uint32_t>> next;
  vector<bool> is_terminal;
  vector<int> level_query;

 public:
  explicit Trie(size_t query_cnt) : size_(1) {
      next.resize(1);
      next[0].resize(ALPHABET_SIZE, 0);
      level_query.resize(query_cnt, -1);
  }

  void insert(const string& s, size_t query_n) {
      uint32_t level = 0;
      for (auto c: s) {
          c -= FIRST_LETTER;
          if (next[level][c] == 0) {
              next[level][c] = size_;
              ++size_;
          }
          if (next.size() < size_) {
              vector<uint32_t> tmp(ALPHABET_SIZE, 0);
              next.push_back(tmp);
          }
          level = next[level][c];
      }
      if (level >= is_terminal.size()) {
          level_query.resize(level + 1, -1);
      }
      level_query[level] = query_n;
  }

  vector<size_t> get_substings(const string& s, size_t left) {
      uint32_t level = 0;
      vector<size_t> result;
      for (size_t i = left; i < s.size(); ++i) {
          char c = s[i];
          c -= FIRST_LETTER;
          if (next[level][c] == 0) {
              break;
          }
          level = next[level][c];
          if (level_query[level] != -1) {
              result.push_back(level_query[level]);
          }
      }
      return result;
  }
};

int main() {
    string text;
    cin >> text;
    size_t query_cnt;
    cin >> query_cnt;
    Trie trie = Trie(query_cnt);
    string query;
    for (uint32_t i = 0; i < query_cnt; ++i) {
        cin >> query;
        trie.insert(query, i);
    }
    vector<bool> result(query_cnt, false);
    for (uint32_t i = 0; i < text.size(); ++i) {
        for (auto el: trie.get_substings(text, i)) {
            result[el] = true;
        }
    }
    for (auto el: result) {
        if (el) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
    return 0;
}