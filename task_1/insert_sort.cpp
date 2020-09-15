#include <iostream>
#include <vector>

using namespace std;

vector<int> ReadInput(const int& array_size, vector<int>& array) {
    int el;
    for (int i = 0; i < array_size; ++i) {
        cin >> el;
        array[i] = el;
    }
    return array;
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

void InsertSort(vector<int>& array) {
    int j;
    for (int i = 1; i < array.size(); ++i) {
        j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            Swap(array[j - 1], array[j]);
            --j;
        }
    }
}

int main() {
    int array_size;
    cin >> array_size;
    vector<int> data(array_size);
    ReadInput(array_size, data);
    InsertSort(data);
    PrintArray(data);
    return 0;
}