#include "iostream"

using std::cin;
using std::cout;

struct Point {
    int x;
    int y;

    Point() : x(0), y(0){};
    Point(int x, int y) : x(x), y(y){};
};

class Vector {
   private:
    int x;
    int y;

   public:
    Vector(int x, int y) : x(x), y(y){};
    Vector(Point a) : x(a.x), y(a.y){};
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y){};

    Vector operator+(const Vector& other) {
        return {this->x + other.x, this->y + other.y};
    }

    int dot(const Vector& other) {
        return this->x * other.x + this->y * other.y;
    }

    int cross(const Vector& other) {
        return this->x * other.y - this->y * other.x;
    }
};

class Segment {
   private:
    Point A;
    Point B;

   public:
    Segment(Point A, Point B) : A(A), B(B){};

    bool point_on(Point M) {
        Vector MA = Vector(M, this->A);
        Vector MB = Vector(M, this->B);

        return MA.cross(MB) == 0 && MA.dot(MB) <= 0;
    }
};

int main() {
    Point A, B, M;
    cin >> M.x >> M.y;
    cin >> A.x >> A.y;
    cin >> B.x >> B.y;

    Segment AB = Segment(A, B);

    if (AB.point_on(M)) {
        cout << "YES"
             << "\n";
    } else {
        cout << "NO"
             << "\n";
    }
    return 0;
}