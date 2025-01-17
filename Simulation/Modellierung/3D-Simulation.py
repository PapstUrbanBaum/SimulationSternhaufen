### Dieses Programm während der Berechnung des C++ Programms für eine grahische Darstellung ausführen
### Für ein flüssiges Ergebnis am besten die Erstellung der Diagramme im C++ Programm auskommentieren


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import numpy as np
import time


# Koordinaten aus Text-Datei einlesen
def read_coordinates_from_file(filename):
    try:
        data = np.loadtxt(filename)
        if data.ndim == 1:
            data = np.array([data])
        return data
    except Exception as e:
        print(f"Fehler beim Lesen der Datei: {e}")
        return np.array([])

# Funktion zum aktualsieren des Diagramms
def update(num):
    koerper_koordinaten = read_coordinates_from_file('../Diagramme/Daten/koordinaten.txt')
    
    if koerper_koordinaten.size == 0:
        return
    
    ax.clear()
    ax.scatter(koerper_koordinaten[:, 0], koerper_koordinaten[:, 1], koerper_koordinaten[:, 2], c='r', marker='o')

    # Auf Wunsch Achsen festsetzen
    ax.set_xlim(-30000000, 30000000)
    ax.set_ylim(-30000000, 30000000)
    ax.set_zlim(-30000000, 30000000)

    ax.set_xlabel('X-Koordinaten in AE')
    ax.set_ylabel('Y-Koordinaten in AE')
    ax.set_zlabel('Z-Koordinaten in AE')
    ax.set_title('3D Simulation der Körper')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ani = FuncAnimation(fig, update, frames=100, interval=100)

plt.show()

