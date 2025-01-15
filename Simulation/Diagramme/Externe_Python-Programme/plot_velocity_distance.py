import matplotlib
matplotlib.use('Agg') 

import matplotlib.pyplot as plt
import sys
import numpy as np

def plot_velocity_distance(filename):
    data = np.loadtxt(filename)
    distances = data[:, 1]  # Extrahiere Abstände
    velocities = data[:, 0]  # Extrahiere Geschwindigkeiten
    
    # Diagramm plotten
    plt.scatter(distances, velocities, marker='o')
    plt.title('Geschwindigkeit - Abstand (logarithmische Skala)')
    plt.xlabel('Geschwindigkeit in AE/a')
    plt.ylabel('Abstand zum Massenmittelpunkt in AE')
    plt.xscale('log') 
    plt.yscale('log') 
    plt.grid(True)
    plt.savefig(f'../Diagramme/Auswertung/Geschwi-Radien/VelocityDistance_{sys.argv[2]}k_{sys.argv[3]}.png')  # Speichere das Diagramm
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python plot_velocity_distance.py <velocity_distance_file> <num_bodies> <time_step>")
        sys.exit(1)
    
    filename = sys.argv[1]
    plot_velocity_distance(filename)
