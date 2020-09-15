#include <iostream>
#include <random>
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

void Swap(int& first, int& second) {
    int s;
    s = first;
    first = second;
    second = s;
}

vector<int> Split(int start_index, int end_index, vector<int>& array, int x) {
    vector<int> index_info = {start_index, 0};
    int temp;
    for (int i = start_index; i < end_index; ++i) {
        if (index_info[0] + index_info[1] >= end_index) {
            break;
        }
        if (array[i] < x) {
            Swap(array[i], array[index_info[0]]);
            index_info[0]++;
            if (index_info[1] > 0) {
                Swap(array[i], array[index_info[0] + index_info[1] - 1]);
            }
        } else if (array[i] == x) {
            Swap(array[i], array[index_info[0] + index_info[1]]);
            index_info[1]++;
        }
    }
    return index_info;
}

void QuickSort(int start_index, int end_index, vector<int>& array) {
    if (end_index - start_index > 1) {
        int x = array[start_index + rand() % (end_index - start_index)];
        vector<int> index_info = Split(start_index, end_index, array, x);
        QuickSort(start_index, index_info[0], array);
        QuickSort(index_info[0] + index_info[1], end_index, array);
    }
}

int main() {
    int array_size;
    cin >> array_size;
    vector<int> data(array_size);
    ReadInput(array_size, data);
    QuickSort(0, data.size(), data);
    PrintArray(data);
    return 0;
}