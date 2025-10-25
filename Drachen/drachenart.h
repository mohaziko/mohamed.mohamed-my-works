#ifndef DRACHENART_H
#define DRACHENART_H

#include "drache.h"

class Nachtschatten : public Drache {
public:
    // ***** Aufgabe 8b: zu ändernder Konstruktor ersetzt alten Konstruktor Nachtschatten() *****

    Nachtschatten(std::string dName, std::string mPlayer)
        : Drache(dName, mPlayer, "Nachtschatten", 160.0, 6.5, 1.75,  5100.0) { }


    // Nachtschatten() : Drache() {
    //     drachenArt = "Nachtschatten";
    //     geschwindigkeit = 160.0;
    //     ausdauer = 6.5;
    //     erholung = 1.75;
    //     drachenPreis = 5100.0;
    // }

    Nachtschatten(const json& j) : Drache(j) { }

    std::string getDrachenArt() const { return "Nachtschatten"; }
};


class Tagschatten : public Drache {
public:

    Tagschatten(std::string dName, std::string mPlayer)
        : Drache(dName, mPlayer, "Tagschatten", 170.0,  8.75,2.25, 3500.0) { }
    // Tagschatten() : Drache() {
    //     drachenArt = "Tagschatten";
    //     geschwindigkeit = 170.0;
    //     ausdauer = 8.75;
    //     erholung = 2.25;
    //     drachenPreis = 3500.0;
    // }

    Tagschatten(const json& j) : Drache(j) {}

    std::string getDrachenArt() const override {
        return drachenArt;
    }
};

class ToedlicherNadder : public Drache {
public:
    ToedlicherNadder(std::string dName, std::string mPlayer)
        : Drache(dName, mPlayer, "ToedlicherNadder", 140.0, 9.5 ,1.5, 3750.0) { }

    // ToedlicherNadder() : Drache() {
    //     drachenArt = "ToedlicherNadder";
    //     geschwindigkeit = 140.0;
    //     ausdauer = 9.5;
    //     erholung = 1.5;
    //     drachenPreis = 3750.0;
    // }

    ToedlicherNadder(const json& j) : Drache(j) {}

    std::string getDrachenArt() const override {
        return drachenArt;
    }
};

class Skrill : public Drache {
public:

    Skrill(std::string dName, std::string mPlayer)
        : Drache(dName, mPlayer, "Skrill", 190.0, 7.25,  3.5, 4200.0) { }
    // Skrill() : Drache() {
    //     drachenArt = "Skrill";
    //     geschwindigkeit = 190.0;
    //     ausdauer = 7.25;
    //     erholung = 3.5;
    //     drachenPreis = 4200.0;
    // }

    Skrill(const json& j) : Drache(j) {}

    std::string getDrachenArt() const override {
        return drachenArt;
    }
};

#endif // DRACHENART_H
