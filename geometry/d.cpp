#include "cmath"
#include "iostream"
#include "vector"

using std::cin;
using std::cout;
using std::sqrt;
using std::vector;

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

class Polygon {
   private:
    vector<Point> vertices;

   public:
    explicit Polygon(std::vector<Point> new_vertices) : vertices(new_vertices){};

    double area() const {
        double s = 0;
        Point O = Point(rand(), rand());
        for (size_t i = 0; i < this->vertices.size(); ++i) {
            Vector OP1 = Vector(O, this->vertices[i]);
            Vector OP2 = Vector(O, this->vertices[(i + 1) % this->vertices.size()]);
            s += OP1.cross(OP2);
        }
        return fabs(s) / 2;
    };
};

int main() {
    int n;
    cin >> n;
    int x, y;
    vector<Point> vertices;
    for (size_t i = 0; i < n; ++i) {
        cin >> x >> y;
        vertices.emplace_back(x, y);
    }
    Polygon P = Polygon(vertices);
    cout << P.area() << "\n";
    return 0;
}