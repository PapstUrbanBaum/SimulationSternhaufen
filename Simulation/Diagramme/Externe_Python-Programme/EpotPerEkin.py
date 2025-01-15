import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')  # Backend für das Rendern ohne GUI
import sys

# Datei einlesen und Zeit- sowie Werte in Listen speichern
filename = '../Diagramme/Daten/EpotPerEkin.txt'
times = []
ratios = []

# Datei einlesen
with open(filename, 'r') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) == 2:  # Sicherstellen, dass es genau zwei Spalten gibt
            try:
                time = float(parts[0])  # Zeitwert (x-Achse)
                ratio = float(parts[1])  # Epot/Ekin-Wert (y-Achse)
                times.append(time)
                ratios.append(ratio)
            except ValueError:
                print(f"Warnung: Ungültiger Wert in Zeile: {line.strip()}")

# Prüfen, ob Daten vorhanden sind
if not times or not ratios:
    print("Fehler: Keine gültigen Daten in der Datei.")
    sys.exit(1)

# Diagramm erstellen
plt.ylim(0, max(ratios)*100)
plt.xlim(0, max(times))
plt.plot(times, ratios, linestyle='-', marker='')  # Linie ohne Punkte
plt.title('Verhältnis der potenziellen zur kinetischen Energie über die Zeit')
plt.xlabel('Zeit in Jahren')
plt.ylabel('Epot/Ekin')
plt.grid(True)

# Diagramm speichern
plt.savefig('../Diagramme/Auswertung/EpotPerEkin.png')

# Diagramm anzeigen (optional, wenn du es direkt sehen willst)
# plt.show()
