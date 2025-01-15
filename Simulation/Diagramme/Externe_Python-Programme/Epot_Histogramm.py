import matplotlib
matplotlib.use('Agg') 

import os


import matplotlib.pyplot as plt
import numpy as np
import sys

def main():
    # Argumente vom Befehlszeilenaufruf abrufen
    if len(sys.argv) != 4:
        print("Usage: python plot_histogram.py <velocity_file> <num_bodies> <time_step>")
        return

    velocity_file = sys.argv[1]
    num_bodies = int(sys.argv[2])
    time_step = float(sys.argv[3])

    # Daten aus der Datei einlesen
    with open(velocity_file, 'r') as file:
        data = [float(line.strip()) for line in file]

    # Logarithmische Skala für die x-Achse
    log_data = np.log10(data)  

    # Diagramm erstellen
    plt.hist(log_data, bins=50)
    plt.title('Verteilung der potenziellen Energie (Zeit: {} Jahre)'.format(time_step))
    plt.xlabel('Logarithmus der potenziellen Energie in 4.47 * 10³⁷J')
    plt.ylabel('Anzahl der Körper')
    save_path = os.path.expanduser('../Diagramme/Auswertung/Epot/Epotverteilung_{}k{}.png'.format(num_bodies, time_step))
    plt.savefig(save_path)

    plt.close()

if __name__ == "__main__":
    main()