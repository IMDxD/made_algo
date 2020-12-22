#include "exception"
#include "iostream"
#include "string"
#include "set"

using std::cin;
using std::cout;
using std::set;
using std::string;

const set<char> VALID_TOKEN = {'(', ')', '+', '-', '*', '.'};

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

  LexemItem get_current() {
      if (VALID_TOKEN.find(data[this->cur_pos]) != VALID_TOKEN.end()) {
          char result = data[this->cur_pos];
          return {-1, result};
      } else if (this->data[this->cur_pos] > 47 && this->data[this->cur_pos] < 58) {
          int value = 0;
          while (this->data[this->cur_pos] > 47 && this->data[this->cur_pos] < 58) {
              value = value * 10 + this->data[this->cur_pos] - 48;
              ++this->cur_pos;
          }
          --this->cur_pos;
          return {value, 'N'};
      } else {
          throw std::invalid_argument("Wrong argument");
      }
  }

  void next() {
      ++this->cur_pos;
  }
};

class Parser {

 private:
  Lexer lexer;

  int parse_sum(int sign) {
      int first_n = sign * parse_mult();
      char oper_name = lexer.get_current().name;
      if (oper_name == '+') {
          lexer.next();
          return first_n + parse_sum(1);
      } else if (oper_name == '-') {
          lexer.next();
          return first_n + parse_sum(-1);
      } else {
          return first_n;
      }
  }

  int parse_mult() {
      int first_n = parse_bracket();
      char oper_name = lexer.get_current().name;
      if (oper_name == '*') {
          lexer.next();
          return first_n * parse_mult();
      } else {
          return first_n;
      }
  }

  int parse_bracket() {
      LexemItem cur = lexer.get_current();
      lexer.next();
      if (cur.name == '(') {
          int result = parse_sum(1);
          cur = lexer.get_current();
          if (cur.name != ')') {
              throw std::invalid_argument("invalid argument");
          } else {
              lexer.next();
              return result;
          }
      } else if (cur.name == 'N') {
          return cur.value;
      } else {
          throw std::invalid_argument("invalid argument");
      }
  }

 public:
  explicit Parser(const string& expr) : lexer(Lexer(expr)) {};

  int parse() {
      int result = parse_sum(1);
      if (lexer.get_current().name == '.') {
          return result;
      } else {
          throw std::invalid_argument("invalid argument");
      }
  }
};

int main() {
    string expr;
    cin >> expr;
    Parser parser = Parser(expr);
    try {
        cout << parser.parse() << "\n";
    } catch (const std::invalid_argument& ia) {
        cout << "WRONG" << "\n";
    }
    return 0;
}