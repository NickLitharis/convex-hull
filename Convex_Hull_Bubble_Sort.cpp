#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>

struct Point {
    int x, y;
};

/* Determinant (Orientation) */
constexpr int determinant(const Point& a, const Point& b, const Point& c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;         // colinear
    return (val > 0) ? 1 : 2;       // 1: clockwise, 2: counterclockwise
}

/* Convex Hull (Jarvis March) */
void convexhull(const std::vector<Point>& points, std::vector<Point>& hull) {
    int n = points.size();
    if (n < 3) return;
    int a = 0, c;
    do {
        hull.push_back(points[a]);
        c = (a + 1) % n;
        for (int i = 0; i < n; i++) {
            if (determinant(points[a], points[i], points[c]) == 2) {
                c = i;
            }
        }
        a = c;
    } while (a != 0);
}

int main(int argc, char* argv[]) {
    int n = 100;
    if (argc > 1) {
        n = std::stoi(argv[1]);
        if (n <= 0) n = 100; // fallback to default if invalid
    }
    std::vector<Point> points(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);

    for (int i = 0; i < n; i++) {
        points[i].x = dis(gen);
        points[i].y = dis(gen);
    }

    // Bubble sort (explicit implementation, replaces any std::sort usage)
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (points[j].x > points[j + 1].x ||
                (points[j].x == points[j + 1].x && points[j].y > points[j + 1].y)) {
                std::swap(points[j], points[j + 1]);
            }
        }
    }

    std::vector<Point> hull;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    convexhull(points, hull);

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Output points and hull to CSV
    std::ofstream fout("points_and_hull.csv");
    fout << "x,y,type\n";
    for (const auto& p : points)
        fout << p.x << "," << p.y << ",point\n";
    for (const auto& p : hull)
        fout << p.x << "," << p.y << ",hull\n";
    // Connect last hull point to first
    if (!hull.empty())
        fout << hull.front().x << "," << hull.front().y << ",hull\n";
    fout.close();

    long long time_taken_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    std::cout << "Time taken by program is : " << time_taken_ns << " ns\n";

    return 0;
}
