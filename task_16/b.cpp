#include "iostream"

using std::cin;
using std::cout;

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y){};
};

class Vector {
   private:
    int x;
    int y;

   public:
    Vector(int x, int y) : x(x), y(y){};
    Vector(Point a) : x(a.x), y(a.y){};
    Vector(Point a, Point b) : x(a.x - b.x), y(a.y - b.y){};

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

    bool point_on(Point M) const {
        Vector MA = Vector(M, this->A);
        Vector MB = Vector(M, this->B);

        return MA.cross(MB) == 0 && MA.dot(MB) <= 0;
    }

    bool cross(const Segment& other) const {
        Vector AB = Vector(this->A, this->B);
        Vector AC = Vector(this->A, other.A);
        Vector AD = Vector(this->A, other.B);
        Vector CD = Vector(other.A, other.B);
        Vector CA = Vector(other.A, this->A);
        Vector CB = Vector(other.A, this->B);
        int ABxAC = AB.cross(AC);
        int ABxAD = AB.cross(AD);
        int CDxCA = CD.cross(CA);
        int CDxCB = CD.cross(CB);
        if (ABxAC * ABxAD <= 0 &&
            CDxCA * CDxCB < 0) {
            return true;
        } else if (ABxAC * ABxAD < 0 &&
                   CDxCA * CDxCB <= 0) {
            return true;
        } else if (ABxAC * ABxAD == 0 &&
                   CDxCA * CDxCB == 0 &&
                   (this->point_on(other.A) ||
                    this->point_on(other.B) ||
                    other.point_on(this->A) ||
                    other.point_on(this->B))) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    int x, y;
    cin >> x >> y;
    Point A(x, y);
    cin >> x >> y;
    Point B(x, y);
    cin >> x >> y;
    Point C(x, y);
    cin >> x >> y;
    Point D(x, y);
    Segment AB = Segment(A, B);
    Segment CD = Segment(C, D);
    if (AB.cross(CD)) {
        cout << "YES"
             << "\n";
    } else {
        cout << "NO"
             << "\n";
    }
}