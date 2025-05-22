#ifndef BUCH_H
#define BUCH_H

#include "medien.h"

class Buch :virtual public Medien {
protected:
    int seitenzahl;
public:
    Buch(const std::string& autor, const std::string& titel, int seitenzahl);
    int getSeitenzahl() const;
    void print() const override;
    std::string typ() const override;
};

#endif
