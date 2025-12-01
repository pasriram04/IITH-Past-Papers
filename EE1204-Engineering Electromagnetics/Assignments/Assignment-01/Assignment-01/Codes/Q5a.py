import numpy as np  # Import NumPy for mathematical functions
import matplotlib.pyplot as plt  # Import Matplotlib for plotting

# Define the function to compute the magnitude of F
def F_magnitude(phi):
    """
    Computes the magnitude of the vector field |F| as a function of phi.
    
    Parameters:
        phi (array): Array of phi values in radians.
    
    Returns:
        array: Computed magnitude values.
    """
    return np.sqrt(38 + 24 * (np.cos(phi) + np.sin(phi)))

# Generate an array of phi values from 0 to 2*pi (one full cycle) with 1000 points
phi_values = np.linspace(0, 2 * np.pi, 1000)  # 1000 points for a very smooth curve

# Compute the magnitude for each phi value
F_values = F_magnitude(phi_values)

# Create a figure and plot the function
plt.figure(figsize=(8, 5))  # Set the figure size
plt.plot(phi_values, F_values, label=r'$|\mathbf{F}| = \sqrt{38 + 24(\cos\phi + \sin\phi)}$', 
         color='b', linewidth=2)

# Mark important points at 0, π/2, π, 3π/2, and 2π
phi_ticks = [0, np.pi/2, np.pi, 3*np.pi/2, 2*np.pi]
phi_labels = [r'$0$', r'$\frac{\pi}{2}$', r'$\pi$', r'$\frac{3\pi}{2}$', r'$2\pi$']
plt.xticks(phi_ticks, phi_labels)

# Add labels and title to the plot
plt.xlabel(r'$\phi$ (radians)')  # X-axis label (phi in radians)
plt.ylabel(r'$|\mathbf{F}|$')  # Y-axis label (magnitude of F)
plt.title(r'Magnitude of $\mathbf{F}$ as a function of $\phi$ for $s=3$')  # Title of the plot

# Add legend and grid for better visualization
plt.legend(loc='upper right', fontsize=10, frameon=True)  # Show the legend in the upper right
plt.grid(True, linestyle='--', alpha=0.7)  # Add a dashed grid with slight transparency

# Show the plot
plt.show()


