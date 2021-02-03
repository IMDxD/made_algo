#include "iostream"

using std::cin;
using std::cout;

struct Point {
    long long x;
    long long y;

    Point() : x(0), y(0){};
    Point(long long x, long long y) : x(x), y(y){};
};

class Vector {
   private:
    long long x;
    long long y;

   public:
    Vector(long long x, long long y) : x(x), y(y){};
    Vector(Point a) : x(a.x), y(a.y){};
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y){};

    Vector operator+(const Vector& other) {
        return {this->x + other.x, this->y + other.y};
    }

    long long dot(const Vector& other) {
        return this->x * other.x + this->y * other.y;
    }

    long long cross(const Vector& other) {
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
        long long ABxAC = AB.cross(AC);
        long long ABxAD = AB.cross(AD);
        long long CDxCA = CD.cross(CA);
        long long CDxCB = CD.cross(CB);
        if (ABxAC * ABxAD == 0 &&
            CDxCA * CDxCB == 0) {
            return this->point_on(other.A) ||
                   this->point_on(other.B) ||
                   other.point_on(this->A) ||
                   other.point_on(this->B);
        } else {
            return ABxAC * ABxAD <= 0 &&
                   CDxCA * CDxCB <= 0;
        }
    }
};

int main() {
    Point A, B, C, D;
    cin >> A.x >> A.y;
    cin >> B.x >> B.y;
    cin >> C.x >> C.y;
    cin >> D.x >> D.y;
    Segment AB = Segment(A, B);
    Segment CD = Segment(C, D);
    if (AB.cross(CD)) {
        cout << "YES"
             << "\n";
    } else {
        cout << "NO"
             << "\n";
    }
    return 0;
}