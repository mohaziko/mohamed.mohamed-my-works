#include "poi.h"

PoI::PoI(double l, double b, char t, string k, string be,string Na):Ort(l,b,t,Na),Kategorie(k),Bemerkung(be) {}

PoI::PoI(double l, double b, char t, int n, string k, string be,string Na):Ort(l,b,t,n,Na),Kategorie(k),Bemerkung(be)
{

}

PoI &PoI::operator=(const PoI &other)
{
    if(this!=&other)
    {
        this->Laengengrad=other.getLaengengrad();
        this->Breitengrad=other.getBreitengrad();
        this->Kategorie=other.getKategorie();
        this->Bemerkung=other.getBemerkung();
        this->Name=other.getName();
    }
    return *this;
}

string PoI::getKategorie() const
{
    return Kategorie;
}

void PoI::setKategorie(const string &newKategorie)
{
    Kategorie = newKategorie;
}

string PoI::getBemerkung() const
{
    return Bemerkung;
}

void PoI::setBemerkung(const string &newBemerkung)
{
    Bemerkung = newBemerkung;
}
