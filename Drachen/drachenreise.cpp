#include "drachenreise.h"

int Drachenreise::naechsteNummer = 1000;


// Konstruktor mit Parametern
Drachenreise::Drachenreise(string abf, string ank, double p)
    : reiseNummer(naechsteNummer++), abfahrt(abf), ankunft(ank), preis(p) {
}

// Konstruktor zum Einlesen
Drachenreise::Drachenreise(const json& j) {
    reiseNummer = j["reiseNummer"];
    abfahrt = j["abfahrt"];
    ankunft = j["ankunft"];
    preis = j["preis"]; // optional für Nachtlager

    if (reiseNummer >= naechsteNummer) {
        naechsteNummer = reiseNummer + 1;
    }
}

json Drachenreise::to_json_base() const {
    json j;
    j["reiseNummer"] = reiseNummer;
    j["abfahrt"] = abfahrt;
    j["ankunft"] = ankunft;
    j["preis"] = preis;
    return j;
}

// --------- getter ---------
int Drachenreise::getReiseNummer() const { return reiseNummer; }
string Drachenreise::getAbfahrt() const { return abfahrt; }
string Drachenreise::getAnkunft() const { return ankunft; }
double Drachenreise::getPreis() const { return preis; }
Reiseplan *Drachenreise::getReiseplan() const { return reiseplan; }

// --------- setter ---------
void Drachenreise::setReiseplan(Reiseplan* plan) { reiseplan = plan; }

void Drachenreise::setAbfahrt(const std::string &newAbfahrt)
{
    abfahrt = newAbfahrt;
}

void Drachenreise::setAnkunft(const std::string &newAnkunft)
{
    ankunft = newAnkunft;
}

void Drachenreise::setPreis(double newPreis)
{
    preis = newPreis;
}

bool Drachenreise::operator<(const Drachenreise &other) const
{
return makeSortable(this->abfahrt) < makeSortable(other.abfahrt);
}

int Drachenreise::makeSortable(const string &dateStr)
{
    int day = std::atoi(dateStr.substr(0, 2).c_str());
    int month = std::atoi(dateStr.substr(3, 2).c_str());
    int year = std::atoi(dateStr.substr(6, 4).c_str());
    return year * 10000 + month * 100 + day;

}


