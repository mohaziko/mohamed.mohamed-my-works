#include "ort.h"

Ort::Ort(double l, double b, char t,int n,string Na):Laengengrad(l),Breitengrad(b),type(t),ID(n),Name(Na) {}

Ort::Ort(double l, double b, char t,string Na):Laengengrad(l),Breitengrad(b),type(t),ID(++Nummer),Name(Na) {}

Ort &Ort::operator=(const Ort &other)
{
    if(this != &other)
    {
        this->Laengengrad=other.getLaengengrad();
        this->Breitengrad=other.getBreitengrad();
        this->type=other.getType();
    }
    return *this;
}

Ort::~Ort()
{

}

void Ort::setNachbar(Ort *nachbar)
{
    if(nachbar != nullptr) {
        // Prüfe ob der Nachbar bereits existiert
        for(auto& n : nachbarn) {
            if(n == nachbar) return;
        }
        nachbarn.push_back(nachbar);
    }
}

std::vector<Ort *> &Ort::getNachbarn()
{
    return nachbarn;
}

void Ort::addNachbar(Ort *nachbar)
{
nachbarn.push_back(nachbar);
}





char Ort::getType() const
{
    return type;
}

void Ort::setType(char newType)
{
    type = newType;
}

int Ort::getNummer()
{
    return Nummer;
}

void Ort::setNummer(int newNummer)
{
    Nummer = newNummer;
}

int Ort::getID() const
{
    return ID;
}

string Ort::getName() const
{
    return Name;
}

double Ort::getLaengengrad() const
{
    return Laengengrad;
}

double Ort::getBreitengrad() const
{
    return Breitengrad;
}

void Ort::setLaengengrad(double newLaengengrad)
{
    Laengengrad = newLaengengrad;
}

void Ort::setBreitengrad(double newBreitengrad)
{
    Breitengrad = newBreitengrad;
}

void Ort::setName(const string &newName)
{
    Name = newName;
}

bool Ort::isActive() const
{
    return active;
}

void Ort::setActive(bool state)
{
    active = state;
}

bool Ort::getIsActive() const
{
    return active;
}

void Ort::clearNachbarn()
{
nachbarn.clear();
}
