#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib> // Für rand()
#include <ctime>   // Für time()
#include <fstream> // Für Dateioperationen
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <cctype> // Für isdigit
#include "Nebenprogramm/Objekt.hpp"
#include "Nebenprogramm/Massepunkt.hpp"
#include "Nebenprogramm/neue_werte.hpp"
#include "Nebenprogramm/Funktionen.hpp"
#include <unistd.h>
using namespace std;


//Hauptschleife
int main() {
    srand(time(nullptr)); // Zufallsgenerator initialisieren
    stringstream command; // Stringstream-Objekt für Befehlszusammenbau oder String-Manipulation erstellen.  


    // Leeren noch befüllter Text-Dateien
    ofstream file1("../Diagramme/Daten/Eges.txt", ios::out | ios::trunc);
    file1.close();
    ofstream file2("../Diagramme/Daten/Rmed.txt", ios::out | ios::trunc);
    file2.close();
    ofstream file3("../Diagramme/Daten/Rmax.txt", ios::out | ios::trunc);
    file3.close();
    ofstream file4("../Diagramme/Daten/velocities.txt", ios::out | ios::trunc);
    file4.close();
    ofstream file5("../Diagramme/Daten/Radien.txt", ios::out | ios::trunc);
    file5.close();
    ofstream file6("../Diagramme/Daten/Ekin.txt", ios::out | ios::trunc);
    file6.close();
    ofstream file7("../Diagramme/Daten/Epot.txt", ios::out | ios::trunc);
    file7.close();
    ofstream file8("../Diagramme/Daten/EpotPerEkin.txt", ios::out | ios::trunc);
    file8.close();
    ofstream file9("../Diagramme/Daten/Vmed.txt", ios::out | ios::trunc);
    file9.close();

    // Objekte aus Datei einlesen
    string filename = "Datenbanksätze/NGC188.txt"; // Datei mit den Daten aus der ESA-Datenbank
    vector<Objekt> objekte = readObjectsFromFile(filename); // Funktion zum Übertragen der Daten aus der Datei ins Programm
    
    // Eichen der Daten
    vector<double> k;
    for (int i = objekte.size()-1; i >= 0; i--){
        k = objekte[i].getKoordinaten(); 

        // Koordinaten des Letzen Körpers im vector werden auf 0 gesetzt. Die Koordinaten aller anderen Körper werden nun neu berechnet mit dem letzten Körper als Koordinatenursprung
        objekte[i].changeKoordinaten({k[0] - objekte[0].getKoordinaten()[0], k[1] - objekte[0].getKoordinaten()[1], k[2] - objekte[0].getKoordinaten()[2]});
    }

    // Prüfen ob Objekte vorhanden sind
    if (objekte.empty()) {
        cerr << "Keine Objekte geladen!" << endl;
        return 1;  // Falls keine Objekte geladen wurden, Programm beenden
    }

    int n = objekte.size(); // Anzahl der Körper
    
    array<double, 7> _massezentrum; //_massezentrum initialisieren

    long long int time = 8e8; // Simulationsdauer in Jahren
    double schritt = 5000; // Simulationsschritt
    long long int plottime = 4e6; // Zeitintervalle zu denen Diagramme geplottet werden
    
    // Programmschleife von 0 bis Simulationsdauer
    for (double i = 0.0; i <= time; i += schritt) {

        _massezentrum = massezentrum(objekte); // Massezentrum berechnen
        for (int i2 = 0; i2 < objekte.size(); i2++) { // Alle Objekte durchgehen
            vector<double> koordinaten = objekte[i2].getKoordinaten(); // Koordinaten des Objekts übergeben
            vector<double> _neue_werte = neue_werte(_massezentrum[3], _massezentrum[0], _massezentrum[1], _massezentrum[2], // Koordinaten und Geschwindigkeiten der Körper neu errechnen
                                                    objekte[i2].getMass(), koordinaten[0], koordinaten[1], koordinaten[2], 
                                                    objekte[i2].getVx(), objekte[i2].getVy(), objekte[i2].getVz(), schritt,
                                                     _massezentrum[4], _massezentrum[5], _massezentrum[6]);

            objekte[i2].changeKoordinaten({_neue_werte[0], _neue_werte[1], _neue_werte[2]}); // Koordinaten des Körpers aktulisieren

            // Geschwindigkeiten der Körper aktualisieren
            objekte[i2].changeVx(_neue_werte[3]); 
            objekte[i2].changeVy(_neue_werte[4]);
            objekte[i2].changeVz(_neue_werte[5]);
        }

        
        // Koordinaten in Datei schreiben
        writeCoordinatesToFile(objekte, "../Diagramme/Daten/koordinaten.txt");
        this_thread::sleep_for(chrono::milliseconds(0)); // Simulationsintervall (auf 0 gesetzt für schnellste Darstellung) 

        // Alle 10^7 Jahre Diagramme erstellen bzw. am Anfang der Simulation in kürzeren Abständen
        if (int(i) % plottime == 0 || (int(i) % 2000000 == 0 && i <= 200000000) || (int(i) % 100000 == 0 && i <= 4000000) ) {
            
            writeEpotToFile(objekte, _massezentrum, "../Diagramme/Daten/Epot.txt"); // potenzielle Energie in Datei schreiben
            writeVelocitiesToFile(objekte, "../Diagramme/Daten/velocities.txt"); // Geschwindigkeiten in Datei schreiben
            writeRadiusToFile(objekte, _massezentrum, "../Diagramme/Daten/Radien.txt"); // Radien in Datei schreiben
            writeEkinToFile(objekte, "../Diagramme/Daten/Ekin.txt"); // kinetische Energien in Datei schreiben
            writeVelocityDistanceToFile(objekte, _massezentrum, "../Diagramme/Daten/velocity_distance.txt"); // Abstände und Geschwindigkeiten in Datei schreiben
            writeEgesToFile(objekte, _massezentrum, "../Diagramme/Daten/Eges.txt", i); // gesamte Energie in Datei schreiben
            writeMaxRadiusToFile(objekte, _massezentrum, "../Diagramme/Daten/Rmax.txt", i); // Maximalen Abstand zum Massenmittelpunkt in Datei schreiben
            writeMediumRadiusToFile(objekte, _massezentrum, "../Diagramme/Daten/Rmed.txt", i); // Mittleren Abstand zum Massenmittelpunkt in Datei schreiben
            writeEpotPerEkinToFile(objekte, _massezentrum, "../Diagramme/Daten/EpotPerEkin.txt", i); // Verhältnis der potenziellen zur kinetischen Energie in Datei schreiben
            writeMediumVelocitiesToFile(objekte, "../Diagramme/Daten/Vmed.txt", i); // Mittlere Geschwindigkeit 
            writeCoordinatesAndMassesToFile(objekte, "../Diagramme/Daten/konturplotmassen.txt"); // Koordinaten und Massen in Datei schreiben

            // Command für Python-Skript generieren und ausführen
            std::ostringstream command;
            command << "python3 ../Diagramme/Externe_Python-Programme/Ekin_Histogramm.py ../Diagramme/Daten/Ekin.txt " << n << " " << i; // Systembefehl ertellen
            system(command.str().c_str());  // Systembefehl ausführen

            // Wiederhole diesen Prozess für jedes andere Histogramm
            command.str("");  // Zurücksetzen der 'command' Stringstream
            command.clear();  // Klarstellung des Stringstreams
            command << "python3 ../Diagramme/Externe_Python-Programme/Radien_Histogramm.py ../Diagramme/Daten/Radien.txt " << n << " " << i;
            system(command.str().c_str());

            command.str("");
            command.clear();
            command << "python3 ../Diagramme/Externe_Python-Programme/Geschwindigkeit_Histogramm.py ../Diagramme/Daten/velocities.txt " << n << " " << i;
            system(command.str().c_str());

            command.str("");
            command.clear();
            command << "python3 ../Diagramme/Externe_Python-Programme/plot_velocity_distance.py ../Diagramme/Daten/velocity_distance.txt " << n << " " << i;
            system(command.str().c_str());

            command.str("");
            command.clear();
            command << "python3 ../Diagramme/Externe_Python-Programme/konturplotmassen.py ../Diagramme/Daten/konturplotmassen.txt " << n << " " << i;
            system(command.str().c_str());

            command.str("");
            command.clear();
            command << "python3 ../Diagramme/Externe_Python-Programme/Epot_Histogramm.py ../Diagramme/Daten/Epot.txt " << n << " " << i;
            system(command.str().c_str());
        }
    }

    command.str("");
    command.clear();
    command << "python3 ../Diagramme/Externe_Python-Programme/Eges.py ";
    system(command.str().c_str());

    command.str("");
    command.clear();
    command << "python3 ../Diagramme/Externe_Python-Programme/RmaxRmed.py ";
    system(command.str().c_str());

    command.str("");
    command.clear();
    command << "python3 ../Diagramme/Externe_Python-Programme/EpotPerEkin.py ";
    system(command.str().c_str());

    command.str("");
    command.clear();
    command << "python3 ../Diagramme/Externe_Python-Programme/Vmed.py ";
    system(command.str().c_str());


    return 0;
}
