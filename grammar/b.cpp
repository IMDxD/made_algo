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

struct Node {
  Node* left;
  Node* right;
  char name;
  int value;

  Node(LexemItem item) : name(item.name), value(item.value), left(nullptr), right(nullptr) {};

  LexemItem evaluate() {
      if (this->name == 'N') {
          return {this->value, 'G'};
      } else if (this->name == 'W') {
          return {-1, 'W'};
      } else {
          if (this->left != nullptr && this->right != nullptr) {
              LexemItem left = this->left->evaluate();
              LexemItem right = this->right->evaluate();
              if (left.name == 'W' || right.name == 'W') {
                  return {-1, 'W'};
              } else {
                  switch (this->name) {
                      case '+': return {left.value + right.value, 'G'};
                      case '-': return {left.value - right.value, 'G'};
                      case '*': return {left.value * right.value, 'G'};
                      default: return {-1, 'W'};
                  }
              }
          } else {
              return {-1, 'W'};
          }
      }
  }
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
          return {-1, 'W'};
      }
  }

  void next() {
      ++this->cur_pos;
  }

  static bool is_number(char value) {
      return value > 47 && value < 58;
  }

  bool is_valid_end() {
      return (this->data[this->cur_pos] == '.') && (this->cur_pos == this->data.size() - 1);
  }
};

class Parser {

 private:
  Lexer lexer;
  Node* tree;

  Node* parse_sum() {
      Node* left_node = parse_mult();
      char oper_name = lexer.get_current().name;
      Node* result_node = left_node;
      while (oper_name == '+' || oper_name == '-') {
          lexer.next();
          result_node = new Node({-1, oper_name});
          Node* right_node = parse_mult();
          result_node->left = left_node;
          result_node->right = right_node;
          oper_name = lexer.get_current().name;
          left_node = result_node;
      }
      return result_node;
  }

  Node* parse_mult() {
      Node* left_node = parse_bracket();
      char oper_name = lexer.get_current().name;
      Node* result_node = left_node;
      while (oper_name == '*')  {
          lexer.next();
          result_node = new Node({-1, oper_name});
          Node* right_node = parse_bracket();
          result_node->left = left_node;
          result_node->right = right_node;
          oper_name = lexer.get_current().name;
          left_node = result_node;
      }
      return result_node;
  }

  Node* parse_bracket() {
      LexemItem cur = lexer.get_current();
      lexer.next();
      if (cur.name == '(') {
          Node* result = parse_sum();
          cur = lexer.get_current();
          if (cur.name != ')') {
              delete result;
              result = new Node({-1, 'W'});
              return result;
          } else {
              lexer.next();
              return result;
          }
      } else if (cur.name == 'N') {
          Node* result = new Node(cur);
          return result;
      } else {
          Node* result = new Node({-1, 'W'});
          return result;
      }
  }

 public:
  explicit Parser(const string& expr) : lexer(Lexer(expr)), tree(nullptr) {};

  void parse() {
      tree = parse_sum();
      if (this->lexer.is_valid_end()) {
          LexemItem result = tree->evaluate();
          if (result.name == 'G') {
              cout << result.value << "\n";
          } else {
              cout << "WRONG" << "\n";
          }
      } else {
          cout << "WRONG" << "\n";
      }
  }
};

int main() {
    string expr;
    cin >> expr;
    Parser parser = Parser(expr);
    parser.parse();
    return 0;
}