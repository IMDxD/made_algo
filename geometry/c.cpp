#include "cmath"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::sqrt;
using std::vector;

const int MAX_COOR = 1'000'000;

int mod(int x, size_t size) {
    int r = x % size;
    if (r < 0) {
        r += size;
    }
    return r;
}

struct Point {
    long long x;
    long long y;

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

    double length() const {
        return sqrt(x * x + y * y);
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

class Polygon {
   private:
    vector<Point> vertices;

   public:
    explicit Polygon(std::vector<Point> new_vertices) : vertices(new_vertices){};

    bool point_in(Point O) const {
        size_t cross_cnt = 0;
        Point M = Point(MAX_COOR + 1, O.y);
        Segment OM = Segment(O, M);
        for (ssize_t i = 0; i < this->vertices.size(); ++i) {
            auto next = this->vertices[mod(i + 1, this->vertices.size())];
            Segment tmp = Segment(this->vertices[i], next);
            if (tmp.point_on(O)) {
                cross_cnt = 1;
                break;
            } else if (OM.point_on(this->vertices[i])) {
                auto prev = this->vertices[mod(i - 1, this->vertices.size())];
                cross_cnt += static_cast<size_t>(prev.y < O.y);
                cross_cnt += static_cast<size_t>(next.y < O.y);
            } else if (!OM.point_on(next)) {
                cross_cnt += static_cast<size_t>(OM.cross(tmp));
            }
        }
        return (cross_cnt % 2) == 1;
    }
};

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    Point O = Point(x, y);
    vector<Point> vertices;
    for (size_t i = 0; i < n; ++i) {
        cin >> x >> y;
        vertices.emplace_back(x, y);
    }
    Polygon P = Polygon(vertices);
    if (P.point_in(O)) {
        cout << "YES"
             << "\n";
    } else {
        cout << "NO"
             << "\n";
    }
    return 0;
}