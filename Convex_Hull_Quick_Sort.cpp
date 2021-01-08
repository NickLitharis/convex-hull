#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
using namespace std;

struct Point
{
	int x, y;
};

/*Determinant*/
int determinant(Point a, Point b, Point c)
{
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

	if (val == 0)
	{
		return 0;
	}
	else if (val > 0)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

/* CONVEX HULL*/
void convexhull(Point points[], int n)
{
	vector<Point> hull;
	int a = 0, c;

	/*Adding points to HULL*/
	do
	{
		hull.push_back(points[a]);
		c = (a + 1) % n;
		for (int i = 0; i < n; i++)
		{
			if (determinant(points[a], points[i], points[c]) == 2)
			{
				c = i;
			}
		}
		a = c;
	} while (a != 0);

	/*Printing points on screen*/
	cout << "Convex Hull Points:" << endl;
	for (int i = 0; i < hull.size(); i++)
	{
		cout << "(" << hull[i].x << "," << hull[i].y << ")\n";
	}
}

/*QUCIK SORT*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(struct Point arr[], int low, int high)
{
	int pivot = arr[high].x;
	int i = (low - 1);
	int j;
	for (j = low; j <= (high - 1); j++)
	{
		if (arr[j].x < pivot)
		{
			i++;
			swap(&arr[i].x, &arr[j].x);
			swap(&arr[i].y, &arr[j].y);
		}
		if (arr[j].x == pivot)
		{
			if (arr[j].y < arr[high].y)
			{
				swap(&arr[j].y, &arr[high].y);
			}
		}
	}
	swap(&arr[i + 1].x, &arr[high].x);
	swap(&arr[i + 1].y, &arr[high].y);
	return (i + 1);
}

void quickSort(struct Point arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int main()
{
	int n = 100;
	struct Point points[n];
	struct timespec start, end;
	srand(time(0));

	for (int i = 0; i < n; i++)
	{
		points[i].x = rand() % 1001;
		points[i].y = rand() % 1001;
	}

	quickSort(points, 0, n - 1);
	clock_gettime(CLOCK_MONOTONIC, &start);
	ios_base::sync_with_stdio(false);

	convexhull(points, n);
	clock_gettime(CLOCK_MONOTONIC, &end);

	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	cout << "Time taken by program is : " << fixed << time_taken << setprecision(9) << " sec";
	return 0;
}
