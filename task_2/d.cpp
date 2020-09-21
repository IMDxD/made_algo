#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int target_length, letters_length;
    string target, letters;
    cin >> target_length >> letters_length;
    cin >> target;
    cin >> letters;
    int index;
    vector<int> letters_count(27);
    for (char s : letters) {
        index = s - 'a';
        letters_count[index]++;
    }
    int start = 0;
    int end = 0;
    int negative_count = 0;
    long long annagram_count = 0;
    while (end <= target_length && start < target_length) {
        while (negative_count == 0) {
            int n = end - start;
            annagram_count += n;
            end++;
            if (end > target_length) {
                break;
            }
            index = target[end - 1] - 'a';
            letters_count[index]--;
            if (letters_count[index] < 0) {
                negative_count++;
            }
        }
        while (negative_count > 0) {
            index = target[start] - 'a';
            start++;
            letters_count[index]++;
            if (letters_count[index] == 0) {
                negative_count--;
            }
        }
    }
    cout << annagram_count << endl;
    return 0;
}