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

/*MERGE SORT*/
void merge(struct Point coor[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	struct Point L[n1];
	struct Point R[n2];

	for (i = 0; i < n1; i++)
	{
		L[i].x = coor[l + i].x;
		L[i].y = coor[l + i].y;
	}
	for (j = 0; j < n2; j++)
	{
		R[j].x = coor[m + 1 + j].x;
		R[j].y = coor[m + 1 + j].y;
	}

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].x <= R[j].x)
		{
			coor[k].x = L[i].x;
			coor[k].y = L[i].y;
			if (L[i].x == R[j].x)
			{
				if (L[i].y < R[j].y)
				{
					coor[k].y = L[i].y;
				}
				else
				{
					coor[k].y = R[j].y;
				}
			}
			i++;
		}
		else
		{
			coor[k].x = R[j].x;
			coor[k].y = R[j].y;
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		coor[k].x = L[i].x;
		coor[k].y = L[i].y;
		i++;
		k++;
	}
	while (j < n2)
	{
		coor[k].x = R[j].x;
		coor[k].y = R[j].y;
		j++;
		k++;
	}
}

void mergeSort(struct Point coor[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(coor, l, m);
		mergeSort(coor, m + 1, r);
		merge(coor, l, m, r);
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

	mergeSort(points, 0, n - 1);
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
