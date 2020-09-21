#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

map<char, int> rome_arab_map;

struct King {
    string name;
    string rome_number;
    int arab_number;
};

int convert_rome_number(string rome_number) {
    int value = 0;
    int last_max_value = 0;
    int current = 0;
    for (int i = rome_number.size() - 1; i >= 0; --i) {
        current = rome_arab_map[rome_number[i]];
        if (current < last_max_value) {
            value -= current;
        } else {
            value += current;
            last_max_value = current;
        }
    }
    return value;
}

bool equal(King left, King right) {
    return (left.name == right.name) && (left.rome_number == right.rome_number);
}

bool lower(King left, King right) {
    if (left.name < right.name) {
        return true;
    } else if (left.name == right.name && left.arab_number < right.arab_number) {
        return true;
    } else {
        return false;
    }
}

vector<King> read_input(const int& array_size, vector<King>& data) {
    string name;
    string rome_number;
    for (int i = 0; i < array_size; ++i) {
        cin >> name >> rome_number;
        King king = {name, rome_number, convert_rome_number(rome_number)};
        data[i] = king;
    }
    return data;
}

void print_array(const vector<King>& array) {
    for (int i = 0; i < array.size(); ++i) {
        cout << array[i].name << " " << array[i].rome_number << endl;
    }
}

void swap(King& first, King& second) {
    King s;
    s = first;
    first = second;
    second = s;
}

vector<int> split(int start_index, int end_index, vector<King>& array, King x) {
    vector<int> index_info = {start_index, 0};
    King temp;
    for (int i = start_index; i < end_index; ++i) {
        if (index_info[0] + index_info[1] >= end_index) {
            break;
        }
        if (lower(array[i], x)) {
            swap(array[i], array[index_info[0]]);
            index_info[0]++;
            if (index_info[1] > 0) {
                swap(array[i], array[index_info[0] + index_info[1] - 1]);
            }
        } else if (equal(array[i], x)) {
            swap(array[i], array[index_info[0] + index_info[1]]);
            index_info[1]++;
        }
    }
    return index_info;
}

void quick_sort(int start_index, int end_index, vector<King>& array) {
    if (end_index - start_index > 1) {
        King x = array[start_index + rand() % (end_index - start_index)];
        vector<int> index_info = split(start_index, end_index, array, x);
        quick_sort(start_index, index_info[0], array);
        quick_sort(index_info[0] + index_info[1], end_index, array);
    }
}

int main() {
    rome_arab_map['I'] = 1;
    rome_arab_map['V'] = 5;
    rome_arab_map['X'] = 10;
    rome_arab_map['L'] = 50;

    int array_size;
    cin >> array_size;
    vector<King> data(array_size);
    read_input(array_size, data);
    quick_sort(0, data.size(), data);
    print_array(data);
    return 0;
}