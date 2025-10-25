#include "nachtlager.h"

int Nachtlager::naechsteLagerID = 1000;

Nachtlager::Nachtlager(string abf, string ank, double p, string ort, string typ, int ruhe)
    : Drachenreise(abf, ank, p), lagerOrt(ort), unterkunftsTyp(typ), ruheLevel(ruhe), lagerID(naechsteLagerID++) {
}

Nachtlager::Nachtlager(const json& j) : Drachenreise(j) {
    lagerID = j["lagerID"];
    lagerOrt = j["ort"];
    unterkunftsTyp = j["unterkunftsTyp"];
    ruheLevel = j["ruheLevel"];
    preis = j.value("preis", 0.0);

    if (lagerID >= naechsteLagerID)
        naechsteLagerID = lagerID + 1;
}


json Nachtlager::to_json() const {
    json j = to_json_base();  // gemeinsame Felder werden in neuer Basisklasse behandelt
    j["typ"] = "nachtlager";
    j["lagerID"] = lagerID;
    j["ort"] = lagerOrt;
    j["unterkunftsTyp"] = unterkunftsTyp;
    j["ruheLevel"] = ruheLevel;
    return j;
}

string Nachtlager::getTyp() const {
    return "nachtlager";
}

int Nachtlager::getLagerID() const { return lagerID; }
string Nachtlager::getLagerOrt() const { return lagerOrt; }
string Nachtlager::getUnterkunftsTyp() const { return unterkunftsTyp; }
double Nachtlager::getRuheLevel() const { return ruheLevel; }


void Nachtlager::setLagerOrt(const std::string &newLagerOrt)
{
    lagerOrt = newLagerOrt;
}

void Nachtlager::setUnterkunftsTyp(const std::string &newUnterkunftsTyp)
{
    unterkunftsTyp = newUnterkunftsTyp;
}

void Nachtlager::setRuheLevel(double newRuheLevel)
{
    ruheLevel = newRuheLevel;
}
