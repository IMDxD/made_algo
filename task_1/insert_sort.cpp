#include <iostream>
#include <vector>

using namespace std;

vector<int> read_input(const int& array_size, vector<int>& array) {
    int el;
    for (int i = 0; i < array_size; ++i) {
        cin >> el;
        array[i] = el;
    }
    return array;
}

void print_array(const vector<int>& array) {
    for (int i = 0; i < array.size(); ++i) {
        cout << array[i];
        if (i < array.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

void swap(int& first, int& second) {
    int s;
    s = first;
    first = second;
    second = s;
}

void insert_sort(vector<int>& array) {
    int j;
    for (int i = 1; i < array.size(); ++i) {
        j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            swap(array[j - 1], array[j]);
            --j;
        }
    }
}

int main() {
    int array_size;
    cin >> array_size;
    vector<int> data(array_size);
    read_input(array_size, data);
    insert_sort(data);
    print_array(data);
    return 0;
}