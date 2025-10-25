#include "filmstudio.h"
#include "drachenart.h"
#include "drachenflug.h"
#include "nachtlager.h"
#include <fstream>
#include <QMessageBox>
#include <QString>
#include <iostream>


using namespace std;

Filmstudio::Filmstudio() {
   // einlesenJSON("C:/c++/prak3/filmstudio.json");     // ***** Aufgabe 8e: Auslagern in das Menü der GUI *****
}

Filmstudio::~Filmstudio() {
    for (auto d : drachenListe)
        delete d;
    drachenListe.clear();

    for (auto& [key, poi] : poiMap)
        delete poi;
    poiMap.clear();
}


Drache* Filmstudio::sucheDrache(const string& name) {
    for (auto d : drachenListe) {
        if (d->getDrachenName() == name) {
            return d;
        }
    }
    return nullptr;
}

vector<Drache*>& Filmstudio::getDrachenListe() {
    return drachenListe;
}

Drachenreise* Filmstudio::getDrachenreise(const int reiseNr) {
    for (Drache* d : drachenListe) {
        for (Reiseplan* plan : d->getReiseplaene()) {
            for (Drachenreise* r : plan->getReiseabschnitte()) {
                if (r->getReiseNummer() == reiseNr) {
                    return r;
                }
            }
        }
    }
    return nullptr;
}

bool Filmstudio::loescheDrache(string name)
{
    for (unsigned i = 0; i < drachenListe.size(); ++i) {
        if(drachenListe[i]->getDrachenName()==name){
            delete drachenListe[i];
            drachenListe.erase(drachenListe.begin()+i);
            return true;
        }
    }
    return false;
}

std::vector<ReiseInfo *> Filmstudio::findeReiseplaeneAlsPlayer(const string &name)
{
    std::vector<ReiseInfo*> result;

    for (auto* drache : drachenListe) {
        if (drache->getMeinPlayer() == name) {
            for (auto* plan : drache->getReiseplaene()) {
                ReiseInfo* info = new ReiseInfo;
                info->nummer = plan->getReiseplanNummer();
                info->name = plan->getName();
                info->beginn = plan->getPlanBeginn();  // Diese Methode in Reiseplan wird weiter unten erklärt
                info->ende = plan->getPlanEnde();      // Diese Methode in Reiseplan wird weiter unten erklärt
                info->preis=plan->berechneGesamtpreis();
                result.push_back(info);
            }
        }
    }
    return result;
}

std::vector<ReiseInfo *> Filmstudio::findeReiseplaeneAlsPassagier(const string &name)
{
    std::vector<ReiseInfo*> result;

    for (auto* drache : drachenListe) {
        for (auto* plan : drache->getReiseplaene()) {
            const auto& passagiere = plan->getPassagiere();
            if (std::find(passagiere.begin(), passagiere.end(), name) != passagiere.end()) {
                ReiseInfo* info = new ReiseInfo;
                info->nummer = plan->getReiseplanNummer();
                info->name = plan->getName();
                info->beginn = plan->getPlanBeginn();
                info->ende = plan->getPlanEnde();
                info->preis=plan->berechnePreisFuerPassagier(name);
                result.push_back(info);
            }
        }
    }
    return result;
}

Reiseplan *Filmstudio::findeReiseplan(int planNr)
{
    for (Drache* d : drachenListe) {
        for (Reiseplan* r : d->getReiseplaene()) {
            if (r->getReiseplanNummer() == planNr) {
                return r;
            }
        }
    }
    return nullptr;
}

std::map<std::string, POI *> Filmstudio::getPoiMap() const
{
    return poiMap;
}

void Filmstudio::einlesenPOIDatei(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open()) {
        // QMessageBox::critical(nullptr, "Fehler", "Konnte die Datei nicht öffnen: " + QString::fromStdString(filename));
        throw std::runtime_error("Konnte Datei nicht öffnen: " + filename);
    }

    json j;
    file >> j;
    for(auto &[key, poi]:poiMap){
        delete poi;
    }
    poiMap.clear();

     for (auto& [key, value] : j.items()) {
        try {
            POI* poi = new POI(value);  // Konstruktor mit json-Objekt
            poiMap[key] = poi;
        } catch (const json::exception& e) {
            //std::cerr << "Fehler beim Einlesen von POI " << key << ": " << e.what() << std::endl;
              throw std::runtime_error("Fehler bei POI: " + key);
        }
     }

}

void Filmstudio::speichernPOIDatei(const string &filename)
{
json j;

    for (const auto& [key, poi] : poiMap) {
        j[key] = poi->to_JSON();
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Konnte Datei nicht öffnen: " + filename);
    }

    file << j.dump(4);
    file.close();

    if (!file) {
        QMessageBox::critical(nullptr, "Fehler", "Konnte nicht in Datei " + QString::fromStdString(filename) + " schreiben!");
    }
}

void Filmstudio::aktualisiereEntfernungenInDrachenfluegen()
{
    for (auto& drache : drachenListe) {
        for (auto* plan : drache->getReiseplaene()) {

            // ***** Teil wird nochmals in on_addDrachenreiseButton_clicked benötigt *****
            aktualisiereEntfernungenInReiseplan(plan);
        }
    }

}

void Filmstudio::aktualisiereEntfernungenInReiseplan(Reiseplan *plan)
{
    auto& abschnitte = plan->getReiseabschnitte();
    for (size_t i = 1; i < abschnitte.size(); ++i) {
        auto* flug = dynamic_cast<Drachenflug*>(abschnitte[i]);
        if (!flug) continue;  // Abschnitt ist kein Flug → überspringen

        std::string startOrt;

        // Bestimme Startort: entweder aus vorherigem Nachtlager oder vorherigem Flug
        if (auto* vorherLager = dynamic_cast<Nachtlager*>(abschnitte[i - 1])) {
            startOrt = vorherLager->getLagerOrt();
        } else if (auto* vorherFlug = dynamic_cast<Drachenflug*>(abschnitte[i - 1])) {
            startOrt = vorherFlug->getZiel();
        } else {
            std::cerr << "[WARN] Kein gültiger Startort für Flug " << flug->getFlugNummer() << std::endl;
            continue;
        }

        const std::string& zielOrt = flug->getZiel();

        double distanz = berechneEntfernungZwischenPOIs(startOrt, zielOrt, poiMap);
        flug->setEntfernung(distanz);
        flug->setPreis(distanz * 3.74);

        std::cout << "[INFO] Flug " << flug->getFlugNummer() << ": " << startOrt << " → " << zielOrt
                  << " | Entfernung: " << distanz << " km | Preis: " << distanz * 3.74 << " DC" << std::endl;
    }

}

void Filmstudio::addPoi(POI *poi)
{
    if (!poi) return;

    // POI-Key automatisch generieren (z. B. "poi17", "poi18" ...)
    int maxNum = 0;
    for (const auto& [key, _] : poiMap) {
        if (key.substr(0, 3) == "poi") {
            try {
                int num = std::stoi(key.substr(3));
                maxNum = std::max(maxNum, num);
            } catch (...) {
                // Nicht parsbarer Schlüssel: ignorieren
            }
        }
    }

    std::string newKey = "poi" + std::to_string(maxNum + 1);
    poiMap[newKey] = poi;

    std::cout << "[INFO] Neuer POI hinzugefügt: " << newKey << " (" << poi->getName() << ")\n";

}

double Filmstudio::haversine(double lat1, double lon1, double lat2, double lon2)
{
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
                   std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_RADIUS_KM * c;

}

double Filmstudio::toRadians(double degree)
{
    return degree * M_PI / 180.0;;
}

double Filmstudio::berechneEntfernungZwischenPOIs(const string &ort1, const string &ort2, const std::map<string, POI *> &poiMap)
{
    POI* p1 = nullptr;
    POI* p2 = nullptr;

    for (const auto& [key, poi] : poiMap) {
        if (poi->getName() == ort1) p1 = poi;
        if (poi->getName() == ort2) p2 = poi;
        if (p1 && p2) break;
    }

    if (!p1 || !p2) return 0.0;

    return haversine(p1->getLatitude(), p1->getLongitude(), p2->getLatitude(), p2->getLongitude());

}






void Filmstudio::addDrache(Drache* d) {
    drachenListe.push_back(d);
}



void Filmstudio::einlesenJSON(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
       // QMessageBox::critical(nullptr, "Fehler", "Konnte die Datei nicht öffnen: " + QString::fromStdString(filename));
       throw std::runtime_error("Konnte Datei nicht öffnen: " + filename);
    }

    json j;
    file >> j;

    for (auto& dracheJson : j) {
        std::string art;
        try {
            art = dracheJson.at("drachenArt").get<std::string>();
        } catch (const json::exception& e) {
            // Exception wird gefangen und an die GUI weitergegeben, damit hier keine QMessageBox der GUI
            // ohne Exception wäre hier die das try und catch nicht und die Mitteilung dafür per QMessageBox
            throw std::runtime_error("Fehlendes oder ungültiges Feld 'drachenArt': " + std::string(e.what()));
        }

        Drache* d = nullptr;

        if (art == "Nachtschatten")
            d = new Nachtschatten(dracheJson);
        else if (art == "Tagschatten")
            d = new Tagschatten(dracheJson);
        else if (art == "ToedlicherNadder")
            d = new ToedlicherNadder(dracheJson);
        else if (art == "Skrill")
            d = new Skrill(dracheJson);
        else {
          //  QMessageBox::critical(nullptr, "Fehler", "Unbekannte Drachenart beim speichern: " + QString::fromStdString(art));
             throw std::runtime_error("Unbekannte Drachenart: " + art);
        }

        drachenListe.push_back(d);
    }
}


void Filmstudio::speichernJSON(const std::string& filename) {
    json j;

    for (auto d : drachenListe) {
        j.push_back(d->to_json());
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Konnte Datei nicht öffnen: " + filename);
    }

    file << j.dump(4);
    file.close();

    if (!file) {
        QMessageBox::critical(nullptr, "Fehler", "Konnte nicht in Datei " + QString::fromStdString(filename) + " schreiben!");
    }
}




