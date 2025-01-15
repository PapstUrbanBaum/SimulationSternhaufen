import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')  # Backend für das Rendern ohne GUI
import sys

# Funktion zum Einlesen von Daten aus einer Datei
def read_data(filename):
    times = []
    values = []
    try:
        with open(filename, 'r') as file:
            for line in file:
                parts = line.strip().split()
                if len(parts) == 2:  # Sicherstellen, dass es genau zwei Spalten gibt
                    try:
                        time = float(parts[0])      # Zeitwert (x-Achse)
                        value = float(parts[1])     # Wert (y-Achse)
                        times.append(time)
                        values.append(value)
                    except ValueError:
                        print(f"Warnung: Ungültiger Wert in Zeile: {line.strip()}")
    except FileNotFoundError:
        print(f"Fehler: Datei '{filename}' nicht gefunden.")
        sys.exit(1)

    if not times or not values:
        print(f"Fehler: Keine gültigen Daten in der Datei '{filename}'.")
        sys.exit(1)
    
    return times, values

# Hauptprogramm
# Dateien einlesen
rmax_file = '../Diagramme/Daten/Rmax.txt'
rmed_file = '../Diagramme/Daten/Rmed.txt'

# Rmax-Daten
times_rmax, values_rmax = read_data(rmax_file)

# Rmed-Daten
times_rmed, values_rmed = read_data(rmed_file)

# Diagramm erstellen
plt.figure(figsize=(10, 6))  # Größe des Diagramms

# Rmax plotten
plt.plot(times_rmax, values_rmax, linestyle='-', color='blue', label='Maximaler Abstand (Rmax)')

# Rmed plotten
plt.plot(times_rmed, values_rmed, linestyle='-', color='red', label='Mittlerer Abstand (Rmed)')

# Diagramm erstellen
plt.title('Abstand zum Massenmittelpunkt - Zeit')
plt.xlabel('Zeit in Jahren')
plt.ylabel('Abstand zum Massenmittelpunkt in AE')
plt.grid(True)
plt.legend()  # Legende anzeigen

# Diagramm speichern
plt.savefig('../Diagramme/Auswertung/RmaxRmed.png')

# Optional: Diagramm anzeigen
# plt.show()
