
#ifndef POI_H
#define POI_H
#include"ort.h"
#include<string>
using namespace std;

class PoI:virtual public Ort
{
public:
    PoI(double l, double b,char t, string k, string be,string Na);
    PoI(double l, double b,char t,int n, string k, string be,string Na);
    PoI& operator=( const PoI& other);
    string getKategorie() const;
    void setKategorie(const string &newKategorie);

    string getBemerkung() const;
    void setBemerkung(const string &newBemerkung);

protected:
    string Kategorie;
    string Bemerkung;
};

#endif // POI_H
