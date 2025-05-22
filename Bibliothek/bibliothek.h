#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include "kunde.h"
#include "medien.h"
#include <memory>
#include <vector>
#include <string>

class Bibliothek {
public:
    Bibliothek();
    ~Bibliothek();

    void mediumAnlegen();
    void mediumLoeschen(int id);
    void bestandAnzeigen() const;
    void bestandNachAutorAnzeigen() const;
    void mediumEmpfehlen() const;
    void mediumAusleihen();
    void mediumZurueckgeben();
    void medienSpeichern() const;
    void medienLaden();
    void kundeAnlegen();
    void kundenlisteAnzeigen() const;

   static Bibliothek* instance;

    std::string getKundenName(int kundenId) const;
    std::vector<std::shared_ptr<Medien> > getBestand() const;

private:
    std::vector<std::shared_ptr<Medien>> bestand;
    std::vector<std::shared_ptr<Kunde>> kunden;

};

#endif
