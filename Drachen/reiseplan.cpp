#include "reiseplan.h"
#include "drachenflug.h"
#include "nachtlager.h"

int Reiseplan::naechsteNummer = 1;

Reiseplan::Reiseplan(string start, std::string ziel)
    : reiseplanNummer(naechsteNummer++), startOrt(start), zielOrt(ziel) {
    name = "Reiseplan " + to_string(reiseplanNummer);
}

Reiseplan::Reiseplan(const json& j) {
    reiseplanNummer = j["reiseplanNummer"];
    name = j["name"];
    passagierListe = j["passagiere"];

    if (reiseplanNummer >= naechsteNummer) {
        naechsteNummer = reiseplanNummer + 1;
    }

    for (const auto& r : j["reiseabschnitte"]) {
        std::string typ = r["typ"];
        std::unique_ptr<Drachenreise> rObj = nullptr;
        if (typ == "drachenflug") {
            rObj = std::make_unique<Drachenflug>(r);
        } else if (typ == "nachtlager") {
            rObj = std::make_unique<Nachtlager>(r);
        }
        if (rObj) {
            rObj->setReiseplan(this);  // <<< WICHTIG: setze den Rückverweis
            reisen.push_back(std::move(rObj));
        }
    }
     sortiereReisen();
}

json Reiseplan::to_json() const {
    json j;
    j["reiseplanNummer"] = reiseplanNummer;
    j["passagiere"] = passagierListe;
    j["name"] = name;
    j["reiseabschnitte"] = json::array();

    for (const auto& reise : reisen) {
        j["reiseabschnitte"].push_back(reise->to_json());  // Polymorphe Methode in Drachenflug/Nachtlager
    }

    return j;
}

Reiseplan::~Reiseplan()=default;



void Reiseplan::addReise(std::unique_ptr<Drachenreise> reise) {
    reise->setReiseplan(this);  // Setzt die Rückreferenz: Drachenreise soll ihren Reiseplan kennen
    reisen.push_back((std::move(reise)));
    sortiereReisen();
}


void Reiseplan::addPassagier(string name) {
    passagierListe.push_back(name);
}

string Reiseplan::getStartOrt() const
{
    return startOrt;
}



// --------- getter ---------
int Reiseplan::getReiseplanNummer() const { return reiseplanNummer; }
string& Reiseplan::getName() { return name; }
string Reiseplan::getZielOrt() const { return zielOrt; }
vector<string>& Reiseplan::getPassagiere() { return passagierListe; }

bool Reiseplan::loescheDrachenreise(int reiseNummer)
{
    for (unsigned i = 0; i < reisen.size(); ++i) {
        if(reisen[i]->getReiseNummer()==reiseNummer){
            reisen.erase(reisen.begin()+i);
            return true;
        }
    }
    return false;
}

bool Reiseplan::loeschePassagier(string name)
{
    for (unsigned i = 0; i < passagierListe.size(); ++i) {
        if(passagierListe[i]==name){
            passagierListe.erase(passagierListe.begin()+i);
            return true;
        }
    }
    return false;
}

string Reiseplan::getPlanBeginn() const
{
    if (reisen.empty()) {
        return "unbekannt";  // oder leerer String, wenn keine Reiseabschnitte vorhanden sind
    }
    return reisen.front()->getAbfahrt();
}

string Reiseplan::getPlanEnde() const
{
    if (reisen.empty()) {
        return "unbekannt";
    }
    // Letzte Reise: Ankunftszeit zurückgeben
    // Angenommen, Drachenreise hat Methode getAnkunft() -> std::string
    return reisen.back()->getAnkunft();
}

double Reiseplan::berechnePreisFuerPassagier(const string &name)
{
    double summe = 0.0;
    // Prüfe ob Passagier in Liste
    if (std::find(passagierListe.begin(), passagierListe.end(), name) == passagierListe.end()) {
        return 0.0;  // Passagier nicht auf dieser Reise
    }

    // Für jeden Reiseabschnitt addiere den Preis, der für den Passagier gilt
    for (const auto& reise : reisen) {
        summe += reise->getPreis();
        // Annahme: Drachenreise hat Methode getPreisFuerPassagier(name)
    }
    return summe;
}

double Reiseplan::berechneGesamtpreis() const
{
    double summe = 0.0;
    for (const std::string& passagier : passagierListe) {
        for (const auto& reise : reisen) {
            summe += reise->getPreis();  // gleicher Preis für alle
        }
    }
    return summe;
}

void Reiseplan::sortiereReisen()
{
    std::sort(reisen.begin(), reisen.end(),
              [](const std::unique_ptr<Drachenreise>& a, const std::unique_ptr<Drachenreise>& b) {
                  return *a < *b;
              });
}
vector<Drachenreise*>& Reiseplan::getReiseabschnitte() {
    reisen_rohzeiger_cache.clear(); // unique_ptr: Cache wird neu aufgebaut
    for (auto& r : reisen) {
        reisen_rohzeiger_cache.push_back(r.get());
    }
    return reisen_rohzeiger_cache; // unique_ptr: Rückgabe von Zeigern
 }

std::vector<Drachenreise *> Reiseplan::getReisen() const
{
    std::vector<Drachenreise*> rohzeiger; // ----- unique_ptr: erzeugt extern verwendbare Liste mit rohen Zeigern
    for (const auto& r : reisen) {
        rohzeiger.push_back(r.get());
    }
    return rohzeiger;
}




