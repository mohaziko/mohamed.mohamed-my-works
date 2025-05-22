#include "kunde.h"
int Kunde::nextID = 1;
Kunde::Kunde(const std::string &nachname):id(nextID++), nachname(nachname) {}

int Kunde::getId() const
{
    return id;
}

std::string Kunde::getNachname() const
{
    return nachname;
}
