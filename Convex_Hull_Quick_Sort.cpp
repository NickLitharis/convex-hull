#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <chrono>

struct Point {
    int x, y;
};

constexpr int determinant(const Point& a, const Point& b, const Point& c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

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

int partition(std::vector<Point>& arr, int low, int high) {
    Point pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].x < pivot.x ||
            (arr[j].x == pivot.x && arr[j].y < pivot.y)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<Point>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    quickSort(points, 0, n - 1);

    std::vector<Point> hull;
    // Timing using C++11 std::chrono
    auto start = std::chrono::high_resolution_clock::now();

    convexhull(points, hull);

    auto end = std::chrono::high_resolution_clock::now();
    auto time_taken_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Time taken by program is : " << time_taken_ns << " ns\n";

    // Output points and hull to CSV with error handling and no duplicate closing point
    std::ofstream fout("points_and_hull.csv");
    if (!fout.is_open() || fout.fail()) {
        std::cerr << "Error: Unable to open points_and_hull.csv for writing.\n";
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
    // Only write closing hull point if needed (not a duplicate)
    if (!hull.empty() && (hull.back().x != hull.front().x || hull.back().y != hull.front().y)) {
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

    return 0;
}
