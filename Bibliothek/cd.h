#ifndef CD_H
#define CD_H

#include "medien.h"

class CD :virtual public Medien {
protected:
    int spielDauer;

public:
    CD(const std::string& autor, const std::string& titel, const int spielDauer);
    void print() const override;
    std::string typ() const override;
    int getSpielDauer() const;
};

#endif
