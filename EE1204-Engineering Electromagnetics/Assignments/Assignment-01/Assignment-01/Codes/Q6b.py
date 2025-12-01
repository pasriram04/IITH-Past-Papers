import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Constants
k = 9e9  # Coulomb's constant (N·m²/C²)

# Define charge positions and values
charges = [
    (0, 1, 1),   # Charge of +1C at (0,1)
    (0, -1, 1),  # Charge of +1C at (0,-1)
    (1, 0, -1),  # Charge of -1C at (1,0)
    (-1, 0, -1)  # Charge of -1C at (-1,0)
]

# Define a grid of points where we will compute the potential
x_vals = np.linspace(-2, 2, 50)  # X-coordinates
y_vals = np.linspace(-2, 2, 50)  # Y-coordinates
X, Y = np.meshgrid(x_vals, y_vals)  # Create a 2D grid

# Initialize electric potential array
V = np.zeros(X.shape)

# Compute the potential at each grid point
for (xq, yq, q) in charges:
    dx = X - xq  # X-distance from charge
    dy = Y - yq  # Y-distance from charge
    r = np.sqrt(dx**2 + dy**2)  # Distance from charge

    r[r < 0.2] = 0.2  # Prevent division by zero
    V += k * q / r  # Compute potential using V = kq/r

# Create 3D plot
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

# Plot the surface
ax.plot_surface(X, Y, V, cmap='coolwarm', edgecolor='none')

# Label axes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Potential V')
ax.set_title('Electric Potential Surface')

# Show the plot
plt.show()

