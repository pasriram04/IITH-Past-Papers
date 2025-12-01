import numpy as np
import matplotlib.pyplot as plt

# Given parameters
phi = np.pi / 4  # 45 degrees in radians

# Define the vector field components
def F_s(s, phi):
    return 40 / (s**2 + 1) + 3 * (np.cos(phi) + np.sin(phi))

def F_phi(s, phi):
    return 3 * (np.cos(phi) - np.sin(phi))

def F_z(s):
    return -2

# Compute the magnitude of F
def magnitude_F(s, phi):
    return np.sqrt(F_s(s, phi)**2 + F_phi(s, phi)**2 + F_z(s)**2)

# Define s values for plotting
s_values = np.linspace(0.1, 10, 100)  # Avoid s=0 to prevent division issues
F_magnitudes = magnitude_F(s_values, phi)

# Plot
plt.figure(figsize=(8, 5))
plt.plot(s_values, F_magnitudes, label=r'$|\mathbf{F}|$ vs $s$', color='b', linewidth=2)
plt.xlabel(r'$s$', fontsize=14)
plt.ylabel(r'$|\mathbf{F}|$', fontsize=14)
plt.title(r'Magnitude of $\mathbf{F}$ as a function of $s$ for $\phi = 45^\circ$', fontsize=14)
plt.grid(True)
plt.legend()
plt.show()

