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
#include "Objekt.hpp"
#include "Massepunkt.hpp"
#include <unistd.h>
using namespace std;

// Funktion zum Schreiben der Koordinaten in eine Datei
void writeCoordinatesToFile(vector<Objekt>& objekte, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();
        file << koordinaten[0] << " " << koordinaten[1] << " " << koordinaten[2] << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der Koordinaten und Massen in eine Datei
void writeCoordinatesAndMassesToFile(vector<Objekt>& objekte, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();
        file << koordinaten[0] << " " << koordinaten[1] << " " << koordinaten[2] <<  " " << obj.getMass() << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der Geschwindigkeiten in eine Datei
void writeVelocitiesToFile(vector<Objekt>& objekte, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        double v = sqrt(obj.getVx() * obj.getVx() + obj.getVy() * obj.getVy() + obj.getVz() * obj.getVz()); // Gesamtgeschwindigkeit berechnen
        file << v << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der Radien in eine Datei
void writeRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        vector<double> k = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - k[0] * obj.getMass())/ms;
        double ys = (mz[1] - k[1] * obj.getMass())/ms;
        double zs = (mz[2] - k[2] * obj.getMass())/ms;

        double r = sqrt(pow(xs - k[0], 2) + pow(ys - k[1], 2) + pow(zs - k[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        file << r << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der kinetischen Energie in eine Datei
void writeEkinToFile(vector<Objekt>& objekte, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        double v = sqrt((obj.getVx() * obj.getVx()) + (obj.getVy() * obj.getVy()) + (obj.getVz() * obj.getVz())); // Gesamtgeschwindigkeit berechnen
        double Ekin = 0.5 * obj.getMass() * pow(v,2); // kinetische Energie berechnen
        file << Ekin << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der potenziellen Energie in eine Datei
void writeEpotToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;
        
        double r = sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        double Epot = (37.4227) * obj.getMass()* (ms-obj.getMass()) / r; // potenzielle Energie berechnen
        file << Epot << "\n";
    }
    file.close();
}

// Funktion zum Schreiben von Radien und Geschwindigkeiten in eine Datei
void writeVelocityDistanceToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename) {
    ofstream file(filename);
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;
        
        double r = sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        double v = sqrt(obj.getVx() * obj.getVx() + obj.getVy() * obj.getVy() + obj.getVz() * obj.getVz()); // Gesamtgeschwindigkeit berechnen
        file << r << " " << v << "\n";
    }
    file.close();
}

// Funktion zum Schreiben der Gesamtenergie des Systems in eine Datei
void writeEgesToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t) {
    ofstream file(filename, ios::app);
    double Eges = 0;
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();
        
        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;
        
        double r = sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        double Epot = -(37.4227) * obj.getMass()* (ms) / r; // potenzielle Energie berechnen

        double v = sqrt((obj.getVx() * obj.getVx()) + (obj.getVy() * obj.getVy()) + (obj.getVz() * obj.getVz())); // Gesamtgeschwindigkeit berechnen
        double Ekin = 0.5 * obj.getMass() * pow(v,2); // kinetische Energie berechnen

        Eges = Eges + Ekin + Epot; // kinetische und potenzielle Energie des Körpers zur Gesamtenergie des Systems addieren
    }
    file << t << " " << Eges << "\n";
    file.close();
}

// Funktion zum Schreiben des Verhältnis zwischen potenzieller und kinetischer Energie des Systems in eine Datei
void writeEpotPerEkinToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t) {
    ofstream file(filename, ios::app);
    double Ekin = 0;
    double Epot = 0;
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;
        
        double r = sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        Epot += -(37.4227) * obj.getMass()* (ms) / r; // potenzielle Energie berechnen

        double v = sqrt((obj.getVx() * obj.getVx()) + (obj.getVy() * obj.getVy()) + (obj.getVz() * obj.getVz())); // Gesamtgeschwindigkeit berechnen
        Ekin += 0.5 * obj.getMass() * pow(v,2); // kinetische Energie berechnen

        
    }
    file << t << " " << Epot/Ekin << "\n";
    file.close();
}


// Funktion zum Schreiben des maximalen Abstands zum Massenmittelpunkt in eine Datei
void writeMaxRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t) {
    ofstream file(filename, ios::app);
    double r = 0;
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;
        
        double rneu = sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand zum Massenmittelpunkt berechnen
        if (rneu > r){ // Abstand zum Massenmittlepunkt des betrachteten Körpers mit bisherigem größten Abstand vergleichen
            r = rneu; // sollte er größer sein, maximalen Abstand zum Massenmittelpunkt neu definieren
        }
    }
    file << t << " " << r << "\n";
    file.close();
}

// Funktion zum Schreiben der mittleren Entfernung zum Massnemittelpunkt des Systems in eine Datei
void writeMediumRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t) {
    ofstream file(filename, ios::app);
    double r = 0;
    for (auto& obj : objekte) {// Abstand zum Massenmittelpunkt berechnen
        vector<double> koordinaten = obj.getKoordinaten();

        // Herausrechnen des Körpers aus dem Massenmittelpunkt
        double ms = mz[3] - obj.getMass();
        double xs = (mz[0] - koordinaten[0] * obj.getMass())/ms;
        double ys = (mz[1] - koordinaten[1] * obj.getMass())/ms;
        double zs = (mz[2] - koordinaten[2] * obj.getMass())/ms;

        r += sqrt(pow(xs - koordinaten[0], 2) + pow(ys - koordinaten[1], 2) + pow(zs - koordinaten[2], 2)); // Abstand des Körpers zum Massenmittelpunkt zum Gesamtabstand addieren
    }
    r = r / objekte.size(); // Teilen des Gesamtabstandes durch die Anzahl der Körper um den mittleren Abstand zu erhalten
    file << t << " " << r << "\n";
    file.close();
}

// Funktion zum Schreiben der mittleren Geschwindigkeit des Systems in eine Datei
void writeMediumVelocitiesToFile(vector<Objekt>& objekte, const string& filename, double t) {
    ofstream file(filename, ios::app);
    double v = 0;
    for (auto& obj : objekte) {
        vector<double> koordinaten = obj.getKoordinaten();
        v += sqrt(pow(obj.getVx(), 2) + pow(obj.getVy(), 2) + pow(obj.getVz(), 2)); //Gesamtgeschwindigkeit des Körpers zu der des Systems hinzurechnen
    }
    v = v / objekte.size(); // Gesamtgeschwindigkeit aller Körper des Systems durch Anzahl der Körper teilen um mittlere Geschwindigkeit zu erhalten
    file << t << " " << v << "\n";
    file.close();
}


// Funktion zum Einlesen der Objekte aus einer Datei
vector<Objekt> readObjectsFromFile(const string& filename) {
    vector<Objekt> objekte;
    ifstream file(filename);
    
    //Prüfen ob Datei zum Schreiben bereit ist
    if (!file.is_open()) {
        cerr << "Fehler beim Öffnen der Datei!" << endl;
        return objekte;
    }
    
    string line;
    double l = 1;
    while (getline(file, line)) { // Jede Zeile
        stringstream ss(line);
        double ID, vx, vy, vz, x, y, z, mass;
        char comma;
        
        // Werte aus der Zeile extrahieren
        if (ss >> ID >> comma >> x >> comma >> y >> comma >> z >> comma >> vx >> comma >> vy >> comma >> vz >> comma >> mass) {
            // Neues Objekt mit den gelesenen Werten erstellen
            objekte.push_back(Objekt({x, y, z}, mass, vx, vy, vz, l));
        }
        l++;
    }
    
    file.close();
    return objekte; // vector mit Körpern zurückgeben
}