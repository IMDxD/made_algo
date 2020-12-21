#include "exception"
#include "iostream"
#include "map"
#include "string"
#include "set"

using std::cin;
using std::cout;
using std::set;
using std::map;
using std::string;

const set<char> VALID_TOKEN = {'(', ')', '+', '-', '*', '.'};
const set<string> VALID_NAMES = {"Podarok", "Ded Moroz", "Moroz", "Snegurochka"};
const map<string, int> CONST_MAP = {{"Ded Moroz", 2020},
                                    {"Moroz", -30},
                                    {"Snegurochka", 10}};

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
      } else if (is_number(this->data[this->cur_pos])) {
          int value = 0;
          while (is_number(this->data[this->cur_pos])) {
              value = value * 10 + this->data[this->cur_pos] - 48;
              ++this->cur_pos;
          }
          --this->cur_pos;
          return {value, 'N'};
      } else {
          size_t start_pos = this->cur_pos;
          while (!is_number(this->data[this->cur_pos]) &&
              VALID_TOKEN.find(data[this->cur_pos]) == VALID_TOKEN.end()) {
              ++this->cur_pos;
          }
          string name = data.substr(start_pos, this->cur_pos - start_pos);
          --this->cur_pos;
          if (VALID_NAMES.find(name) != VALID_NAMES.end()) {
              if (name == "Podarok") {
                  return {-1, 'P'};
              } else {
                  return {CONST_MAP.at(name), 'N'};
              }
          } else {
              throw std::invalid_argument("Wrong argument");
          }
      }
  }

  static bool is_number(char value) {
      return value > 47 && value < 58;
  }

  bool is_valid_end() {
      return (this->data[this->cur_pos] == '.') && (this->cur_pos == this->data.size() - 1);
  }

  void next() {
      ++this->cur_pos;
  }
};


class Parser {

 private:
  Lexer lexer;

  int parse_sum(int sign) {
      int first_n = sign*parse_mult();
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

  int podarok() {
      LexemItem cur = lexer.get_current();
      if (cur.name != '(') {
          throw std::invalid_argument("invalid argument");
      } else {
          int result = parse_sum(1);
          cur = lexer.get_current();
          if (cur.name != ')') {
              throw std::invalid_argument("invalid argument");
          } else {
              lexer.next();
              if (result > 0) {
                  return 5 * result;
              } else {
                  return -1 * result;
              }
          }
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
      } else if (cur.name == 'P') {
          return podarok();
      }
      else {
          throw std::invalid_argument("invalid argument");
      }
  }

 public:
  explicit Parser(const string& expr) : lexer(Lexer(expr)) {};

  int parse() {
      int result = parse_sum(1);
      if (lexer.is_valid_end()){
          return result;
      } else {
          throw std::invalid_argument("invalid argument");
      }
  }
};

int main() {
    string expr;
    getline(cin, expr);
    Parser parser = Parser(expr);
    try {
        cout << parser.parse() << "\n";
    } catch (const std::invalid_argument& ia) {
        cout << "WRONG" << "\n";
    }
    return 0;
}