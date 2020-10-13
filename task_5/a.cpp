#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;

const size_t INITIAL_SIZE = 1024;
const size_t MAX_SIZE = 2'000'002;

unsigned modulo(int value, unsigned m) {
  int mod = value % (int) m;
  if (mod < 0) {
    mod += static_cast<int>(m);
  }
  return mod;
}

class Set {
 private:

  vector<int>* array;
  size_t size_;
  const unsigned P = 2'000'003;
  const unsigned A = 7;
  int null_value = INT32_MAX;

  size_t hash_function(int value) const {
    return modulo(static_cast<int>(value * this->A), this->P) % this->array->size();
  }

  size_t find_index(int value){
    size_t index = this->hash_function(value);
    while (!((*this->array)[index] == null_value || (*this->array)[index] == value)) {
      index = (index + 1) % this->array->size();
    }
    return index;
  }

  void rehash(size_t new_size){
    vector<int>* old_array = this->array;
    this->array = new vector<int>(new_size, INT32_MAX);
    this->size_ = 0;
    for (auto el: *old_array){
      if (el != this->null_value){
        this->put(el);
      }
    }
    delete old_array;
  }

  void restore_hash(size_t index){
    size_t next_index = (index + 1) % this->array->size();
    size_t swap_index = index;
    while ((*this->array)[next_index] != this->null_value) {
      size_t next_hash = hash_function((*this->array)[next_index]);
      if (next_hash > next_index || next_hash <= index) {
        swap((*this->array)[swap_index], (*this->array)[next_index]);
        swap_index = next_index;
      }
      ++next_index;
    }
  }

 public:
  Set(): array(new vector<int>(INITIAL_SIZE, INT32_MAX)), size_(0) {};

  bool contains(int value) {
    size_t index = this->find_index(value);
    return (*this->array)[index] == value;
  }

  void put(int value) {
    if (this->size_ == this->array->size() /2){
      size_t new_size = std::max(this->array->size() * 2, MAX_SIZE);
      this->rehash(new_size);
    }
    size_t index = this->find_index(value);
    if ((*this->array)[index] != value) {
      (*this->array)[index] = value;
      ++this->size_;
    }
  }

  void remove(int value) {
    size_t index = this->hash_function(value);
    size_t step = 0;
    while ((*this->array)[index] != this->null_value && step < this->array->size()) {
      if ((*this->array)[index] == value) {
        (*this->array)[index] = this->null_value;
        restore_hash(index);
        --this->size_;
        if (this->size_ == this->array->size() / 8){
          size_t new_size = std::min(this->array->size() / 8, INITIAL_SIZE);
          this->rehash(new_size);
        }
        break;
      }
      index = (index + 1) % this->array->size();
      ++step;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Set hashset = Set();
  string oper;
  int value;
  while (cin >> oper >> value) {
    if (oper == "insert") {
      hashset.put(value);
    } else if (oper == "exists") {
      if (hashset.contains(value)) {
        cout << "true\n";
      } else {
        cout << "false\n";
      }
    } else {
      hashset.remove(value);
    }
  }
  return 0;
}
