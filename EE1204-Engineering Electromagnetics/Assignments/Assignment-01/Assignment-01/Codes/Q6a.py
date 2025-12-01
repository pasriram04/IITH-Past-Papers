import numpy as np
import matplotlib.pyplot as plt  # Import required libraries

# Constants
k = 9e9  # Coulomb's constant (N·m²/C²)

# Define charge positions and values based on the given image
charges = [
    (0, 1, 1),   # Charge of +1C at (0,1)
    (0, -1, 1),  # Charge of +1C at (0,-1)
    (1, 0, -1),  # Charge of -1C at (1,0)
    (-1, 0, -1)  # Charge of -1C at (-1,0)
]

# Define a grid of points where we will compute the electric field
x_vals = np.linspace(-2, 2, 20)  # X-coordinates from -2 to 2 with 20 points
y_vals = np.linspace(-2, 2, 20)  # Y-coordinates from -2 to 2 with 20 points
X, Y = np.meshgrid(x_vals, y_vals)  # Create a 2D grid of points

# Initialize electric field components (Ex, Ey) as zero arrays
Ex = np.zeros(X.shape)  # X-component of electric field
Ey = np.zeros(Y.shape)  # Y-component of electric field

# Loop through each charge to compute its contribution to the field
for (xq, yq, q) in charges:
    dx = X - xq  # X-distance from charge to grid points
    dy = Y - yq  # Y-distance from charge to grid points
    r = np.sqrt(dx**2 + dy**2)  # Compute the Euclidean distance from charge
    
    r[r < 0.2] = 0.2  # Prevent division by zero by setting a minimum radius

    # Compute the magnitude of the electric field using Coulomb’s law: E = kq / r²
    E = k * q / r**2

    # Compute the electric field components Ex and Ey
    Ex += E * (dx / r)  # Contribution of this charge to the Ex field
    Ey += E * (dy / r)  # Contribution of this charge to the Ey field

# Normalize field vectors for better visualization (scale all vectors to unit length)
magnitude = np.sqrt(Ex**2 + Ey**2)  # Compute field magnitude
Ex /= magnitude  # Normalize Ex
Ey /= magnitude  # Normalize Ey

# Plot the electric field using quiver plot (vector arrows)
plt.figure(figsize=(6, 6))  # Set figure size
plt.quiver(X, Y, Ex, Ey, color='b', scale=20)  # Plot electric field vectors

# Plot the charge locations with colors (Red for +1C, Blue for -1C)
plt.scatter([0, 0, 1, -1], [1, -1, 0, 0], c=['red', 'red', 'blue', 'blue'], s=100, label='Charges')

# Label axes
plt.xlabel('x')  
plt.ylabel('y')

# Set title for the plot
plt.title('Electric Field of Given Charge Distribution')

# Show legend
plt.legend()

# Display grid for reference
plt.grid()

# Show the plot
plt.show()


