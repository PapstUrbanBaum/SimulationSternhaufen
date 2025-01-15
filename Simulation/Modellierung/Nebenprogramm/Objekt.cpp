#include "Objekt.hpp"


// Klasse Objekt
Objekt::Objekt(std::vector<double> neu_koordinaten, double neu_mass, double neu_vx, double neu_vy, double neu_vz, double IDneu) {
    koordinaten = neu_koordinaten;
    objekt_mass = neu_mass;
    vx = neu_vx;
    vy = neu_vy;
    vz = neu_vz;
    ID = IDneu;
}

// Methode zum zurückgeben der Koordinaten
std::vector<double> Objekt::getKoordinaten() const{
    return koordinaten;
}

// Methode zum zurückgeben der Masse
double Objekt::getMass() {
    return objekt_mass;
}

// Methode zum zurückgeben der Geschwindigkeit in X-Richtung
double Objekt::getVx() {
    return vx;
}

// Methode zum zurückgeben der Geschwindigkeit in Y-Richtung
double Objekt::getVy() {
    return vy;
}

// Methode zum zurückgeben der Geschwindigkeit in Z-Richtung
double Objekt::getVz() {
    return vz;
}

// Methode zum zurückgeben der ID
double Objekt::getID() {
    return ID;
}


// Methode zum verändern der Koordinaten
void Objekt::changeKoordinaten(std::vector<double> k){
    koordinaten = k;
}

// Methode zum verändern der Geschwindigkeit in X-Richtung
void Objekt::changeVx(double v){
    vx = v;
}

// Methode zum verändern der Geschwindigkeit in Y-Richtung
void Objekt::changeVy(double v){
    vy = v;
}

// Methode zum verändern der Geschwindigkeit in Z-Richtung
void Objekt::changeVz(double v){
    vz = v;
}

// Methode zum verändern der ID
void Objekt::changeID(double v){
    ID = v;
}