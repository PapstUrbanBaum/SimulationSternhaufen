#pragma once

#include <iostream>
#include <vector>


class Objekt {
    // Initialisieren der Attribute 
    private:std::vector<double> koordinaten;
    private:double objekt_mass;
    private:double vx;
    private:double vy;
    private:double vz;
    private:int ID;

public:
    //Kontruktor
    Objekt(std::vector<double> neu_koordinaten, double neu_mass, double neu_vx, double neu_vy, double neu_vz, double IDneu = 0);
    std::vector<double> getKoordinaten() const;
    double getMass();
    double getVx();
    double getVy();
    double getVz();
    double getID();

    void changeKoordinaten(std::vector<double> k);
    void changeMass(double m);
    void changeVx(double v);
    void changeVy(double v);
    void changeVz(double v);
    void changeID(double v);

};