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
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
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

/* Merge Sort for Points */
void merge(std::vector<Point>& coor, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<Point> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = coor[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = coor[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].x < R[j].x || (L[i].x == R[j].x && L[i].y <= R[j].y)) {
            coor[k++] = L[i++];
        } else {
            coor[k++] = R[j++];
        }
    }
    while (i < n1) coor[k++] = L[i++];
    while (j < n2) coor[k++] = R[j++];
}

void mergeSort(std::vector<Point>& coor, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(coor, l, m);
        mergeSort(coor, m + 1, r);
        merge(coor, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    int n = 100;
    if (argc > 1) {
        try {
            n = std::stoi(argv[1]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid input for number of points, using default (100).\n";
            n = 100;
        } catch (const std::out_of_range&) {
            std::cerr << "Input out of range for number of points, using default (100).\n";
            n = 100;
        }
        if (n <= 0) {
            std::cerr << "Number of points must be positive, using default (100).\n";
            n = 100;
        }
    }
    std::vector<Point> points(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);

    for (int i = 0; i < n; i++) {
        points[i].x = dis(gen);
        points[i].y = dis(gen);
    }

    mergeSort(points, 0, n - 1);

    std::vector<Point> hull;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    convexhull(points, hull);

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Output points and hull to CSV with error checking
    std::ofstream fout("points_and_hull.csv");
    if (!fout.is_open() || fout.fail()) {
        std::cerr << "Error: Could not open points_and_hull.csv for writing.\n";
        return 1;
    }

    fout << "x,y,type\n";
    if (fout.fail()) {
        std::cerr << "Error: Failed to write CSV header.\n";
        fout.close();
        return 1;
    }

    for (const auto& p : points) {
        fout << p.x << "," << p.y << ",point\n";
        if (fout.fail()) {
            std::cerr << "Error: Failed to write point to CSV.\n";
            fout.close();
            return 1;
        }
    }
    for (const auto& p : hull) {
        fout << p.x << "," << p.y << ",hull\n";
        if (fout.fail()) {
            std::cerr << "Error: Failed to write hull point to CSV.\n";
            fout.close();
            return 1;
        }
    }
    // Connect last hull point to first for closed polygon
    if (!hull.empty()) {
        fout << hull.front().x << "," << hull.front().y << ",hull\n";
        if (fout.fail()) {
            std::cerr << "Error: Failed to write closing hull point to CSV.\n";
            fout.close();
            return 1;
        }
    }

    fout.close();
    if (fout.fail()) {
        std::cerr << "Error: Failed to close CSV file properly.\n";
        return 1;
    }

    long long time_taken_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    std::cout << "Time taken by program is : " << time_taken_ns << " ns\n";

    return 0;
}
