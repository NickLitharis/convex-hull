# Convex Hull Algorithms Playground

Welcome! This project lets you explore and compare different convex hull algorithms, each using a different sorting method. You can generate random points, compute their convex hull, and visualize the results—all with simple commands.

---

## 📦 What’s Inside?

- **Convex_Hull_Bubble_Sort.cpp**  
  Convex hull with Bubble Sort (easy to understand, not the fastest).
- **Convex_Hull_Selection_Sort.cpp**  
  Convex hull with Selection Sort (simple and educational).
- **Convex_Hull_Merge_Sort.cpp**  
  Convex hull with Merge Sort (efficient for large datasets).
- **Convex_Hull_Quick_Sort.cpp**  
  Convex hull with Quick Sort (fast and popular).
- **visualize.py**  
  Python script to plot your points and hull for easy viewing.
- **points_and_hull.csv**  
  Automatically generated file with all points and hull coordinates.

---

## ⚡ Getting Started

### 1. Build the Programs

Make sure you have a C++ compiler (like `g++`).  
Open a terminal in the project folder and run:

```bash
g++ Convex_Hull_Bubble_Sort.cpp -o Convex_Hull_Bubble_Sort
g++ Convex_Hull_Selection_Sort.cpp -o Convex_Hull_Selection_Sort
g++ Convex_Hull_Merge_Sort.cpp -o Convex_Hull_Merge_Sort
g++ Convex_Hull_Quick_Sort.cpp -o Convex_Hull_Quick_Sort
```

---

### 2. Run an Algorithm

Each program generates random points and computes their convex hull.  
You can choose how many points to use:

- **Default (100 points):**
  ```bash
  ./Convex_Hull_Bubble_Sort
  ```
- **Custom (e.g., 500 points):**
  ```bash
  ./Convex_Hull_Bubble_Sort 500
  ```

The program will print the time taken (in nanoseconds) and create `points_and_hull.csv` for visualization.

---

### 3. Visualize the Results

See your points and hull in a plot!  
First, make sure you have Python 3 and these packages:

```bash
pip install matplotlib pandas
```

Then run:

```bash
python3 visualize.py
```

A window will pop up showing your points (blue) and the convex hull (red).

---

## 🛠 Requirements

- **C++ compiler:** `g++` or similar
- **Python 3:** For visualization
- **Python packages:** `matplotlib`, `pandas`

---

## 📝 License

MIT License — free to use, modify, and share!

---

## 💡 Tips & Contributions

- Try different algorithms and sample sizes to see how performance changes.
- Feel free to suggest improvements or add new algorithms!
- If you find a bug or have a question, open an issue or start a discussion.

---

Enjoy exploring computational geometry!
