#include "adresse.h"

Adresse::Adresse(double l, double b, char t, string s, int h, int p, string g,string Na):Ort(l,b,t,Na),Strasse(s),HausNummer(h),PLZ(p),Gemeinde(g) {}

Adresse::Adresse(double l, double b, char t, int n, string s, int h, int p, string g,string Na):Ort(l,b,t,n,Na),Strasse(s),HausNummer(h),PLZ(p),Gemeinde(g)
{

}

Adresse &Adresse::operator=(const Adresse &other)
{
    if(this!=&other)
    {
        this->Laengengrad=other.getLaengengrad();
        this->Breitengrad=other.getBreitengrad();
        this->HausNummer=other.getHausNummer();
        this->Strasse=other.getStrasse();
        this->PLZ=other.getPLZ();
        this->Gemeinde=other.getGemeinde();
        this->Name=other.getName();

    }
    return *this;
}

string Adresse::getStrasse() const
{
    return Strasse;
}

void Adresse::setStrasse(string newStrasse)
{
    Strasse = newStrasse;
}

int Adresse::getHausNummer() const
{
    return HausNummer;
}

void Adresse::setHausNummer(int newHausNummer)
{
    HausNummer = newHausNummer;
}

int Adresse::getPLZ() const
{
    return PLZ;
}

void Adresse::setPLZ(int newPLZ)
{
    PLZ = newPLZ;
}

string Adresse::getGemeinde() const
{
    return Gemeinde;
}

void Adresse::setGemeinde(const string &newGemeinde)
{
    Gemeinde = newGemeinde;
}
