#include "iostream"
#include "string"

using std::cin;
using std::cout;
using std::string;


struct LexemItem {
  int value;
  char name;
};

std::ostream& operator<<(std::ostream& output, const LexemItem& item) {
    if (item.name == 'N') {
        cout << item.value;
    } else {
        cout << item.name;
    }
    return output;
}

class Lexer {
 private:
  string data;
  size_t cur_pos;

 public:
  explicit Lexer(string data) : data(std::move(data)), cur_pos(0) {};

  LexemItem get_next() {
      LexemItem result = get_current();
      ++this->cur_pos;
      return result;
  }

  LexemItem get_current() {
      if (this->data[this->cur_pos] < 48 || this->data[this->cur_pos] > 57) {
          char result = data[this->cur_pos];
          return {-1, result};
      } else {
          int value = 0;
          while (this->data[this->cur_pos] > 47 && this->data[this->cur_pos] < 58) {
              value = value * 10 + this->data[this->cur_pos] - 48;
              ++this->cur_pos;
          }
          --this->cur_pos;
          return {value, 'N'};
      }
  }
};

int main() {
    string expr;
    cin >> expr;
    Lexer lexer = Lexer(expr);
    LexemItem cur_val = lexer.get_next();
    while (cur_val.name != '.') {
        cout << cur_val << "\n";
        cur_val = lexer.get_next();
    }
    return 0;
}