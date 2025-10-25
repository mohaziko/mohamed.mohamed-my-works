#ifndef NACHTLAGER_H
#define NACHTLAGER_H

#include "drachenreise.h"

class Nachtlager : public Drachenreise {
public:
    Nachtlager(std::string abf, std::string ank, double p, std::string ort, std::string typ, int ruhe);
    Nachtlager(const json& j);

    json to_json() const override;
    std::string getTyp() const override;

    // --------- getter ---------
    int getLagerID() const;
    std::string getLagerOrt() const;
    std::string getUnterkunftsTyp() const;
    double getRuheLevel() const;


    void setLagerOrt(const std::string &newLagerOrt);

    void setUnterkunftsTyp(const std::string &newUnterkunftsTyp);

    void setRuheLevel(double newRuheLevel);

private:
    static int naechsteLagerID;
    std::string lagerOrt;
    std::string unterkunftsTyp;
    double ruheLevel;
    int lagerID;
};

#endif // NACHTLAGER_H
