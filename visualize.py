import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("points_and_hull.csv")

points = df[df['type'] == 'point']
hull = df[df['type'] == 'hull']

plt.scatter(points['x'], points['y'], label='Points', color='blue')
plt.plot(hull['x'], hull['y'], label='Convex Hull', color='red', linewidth=2)
plt.scatter(hull['x'], hull['y'], color='red')

plt.legend()
plt.title("Convex Hull Visualization")
plt.xlabel("x")
plt.ylabel("y")
plt.show()