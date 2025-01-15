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
void writeCoordinatesToFile(vector<Objekt>& objekte, const string& filename);

// Funktion zum Schreiben der Koordinaten und Massen in eine Datei
void writeCoordinatesAndMassesToFile(vector<Objekt>& objekte, const string& filename);

// Funktion zum Schreiben der Geschwindigkeiten in eine Datei
void writeVelocitiesToFile(vector<Objekt>& objekte, const string& filename);

// Funktion zum Schreiben der Radien in eine Datei
void writeRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename);

// Funktion zum Schreiben der kinetischen Energie in eine Datei
void writeEkinToFile(vector<Objekt>& objekte, const string& filename);

// Funktion zum Schreiben der potenziellen Energie in eine Datei
void writeEpotToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename);

// Funktion zum Schreiben von Abständen und Geschwindigkeiten in eine Datei
void writeVelocityDistanceToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename);

// Funktion zum Schreiben der Gesamtenergie des Systems in eine Datei
void writeEgesToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t);

// Funktion zum Schreiben des Verhältnis von potenzieller und kinetischer Energie des Systems in eine Datei
void writeEpotPerEkinToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t);

// Funktion zum Schreiben des maximalen Abstand zum Massnemittelpunkt des Systems in eine Datei
void writeMaxRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t);

// Funktion zum Schreiben des mittleren Abstand zum Massnemittelpunkt des Systems in eine Datei
void writeMediumRadiusToFile(vector<Objekt>& objekte, array<double, 7> mz, const string& filename, double t);

// Funktion zum Schreiben der maximalen Geschwindigkeit aller Körper des Systems in eine Datei
void writeMaxVelocitiesToFile(vector<Objekt>& objekte, const string& filename, double  t);

// Funktion zum Schreiben der mittleren Geschwindigkeit der Körper des Systems in eine Datei
void writeMediumVelocitiesToFile(vector<Objekt>& objekte, const string& filename, double t);

// Funktion zum Einlesen der Objekte aus einer Datei
vector<Objekt> readObjectsFromFile(const string& filename);