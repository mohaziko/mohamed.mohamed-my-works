#include "medien.h"
#include "buch.h"
#include "cd.h"
#include "hoerbuch.h"
#include "kunde.h"
#include <iomanip>
#include"bibliothek.h"

int Medien::nextID = 1;

Medien::Medien(const std::string& autor, const std::string& titel)
    : id(nextID++), autor(autor), titel(titel), ausgeliehen(false) {}

int Medien::getID() const { return id; }
std::string Medien::getAutor() const { return autor; }
std::string Medien::getTitel() const { return titel; }
bool Medien::istAusgeliehen() const { return ausgeliehen; }


void Medien::ausleihen(int kundenId) {
    ausgeliehen = true;
    this->kundenId = kundenId;
}


void Medien::zurueckgeben() {
    ausgeliehen = false;
    //entleiher = "";
     kundenId = -1;
}

int Medien::getKundenId() const
{
    return kundenId ;

}
std::ostream& operator<<(std::ostream& os, const Medien& medium) {


    os << "ID: "<<std::setw(5) << medium.getID() << " | "
       << "Typ: " <<std::setw(5)<< medium.typ() << " | "
       << "Autor: " <<std::setw(5)<< medium.getAutor() << " | "
       << "Titel: " <<std::setw(5)<< medium.getTitel() << " | "
       << "Status: " << (medium.istAusgeliehen() ? "Ausgeliehen" : "Verfugbar");

    if (medium.istAusgeliehen()) {

        os << " (Kunden-ID: " << medium.getKundenId() ;
        if (Bibliothek::instance) {
            os << ", Name: " << Bibliothek::instance->getKundenName(medium.getKundenId());
        }
        os << ")";
    }

    // Typüberprüfung und spezifische Ausgaben
    if (const Buch* buch = dynamic_cast<const Buch*>(&medium)) {
        os << "\nSeitenzahl: " << buch->getSeitenzahl();
    }

    if (const CD* cd = dynamic_cast<const CD*>(&medium)) {
        os << "\nSpieldauer: " << cd->getSpielDauer() << " Minuten";
    }

    if (const Hoerbuch* hoerbuch = dynamic_cast<const Hoerbuch*>(&medium)) {
        // Hörbuch erbt bereits von Buch und CD, also wurden Seitenzahl und Spieldauer
        // schon durch die obigen Überprüfungen ausgegeben
         os << "\nBooklet vorhanden: " << (hoerbuch->getHatBooklet() ? "Ja" : "Nein");
    }


    return os;
}
Medien::operator std::string() const {
    return "ID: " + std::to_string(id) + ", Autor: " + autor + ", Titel: " + titel;
}
