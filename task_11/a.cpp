#include "iostream"
#include "list"
#include "queue"
#include "vector"

using std::cin;
using std::cout;
using std::queue;
using std::list;
using std::pair;
using std::vector;

const pair<ssize_t, ssize_t> DEFAULT_COOR = {0, 0};
const pair<ssize_t, ssize_t> START_FROM = {-1, -1};
const vector<pair<ssize_t, ssize_t>> HORSE_MOVES = {
    {-2, 1},
    {-2, -1},
    {2, 1},
    {2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2}
};

bool check_vertex(pair<ssize_t, ssize_t> vertex, pair<ssize_t, ssize_t> move, ssize_t bord_size) {
    pair<ssize_t, ssize_t> moved{vertex.first + move.first, vertex.second + move.second};
    return moved.first >= 1 && moved.first <= bord_size && moved.second >= 1 && moved.second <= bord_size;
}

vector<pair<ssize_t, ssize_t>> get_move_coor(pair<ssize_t, ssize_t> vertex, ssize_t bord_size) {
    vector<pair<ssize_t, ssize_t>> result;
    for (auto& move: HORSE_MOVES) {
        if (check_vertex(vertex, move, bord_size)) {
            result.emplace_back(vertex.first + move.first, vertex.second + move.second);
        }
    }
    return result;
}

int main() {
    ssize_t bord_size;
    cin >> bord_size;
    vector<vector<pair<ssize_t, ssize_t>>> from_matrix(bord_size);
    for (auto& row: from_matrix) {
        row.resize(bord_size, DEFAULT_COOR);
    }
    ssize_t start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y >> end_x >> end_y;
    queue<pair<ssize_t, ssize_t>> coor_queue;
    coor_queue.push({start_x, start_y});
    from_matrix[start_x - 1][start_y - 1] = START_FROM;
    pair<ssize_t, ssize_t> cur_coor = {start_x, start_y};
    pair<ssize_t, ssize_t> end_coor = {end_x, end_y};
    while (!coor_queue.empty() && cur_coor != end_coor) {
        cur_coor = coor_queue.front();
        coor_queue.pop();
        for (auto& neighbor: get_move_coor(cur_coor, bord_size)) {
            if (from_matrix[neighbor.first - 1][neighbor.second - 1] == DEFAULT_COOR) {
                coor_queue.push(neighbor);
                from_matrix[neighbor.first - 1][neighbor.second - 1] = {cur_coor.first, cur_coor.second};
            }
        }
    }
    list<pair<ssize_t, ssize_t>> path;
    pair<ssize_t, ssize_t> cur_path_coor = {end_x, end_y};
    while (cur_path_coor != START_FROM) {
        path.push_front(cur_path_coor);
        cur_path_coor = from_matrix[cur_path_coor.first - 1][cur_path_coor.second - 1];
    }
    cout << path.size() << "\n";
    for (auto& step: path) {
        cout << step.first << " " << step.second << "\n";
    }
    return 0;
}
