#include <iostream>
#include <vector>
#include <cmath>
#include "neue_werte.hpp"

std::vector<double> neue_werte(double Mg, double xz, double yz , double zz , double mk, double xk , double yk, double zk, double vx, double vy, double vz, double t, double vxz, double vyz, double vzz, double ID){
    // Attribute des Massenmittelpunkts
    double Ms = Mg - mk;
    double xs = (xz - xk * mk)/Ms;
    double ys = (yz - yk * mk)/Ms;
    double zs = (zz - zk * mk)/Ms;
    double vxs = (vxz - vx * mk)/Ms;
    double vys = (vyz - vy * mk)/Ms;
    double vzs = (vzz - vz * mk)/Ms;

    double r = sqrt(pow(xs-xk,2) + pow(ys-yk,2) + pow(zs - zk,2)); // Abstand des Körpers zum Massenmittelpunkt

    // Beschleunigung des Körpers in X-, Y- und Z-Richtung
    double ax = ((37.4227) * Ms * (xs - xk)) / pow(r,3);
    double ay = ((37.4227) * Ms * (ys - yk)) / pow(r,3);
    double az = ((37.4227) * Ms * (zs - zk)) / pow(r,3);

    // Gesamtbeschleunigung und -geschwindigkeit bestimmen
    double ages = sqrt(pow(ax,2) + pow(ay,2) + pow(az,2));
    double vges = sqrt(pow(vx,2) + pow(vy,2) + pow(vz,2));

    // Dynamische Zeitskala
    if (ages < 2 * vges * 2/(t) || vges == 0){ // Wenn der Weg der Beschleunigung den Weg der normalen Geschwindigkeit nicht überwiegt

        // Zurückgelegten weg innerhalb des Zeitintervall mittels Halbschrittverfahren berechnen
        double sx1 = vx * 0.5 * t + ax * pow(0.5 * t, 2)/2;
        double sy1 = vy * 0.5 * t + ay * pow(0.5 * t, 2)/2;
        double sz1 = vz * 0.5 * t + az * pow(0.5 * t, 2)/2;

        // Neue Geschwindigkeit
        vx = vx + ax * t;
        vy = vy + ay * t;
        vz = vz + az * t;

        // Zweite Streckenberechnung des Halbschrittverfahrens
        double sx2 = vx * 0.5 * t + ax * pow(0.5 * t, 2)/2;
        double sy2 = vy * 0.5 * t + ay * pow(0.5 * t, 2)/2;
        double sz2 = vz * 0.5 * t + az * pow(0.5 * t, 2)/2;

        // Aktualisieren der Koordinaten
        xk = xk + sx1 + sx2;
        yk = yk + sy1 + sy2;
        zk = zk + sz1 + sz2;

        std::vector<double> ergebnisse = {xk, yk, zk, vx, vy ,vz};

        return ergebnisse; // Rückgabe der Koordinaten
    }
    
    else{ // Ansonsten 
        double tneu = (0.5 * t - vges / ages) / 5; // Bestimme kleineres Zeitintervall

        // gehe dieses mit diesem Zeitintervall erneut den Schritt durch
        for (double i = 0; i < t - tneu; i += tneu){

            // Mit kleineren Schritten genaueres Ergebnis für die Koordinaten und Geschwindigkeiten bestimmen
            std::vector<double> ergebnisseKoerper = neue_werte( Mg,  xz,  yz ,  zz ,  mk,  xk ,  yk,  zk,  vx,  vy,  vz,  tneu,  vxz,  vyz,  vzz, ID);
            std::vector<double> ergebnisseZentrum = neue_werte( Mg,  xz,  yz ,  zz ,  Ms,  xs ,  ys,  zs,  vxs,  vys,  vzs,  tneu,  vxz,  vyz,  vzz, ID);
            xk = ergebnisseKoerper[0];
            yk = ergebnisseKoerper[1];
            zk = ergebnisseKoerper[2];
            vx = ergebnisseKoerper[3];
            vy = ergebnisseKoerper[4];
            vz = ergebnisseKoerper[5];

            xz = ergebnisseZentrum[0] * Ms + mk * xk;
            yz = ergebnisseZentrum[1] * Ms + mk * yk;
            zz = ergebnisseZentrum[2] * Ms + mk * zk;
            vxz = ergebnisseZentrum[3] * Ms + mk * vx;
            vyz = ergebnisseZentrum[4] * Ms + mk * vy;
            vzz = ergebnisseZentrum[5] * Ms + mk * vz;
        }
        std::vector<double> ergebnisse = {xk, yk, zk, vx, vy ,vz};

        return ergebnisse; // Rückgabe der Koordinaten und Geschwindigkeiten
    }
}