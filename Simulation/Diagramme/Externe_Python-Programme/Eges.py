import matplotlib.pyplot as plt
import sys
# Datei einlesen und Zeit- sowie Energiewerte in Listen speichern
filename = '../Diagramme/Daten/Eges.txt'
times = []
energies = []

# Datei einlesen
with open(filename, 'r') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) == 2:  # Sicherstellen, dass es genau zwei Spalten gibt
            try:
                time = float(parts[0])  # Zeitwert (x-Achse)
                energy = float(parts[1])  # Energiewert (y-Achse)
                times.append(time)
                energies.append(energy)
            except ValueError:
                print(f"Warnung: Ungültiger Wert in Zeile: {line.strip()}")

# Prüfen, ob Daten vorhanden sind
if not times or not energies:
    print("Fehler: Keine gültigen Daten in der Datei.")
    sys.exit(1)

# Diagramm erstellen
plt.ylim(0, max(energies) * 2)
plt.xlim(0, max(times))
plt.plot(times, energies, linestyle='-', marker='')
plt.title('Gesamtenergie - Zeit')
plt.xlabel('Zeit in Jahren')
plt.ylabel('Gesamtenergie in 4.47 * 10³⁷J)')
plt.grid(True)

# Diagramm speichern
plt.savefig('../Diagramme/Auswertung/Eges.png')

# Diagramm anzeigen (optional)
# plt.show()
