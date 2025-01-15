#include <iostream>
#include <vector>
#include <array>
#include "Massepunkt.hpp"
#include "Objekt.hpp"

std::array<double,7> massezentrum(std::vector<Objekt>& objekte){
    int n = objekte.size(); // Anzahl der Körper
    // initialisieren der Masse, Koordinaten und Geschwindigkeiten des Massenmittelpunkts
    double Mg = 0;
    double xz = 0;
    double yz = 0;
    double zz = 0;
    double vxz = 0;
    double vyz = 0;
    double vzz = 0;
    std::array<double, 7> massezentrum; // initialisiern eines arrays der die Werte am Ende enthält
    
    
    for (int i = 0; i < n; i++){ // Für jeden Körper
        // Massen, Geschwindigkeiten und Koordinaten des Körpers 
        double mass = objekte[i].getMass();
        double vx = objekte[i].getVx();
        double vy = objekte[i].getVy();
        double vz = objekte[i].getVz();
        const std::vector<double>& koordinaten = objekte[i].getKoordinaten();

        Mg = Mg + mass; // Masse des Massenmittelpunkts erhöhen
        // Koordinaten und Geschwindikeiten des Massenmittelpunkts erhöhen
        xz += mass * koordinaten[0]; 
        yz += mass * koordinaten[1];
        zz += mass * koordinaten[2];
        vxz += mass * vx;
        vyz += mass * vy;
        vzz += mass * vz;
    }

    massezentrum = {xz, yz, zz, Mg, vxz, vyz, vzz}; 

    return massezentrum; // Zurückgeben der Werte
}