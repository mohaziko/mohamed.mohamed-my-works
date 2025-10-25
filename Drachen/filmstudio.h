#ifndef FILMSTUDIO_H
#define FILMSTUDIO_H

#include "drache.h"

#include <string>
#include <map>
#include "poi.h"
#include <cmath>

constexpr double EARTH_RADIUS_KM = 6371.0;

struct ReiseInfo
{
    int nummer;
    string name;
    string beginn;
    string ende;
    double preis;
};

class Filmstudio {
public:

    Filmstudio();
    ~Filmstudio();

    void einlesenJSON(const std::string& filename);
    void speichernJSON(const std::string& filename);

    Drache* sucheDrache(const std::string& name);
    void addDrache(Drache* d);

    // --------- getter ---------
    vector<Drache*>& getDrachenListe();
    Drachenreise* getDrachenreise(const int reiseNr);  // war getDrachenflug
    bool loescheDrache(string name);//Aufgabe 9(a)

    std::vector<ReiseInfo*> findeReiseplaeneAlsPlayer(const std::string& name);//Aufgabe 10(g)
    std::vector<ReiseInfo*> findeReiseplaeneAlsPassagier(const std::string& name);//Aufgabe 10(g)

    Reiseplan* findeReiseplan(int planNr);

    // POI Map Zugriff
           std::map<std::string, POI *> getPoiMap() const;

    // POI JSON einlesen
    void einlesenPOIDatei(const std::string& filename);
    void speichernPOIDatei(const std::string& filename) ;

    void aktualisiereEntfernungenInDrachenfluegen();
    void aktualisiereEntfernungenInReiseplan(Reiseplan* plan);
    void addPoi(POI* poi) ;
    double berechneEntfernungZwischenPOIs(const std::string& ort1, const std::string& ort2, const std::map<std::string, POI*>& poiMap);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    double toRadians(double degree);




private:
    vector<Drache*> drachenListe;
    std::map<std::string, POI*> poiMap;
};

#endif // FILMSTUDIO_H
