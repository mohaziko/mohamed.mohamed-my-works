#include "hoerbuch.h"
#include <iomanip>

Hoerbuch::Hoerbuch(const std::string &autor, const std::string &titel, int seitenzahl, int spielDauer, bool mitBooklet): Medien(autor, titel), Buch(autor, titel, seitenzahl),
    CD(autor, titel, spielDauer),hatBooklet(mitBooklet) {}


void Hoerbuch::print() const {

    std::cout << std::setw(5) << id << " | "
              << std::setw(20) << autor << " | "
              << std::setw(30) << titel << " | "


              << (ausgeliehen ? "Ausgeliehen an Kunde: " + std::to_string(kundenId) : "Verfügbar")
              << std::endl;
    std::cout << "\nSeitenzahl im Booklet: " << getSeitenzahl()
              << "\nSpieldauer: " << getSpielDauer() << " Minuten"
              << "\nBooklet vorhanden: " << (hatBooklet ? "Ja" : "Nein");
}

std::string Hoerbuch::typ() const { return "Horbuch"; }

void Hoerbuch::setHatBooklet(bool newHatBooklet)
{
    hatBooklet = newHatBooklet;
}

bool Hoerbuch::getHatBooklet() const
{
    return hatBooklet;
}

void Hoerbuch::bookletVerloren()
{
    hatBooklet = false;
    std::cout << "Booklet wurde als verloren markiert.\n";
}
