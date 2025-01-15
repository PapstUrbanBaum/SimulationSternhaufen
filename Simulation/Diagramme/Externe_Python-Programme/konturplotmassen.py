import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
import os

def main():
    # Argumente vom Befehlszeilenaufruf abrufen
    if len(sys.argv) != 4:
        print("Usage: python plot_gravitational.py <data_file> <num_bodies> <time_step>")
        return

    data_file = sys.argv[1]
    num_bodies = int(sys.argv[2])
    time_step = float(sys.argv[3])

    # Prüfen, ob die Eingabedatei existiert
    if not os.path.isfile(data_file):
        print(f"Error: File '{data_file}' not found.")
        return

    # Ausgabeordner definieren
    output_folder = "KonturplotMassen"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Daten laden
    df = pd.read_csv(data_file, delimiter=' ', header=None)
    df.columns = ['x', 'y', 'z', 'm']

    x = df['x']
    y = df['y']
    z = df['m']

    # Gitter erstellen
    N = 1000
    x1 = np.linspace(min(x), max(x), N)
    y1 = np.linspace(min(y), max(y), N)
    X, Y = np.meshgrid(x1, y1)

    # Gravitationskonstante
    G = 37.4227

    # Gravitationspotential berechnen
    Vg = np.zeros(X.shape)
    for i in range(len(x)):
        distance = np.sqrt((X - x[i])**2 + (Y - y[i])**2)
        if np.any(distance == 0):
            continue
        Vg += G * z[i] / distance

    # Plot erstellen und speichern
    fig, ax = plt.subplots(dpi=1000)
    im = ax.contourf(X, Y, np.log10(Vg), cmap=plt.cm.hsv, levels=100)
    cbar = plt.colorbar(im)
    cbar.set_label('$log_{10}$ (|V| in AE²/a²)', size=11)
    ax.set_xlabel('x in AE')
    ax.set_ylabel('y in AE')

    # Diagramm speichern mit Anzahl der Körper und Zeitpunkt im Dateinamen
    plt.savefig('../Diagramme/Auswertung/KonturplotMassen/KonturplotMassen_{}k{}.png'.format(num_bodies, time_step))
    plt.close()


if __name__ == "__main__":
    main()

