#include "cd.h"
#include <iomanip>

int CD::getSpielDauer() const
{
    return spielDauer;
}

CD::CD(const std::string& autor, const std::string& titel, const int spielDauer)
    : Medien(autor, titel), spielDauer(spielDauer) {}




void CD::print() const {
    std::cout << std::setw(5) << id << " | "
              << std::setw(20) << autor << " | "
              << std::setw(30) << titel << " | "
              << std::setw(10) << spielDauer << " | "
              << (ausgeliehen ? "Ausgeliehen an: " + std::to_string(kundenId) : "Verfügbar")
              << std::endl;
}



std::string CD::typ() const {
    return "CD";
}
