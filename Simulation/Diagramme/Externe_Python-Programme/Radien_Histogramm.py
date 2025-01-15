import matplotlib
matplotlib.use('Agg') 

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
    plt.title('Verteilung der Abstände zum Massenmitttelpunkt (Zeit: {} Jahre)'.format(time_step))
    plt.xlabel('Logarithmus der Abstände zum Massenmittelpunkt in AE')
    plt.ylabel('Anzahl der Körper')
    plt.savefig('../Diagramme/Auswertung/Radien/Radienverteilung_{}k{}.png'.format(num_bodies, time_step))
    plt.close()

if __name__ == "__main__":
    main()
