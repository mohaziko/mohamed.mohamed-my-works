#ifndef ADRESSE_H
#define ADRESSE_H
#include"ort.h"
#include<string>
using namespace std;
class Adresse: virtual public Ort
{
public:
    Adresse(double l,double b,char t, string s,int h, int p, string g,string Na);
    Adresse(double l,double b,char t,int n, string s,int h, int p, string g,string Na);
    Adresse& operator=(const Adresse& other);
    string getStrasse() const;
    void setStrasse(string newStrasse);

    int getHausNummer() const;
    void setHausNummer(int newHausNummer);

    int getPLZ() const;
    void setPLZ(int newPLZ);

    string getGemeinde() const;
    void setGemeinde(const string &newGemeinde);

protected:

    string Strasse;
    int HausNummer;
    int PLZ;
    string Gemeinde;

};

#endif // ADRESSE_H
