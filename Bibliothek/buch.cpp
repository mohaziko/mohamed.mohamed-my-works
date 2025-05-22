#include "buch.h"
#include <iomanip>
using namespace std;
Buch::Buch(const std::string& autor, const std::string& titel, int seitenzahl)
    : Medien(autor, titel), seitenzahl(seitenzahl) {}

int Buch::getSeitenzahl() const
{
    return seitenzahl;
}



void Buch::print() const {
    std::cout << std::setw(5) << getID() << " | "
              << std::setw(20) << getAutor() << " | "
              << std::setw(30) << titel << " | "
              << std::setw(5) << getSeitenzahl() << " Seiten | "
              << (ausgeliehen ? "Ausgeliehen an Kunde: " + std::to_string(kundenId)  : "Verfügbar")
              << std::endl;
}

std::string Buch::typ() const {
    return "Buch";
}
