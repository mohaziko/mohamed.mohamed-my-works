#ifndef REISEPLAN_H
#define REISEPLAN_H

#include "drachenreise.h"
#include <vector>
#include <string>
#include <memory>

class Reiseplan {

public:
    Reiseplan(std::string start="unbekannt", std::string ziel="unbekannt");
    Reiseplan(const json& j);
    ~Reiseplan();

    json to_json() const;
    void addReise(std::unique_ptr<Drachenreise>reise);
    void addPassagier(std::string name);

    // --------- getter ---------
    std::string getStartOrt() const;
    std::string getZielOrt() const;
    double getGesamtpreis() const;
    int getReiseplanNummer() const;
    std::string& getName();
    vector<Drachenreise*>& getReiseabschnitte();
    vector<std::string>& getPassagiere();
    std::vector<Drachenreise*>getReisen()const;

    bool loescheDrachenreise(int reiseNummer) ;//Aufgabe 9 (a)
    bool loeschePassagier(string name);//Aufgabe 9 (a)

    std::string getPlanBeginn() const;//Aufgabe 10 (f)
    std::string getPlanEnde() const;//Aufgabe 10 (f)

    double berechnePreisFuerPassagier(const std::string& name);
    double berechneGesamtpreis()const;


    void sortiereReisen();
private:
    static int naechsteNummer;
    int reiseplanNummer;
    std::string name;
    std::string startOrt;
    std::string zielOrt;
    std::vector<std::unique_ptr<Drachenreise>> reisen;
    mutable std::vector<Drachenreise*> reisen_rohzeiger_cache;
    vector<std::string> passagierListe;
};

#endif // REISEPLAN_H
