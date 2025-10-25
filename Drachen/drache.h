    #ifndef DRACHE_H
#define DRACHE_H

#include <string>
#include <vector>
#include "drachenreise.h"       // neue Basisklasse für Reisen
#include "reiseplan.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Drache {
public:
    // ***** Aufgabe 8b: Konstruktor anpassen *****
    //Drache();
    Drache(std::string dN, string mP, string dA,
           double g, double a, double e, double dP);

    Drache(const json& j);
    virtual ~Drache();     // virtual notwendig um mit delete alle Objekte zu zerstören

    json to_json() const;

    // Reiseverwaltung
    void addDrachenreise(Drachenreise* reise);
    void addReiseplan(Reiseplan* plan);
    Reiseplan* findeReiseplan(std::string name);


    // --------- getter ---------
    std::string getDrachenName() const;
    std::string getMeinPlayer() const;
    double getGeschwindigkeit() const;
    double getAusdauer() const;
    double getErholung() const;
    double getDrachenPreis() const;
    virtual std::string getDrachenArt() const = 0;   // macht Drache abstrakt
    vector<Reiseplan*>& getReiseplaene();

    // --------- setter ---------
    void setDrachenName(const std::string& newDrachenName);
    void setMeinPlayer(const std::string& newMeinPlayer);

    bool loescheReiseplan(string name);//Aufgabe 9 (a)

protected:
    std::string drachenName;
    std::string meinPlayer;
    std::string drachenArt;
    double geschwindigkeit;
    double ausdauer;
    double erholung;
    double drachenPreis;

    vector<Reiseplan*> reiseplaene;   // geändert: war früher
};

#endif // DRACHE_H
