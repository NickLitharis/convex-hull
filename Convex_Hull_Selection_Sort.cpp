// Convex Hull with [Sorting Algorithm]
// This program generates random points, sorts them, computes the convex hull, and writes results to a CSV file.

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono> // For timing

struct Point {
    int x, y;
};

// Compute orientation (determinant) for three points
constexpr int determinant(const Point& a, const Point& b, const Point& c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0; // Colinear
    return (val > 0) ? 1 : 2; // 1: clockwise, 2: counterclockwise
}

// Jarvis March convex hull algorithm
void convexhull(const std::vector<Point>& points, std::vector<Point>& hull) {
    int n = points.size();
    if (n < 3) return; // Convex hull not possible for fewer than 3 points
    int a = 0, c;
    do {
        hull.push_back(points[a]);
        c = (a + 1) % n;
        for (int i = 0; i < n; i++) {
            // Find the most counterclockwise point
            if (determinant(points[a], points[i], points[c]) == 2) {
                c = i;
            }
        }
        a = c;
    } while (a != 0);
}

// [Sorting Algorithm] implementation
void selectionSort(std::vector<Point>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // Compare x, then y for ordering
            if (arr[j].x < arr[min_idx].x ||
                (arr[j].x == arr[min_idx].x && arr[j].y < arr[min_idx].y)) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

// Entry point
int main(int argc, char* argv[]) {
    // Parse number of points from command line, fallback to 100 if invalid
    int n = 100;
    if (argc > 1) {
        try {
            n = std::stoi(argv[1]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Warning: Invalid input for number of points, using default (100).\n";
            n = 100;
        } catch (const std::out_of_range&) {
            std::cerr << "Warning: Input out of range for number of points, using default (100).\n";
            n = 100;
        }
        if (n <= 0) {
            std::cerr << "Warning: Number of points must be positive, using default (100).\n";
            n = 100;
        }
    }

    // Generate random points
    std::vector<Point> points(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);
    for (int i = 0; i < n; i++) {
        points[i].x = dis(gen);
        points[i].y = dis(gen);
    }

    // Sort points using [Sorting Algorithm]
    selectionSort(points);

    std::vector<Point> hull;

    // Start timing convex hull computation
    auto start = std::chrono::high_resolution_clock::now();

    convexhull(points, hull);

    auto end = std::chrono::high_resolution_clock::now();
    auto time_taken_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by program is : " << time_taken_us << " us\n";

    // Write points and hull to CSV file for visualization
    std::ofstream fout("points_and_hull.csv");
    if (!fout.is_open() || !fout) {
        std::cerr << "Error: Unable to open points_and_hull.csv for writing.\n";
        return 1;
    }
    fout << "x,y,type\n";
    if (!fout) {
        std::cerr << "Error: Failed to write CSV header.\n";
        fout.close();
        return 1;
    }
    for (const auto& p : points) {
        fout << p.x << "," << p.y << ",point\n";
        if (!fout) {
            std::cerr << "Error: Failed to write point to CSV.\n";
            fout.close();
            return 1;
        }
    }
    for (const auto& p : hull) {
        fout << p.x << "," << p.y << ",hull\n";
        if (!fout) {
            std::cerr << "Error: Failed to write hull point to CSV.\n";
            fout.close();
            return 1;
        }
    }
    // No duplicate closing point; hull already contains start/end if needed

    fout.close();
    if (!fout) {
        std::cerr << "Error: Failed to close CSV file properly.\n";
        return 1;
    }

    return 0;
}
