#include <iostream>
#include <vector>

using namespace std;

vector<int> read_input(const int &array_size, vector<int> &data) {
    int el;
    for (int i = 0; i < array_size; ++i) {
        cin >> el;
        data[i] = el;
    }
    return data;
}

vector<int> copy_array_slice(const vector<int> &source, int start_index, int end_index) {
    vector<int> temp(end_index - start_index);
    for (int i = start_index; i < end_index; ++i) {
        temp[i - start_index] = source[i];
    }
    return temp;
}

pair<int, int> split(int start_index, int end_index, vector<int> &array, int x) {
    int lower_insert_index = start_index;
    int same_value_count = 0;
    for (int i = start_index; i < end_index; ++i) {
        if (lower_insert_index + same_value_count >= end_index) {
            break;
        }
        if (array[i] < x) {
            swap(array[i], array[lower_insert_index]);
            lower_insert_index++;
            if (same_value_count > 0) {
                swap(array[i], array[lower_insert_index + same_value_count - 1]);
            }
        } else if (array[i] == x) {
            swap(array[i], array[lower_insert_index + same_value_count]);
            same_value_count++;
        }
    }
    return {lower_insert_index, same_value_count};
}

int k_number_statistic(int start_index, int end_index, int k, vector<int> &array) {
    if (end_index - start_index == 1) {
        return array[start_index];
    } else {
        int x = array[start_index + rand() % (end_index - start_index)];
        pair<int, int> index_info = split(start_index, end_index, array, x);
        if (k < index_info.first) {
            return k_number_statistic(start_index, index_info.first, k, array);
        } else if (k >= index_info.first + index_info.second) {
            return k_number_statistic(index_info.first + index_info.second, end_index, k, array);
        } else {
            return array[index_info.first];
        }
    }
}

int main() {
    int array_size;
    cin >> array_size;
    vector<int> data(array_size);
    read_input(array_size, data);
    int queries_number, start, end, k;
    cin >> queries_number;
    for (int i = 0; i < queries_number; ++i) {
        cin >> start >> end >> k;
        vector<int> temp = copy_array_slice(data, start - 1, end);
        cout << k_number_statistic(0, end - start + 1, k - 1, temp) << endl;
    }
    return 0;
}