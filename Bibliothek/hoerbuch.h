#ifndef HOERBUCH_H
#define HOERBUCH_H

#include "buch.h"
#include "cd.h"


class Hoerbuch:virtual public Buch,virtual public CD
{
public:
    Hoerbuch(const std::string& autor, const std::string& titel,
             int seitenzahl, int spielDauer,bool mitBooklet = true);
    void print() const override;
    std::string typ() const override;
    void setHatBooklet(bool newHatBooklet);
    bool getHatBooklet() const;
    void bookletVerloren();
private:
    bool hatBooklet;

};

#endif // HOERBUCH_H
