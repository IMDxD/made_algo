#include "algorithm"
#include "cmath"
#include "functional"
#include "iostream"
#include "list"
#include "vector"

using std::cin;
using std::cout;
using std::list;
using std::sort;
using std::sqrt;
using std::vector;

struct Point {
    long long x;
    long long y;

    Point(long long x, long long y) : x(x), y(y){};

    bool operator==(const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }
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

    double perimeter() const {
        double p = 0;
        for (size_t i = 0; i < this->vertices.size(); ++i) {
            Vector tmp = Vector(this->vertices[i], this->vertices[(i + 1) % this->vertices.size()]);
            p += tmp.length();
        }
        return p;
    };
};

void push_shape(Point vert, vector<Point>& shape, std::function<bool(long long)> cmp) {
    if (shape.size() > 1) {
        int index = shape.size() - 1;
        Vector prev = Vector(shape[index - 1], shape[index]);
        Vector cur = Vector(shape[index], vert);
        long long cross = prev.cross(cur);
        while (cmp(cross) && index > 0) {
            shape.pop_back();
            if (--index > 0) {
                prev = Vector(shape[index - 1], shape[index]);
                cur = Vector(shape[index], vert);
                cross = prev.cross(cur);
            }
        }
    }
    shape.push_back(vert);
}

int main() {
    auto cmp_x = [](Point a, Point b) { return a.x < b.x ||
                                               (a.x == b.x && a.y < b.y); };
    auto cmp_bottom = [](long long x) { return x <= 0; };
    auto cmp_top = [](long long x) { return x >= 0; };
    vector<Point> vertices;
    uint32_t n;
    cin >> n;
    long long x, y;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> x >> y;
        vertices.emplace_back(x, y);
    }
    sort(vertices.begin(), vertices.end(), cmp_x);
    Point P0 = vertices[0];
    Point P1 = vertices[vertices.size() - 1];
    Vector PP = Vector(P0, P1);
    vector<Point> top;
    vector<Point> bottom;
    for (uint32_t i = 0; i < vertices.size(); ++i) {
        Point vert = vertices[i];
        Vector tmp = Vector(P0, vert);
        if (i == 0 || i == vertices.size() - 1) {
            push_shape(vert, top, cmp_top);
            push_shape(vert, bottom, cmp_bottom);
        } else if (PP.cross(tmp) > 0) {
            push_shape(vert, top, cmp_top);
        } else if (PP.cross(tmp) < 0) {
            push_shape(vert, bottom, cmp_bottom);
        }
    }
    vector<Point> shape = top;
    for (int i = bottom.size() - 2; i > 0; --i) {
        shape.push_back(bottom[i]);
    }
    Polygon shape_polygon = Polygon(shape);
    cout << shape_polygon.perimeter() << "\n";
    return 0;
}