import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')
import sys

# Datei einlesen und Zeit- sowie Geschwindigkeitswerte in Listen speichern
filename = '../Diagramme/Daten/Vmed.txt'
times = []
velocities = []

# Datei einlesen
with open(filename, 'r') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) == 2:  # Sicherstellen, dass es genau zwei Spalten gibt
            try:
                time = float(parts[0])  # Zeitwert (x-Achse)
                velocity = float(parts[1])  # Geschwindigkeitswert (y-Achse)
                times.append(time)
                velocities.append(velocity)
            except ValueError:
                print(f"Warnung: Ungültiger Wert in Zeile: {line.strip()}")

# Prüfen, ob Daten vorhanden sind
if not times or not velocities:
    print("Fehler: Keine gültigen Daten in der Datei.")
    sys.exit(1)

# Diagramm erstellen
plt.plot(times, velocities, linestyle='-', marker='')
plt.title('Mittlere Geschwindigkeit - Zeit')
plt.xlabel('Zeit in Jahren')
plt.ylabel('Geschwindigkeit in AE/a')
plt.grid(True)

# Diagramm speichern
plt.savefig('../Diagramme/Auswertung/Vmed.png')

# Diagramm anzeigen (optional, wenn du es direkt sehen willst)
# plt.show()
