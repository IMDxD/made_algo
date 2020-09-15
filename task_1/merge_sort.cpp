#include <iostream>
#include <vector>

using namespace std;

vector<int> ReadInput(const int& array_size, vector<int>& data) {
    int el;
    for (int i = 0; i < array_size; ++i) {
        cin >> el;
        data[i] = el;
    }
    return data;
}

void PrintArray(const vector<int>& array) {
    for (int i = 0; i < array.size(); ++i) {
        cout << array[i];
        if (i < array.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

void Merge(int start_index, int split_index, int end_index, const vector<int>& array, vector<int>& result) {
    int i = start_index;
    int j = split_index;
    int step = start_index;
    if (end_index > array.size()) {
        end_index = array.size();
    }
    while (i + j < end_index + split_index) {
        if ((j >= end_index) ||
            (i < split_index && array[i] < array[j])) {
            result[step] = array[i];
            i++;
        } else {
            result[step] = array[j];
            j++;
        }
        step++;
    }
}

int main() {
    int array_size;
    cin >> array_size;
    vector<int> data(array_size);
    ReadInput(array_size, data);
    vector<int> temp = data;
    for (int i = 1; i < data.size(); i *= 2) {
        for (int j = 0; j < data.size(); j += 2 * i) {
            Merge(j, j + i, j + 2 * i, data, temp);
        }
        data = temp;
    }
    PrintArray(temp);
    return 0;
}