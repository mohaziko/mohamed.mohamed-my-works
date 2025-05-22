#include "bibliothek.h"
#include "hoerbuch.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;
Bibliothek* Bibliothek::instance = nullptr;
Bibliothek::Bibliothek() {
instance = this;
}

 Bibliothek::~Bibliothek() {
    // for (auto &medium : bestand) {
    //      bestand.clear();
    //  }
 }



void Bibliothek::mediumAnlegen() {
    string autor, titel;
    int auswahl;
    std::cout << "Art des Mediums:\n"
              << "1: Buch\n"
              << "2: CD\n"
              << "3: Hörbuch\n"
              << "Auswahl: ";
    cin >> auswahl;
   std::cin.ignore();

    cout << "Autor: ";
    /*
     * gibt den maximal möglichen Wert für einen std::streamsize-Typ zurück.
     * Das bedeutet, dass hier praktisch "so viele Zeichen wie möglich" gemeint ist.*/
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, autor);
    cout << "Titel: ";
    getline(cin, titel);


    switch(auswahl) {
    case 1: {
        int seitenzahl;
        std::cout << "Seitenzahl: ";
        std::cin >> seitenzahl;
        bestand.push_back(std::make_shared<Buch>(autor, titel, seitenzahl));
        break;
    }
    case 2: {
        int spielDauer;
        std::cout << "Spieldauer (Min): ";
        std::cin >> spielDauer;
        bestand.push_back(std::make_shared<CD>(autor, titel, spielDauer));
        break;
    }
    case 3: {
        int seitenzahl, spielDauer;
           char hatBooklet;
        std::cout << "Seitenzahl: ";
        std::cin >> seitenzahl;
        std::cout << "Spieldauer (Min): ";
        std::cin >> spielDauer;
        std::cout << "Booklet vorhanden? (j/n): ";
        std::cin >> hatBooklet;

        bestand.push_back(std::make_shared<Hoerbuch>(autor, titel, seitenzahl, spielDauer,(hatBooklet == 'j' || hatBooklet == 'J')));
        break;
    }
    default:
        std::cout << "Ungültige Auswahl\n";
        return;
    }
    cout << "Medium erfolgreich hinzugefügt.\n";
}

void Bibliothek::mediumLoeschen(int id) {



    int index = 0;
    for(const auto& medium : bestand) {
        if(medium->getID() == id) {
            bestand.erase(bestand.begin() + index);
            std::cout << "Medium gelöscht.\n";
            return;
        }
        index++;
    }
    std::cout << "Medium nicht gefunden.\n";
}

void Bibliothek::bestandAnzeigen() const {
    if (bestand.empty()){
        cout<<"Der bestand ist leer.\n";
        return;
    }

    for (const auto& medium : bestand) {
        //medium->print();
        cout<<*medium<<"\n\n";


    }
}
void Bibliothek::kundeAnlegen() {
    std::string nachname;
    std::cout << "Nachname: ";
    std::cin.ignore();
    std::getline(std::cin, nachname);

    kunden.push_back(std::make_shared<Kunde>(nachname));
    std::cout << "Kunde erfolgreich angelegt.\n";
}
void Bibliothek::bestandNachAutorAnzeigen() const {
    std::string autor;
    std::cout << "Autor: ";
    std::cin.ignore();
    std::getline(std::cin, autor);

    for (const auto& medium : bestand) {
        if (medium->getAutor() == autor) {
            cout<<*medium<<"\n\n";
        }
    }
}
void Bibliothek::kundenlisteAnzeigen() const {
    if (kunden.empty()) {
        std::cout << "Keine Kunden vorhanden.\n";
        return;
    }

    for (const auto& kunde : kunden) {
        std::cout << "ID: " << kunde->getId()
        << ", Name: " << kunde->getNachname() << std::endl;
    }
}

string Bibliothek::getKundenName(int kundenId) const
{
    for (const auto& kunde : kunden) {
        if (kunde->getId() == kundenId) {
            return kunde->getNachname();
        }
    }
    return "Unbekannt";
}

std::vector<std::shared_ptr<Medien> > Bibliothek::getBestand() const
{
    return bestand;
}
void Bibliothek::mediumEmpfehlen() const {
    if (bestand.empty()) {
        std::cout << "Keine Medien vorhanden.\n";
        return;
    }


    srand(time(nullptr));  // Initialisiere Zufallsgenerator mit aktuellem Timestamp
    int zufallsIndex = rand() % bestand.size();


    // Zufälliges Medium auswählen
    const auto& empfohlen = bestand[zufallsIndex];
    std::cout << "Empfohlenes Medium:\n" << *empfohlen << std::endl;
}

void Bibliothek::mediumAusleihen() {


    int mediumId, kundenId;

    std::cout << "Medium ID: ";
    std::cin >> mediumId;
    std::cout << "Kunden ID: ";
    std::cin >> kundenId;

    // Suche Medium
    bool mediumGefunden = false;
    bool kundeGefunden = false;

    for(const auto& medium : bestand) {
        if(medium->getID() == mediumId) {
            mediumGefunden = true;

            // Prüfe ob Medium bereits ausgeliehen
            if(medium->istAusgeliehen()) {
                std::cout << "Medium ist bereits ausgeliehen.\n";
                return;
            }

            // Suche Kunde
            for(const auto& kunde : kunden) {
                if(kunde->getId() == kundenId) {
                    kundeGefunden = true;
                    medium->ausleihen(kundenId);
                    std::cout << "Medium erfolgreich ausgeliehen.\n";
                    return;
                }
            }
            break;
        }
    }

    // Fehlermeldungen
    if(!mediumGefunden) {
        std::cout << "Medium nicht gefunden.\n";
    } else if(!kundeGefunden) {
        std::cout << "Kunde nicht gefunden.\n";
    }
}

void Bibliothek::mediumZurueckgeben() {
    int mediumId;
    std::cout << "Medium ID: ";
    std::cin >> mediumId;

    for(const auto& medium : bestand) {
        if(medium->getID() == mediumId) {
            if(!medium->istAusgeliehen()) {
                std::cout << "Medium war nicht ausgeliehen.\n";
                return;
            }

            medium->zurueckgeben();
            std::cout << "Medium erfolgreich zurückgegeben.\n";
            return;
        }
    }

    std::cout << "Medium nicht gefunden.\n";
}

 void Bibliothek::medienSpeichern() const
 {
     ofstream file("C:\\Users\\moham\\OneDrive\\Documents\\lj\\medien.txt");
     if (!file) {
         cerr << "Fehler beim Öffnen der Datei.\n";
            return;
    }
     file << "Bucher\n";
     for (const auto& medium : bestand) {

         if (medium->typ() == "Buch") {
             file << medium->getID() << ";"
                  << medium->getAutor() << ";"
                  << medium->getTitel() << ";"
                  << dynamic_cast<Buch*>(medium.get())->getSeitenzahl() << ";"
                  << medium->istAusgeliehen() << ";"
                  << medium->getKundenId() << "\n";
         }
     }

     // Speichere die CDs
     file << "CDs\n";
     for (const auto& medium : bestand) {
         if (medium->typ() == "CD") {
             file << medium->getID() << ";"
                  << medium->getAutor() << ";"
                  << medium->getTitel() << ";"
                  << dynamic_cast<CD*>(medium.get())->getSpielDauer() << ";"
                  << medium->istAusgeliehen() << ";"
                  << medium->getKundenId() << "\n";
         }
     }

     // Speichere die Hörbücher
     file << "Horbucher\n";
     for (const auto& medium : bestand) {
         if (medium->typ() == "Horbuch") {
             auto hoerbuch = dynamic_cast<Hoerbuch*>(medium.get());
             file << medium->getID() << ";"
                  << medium->getAutor() << ";"
                  << medium->getTitel() << ";"
                  << hoerbuch->getSeitenzahl() << ";"
                  << hoerbuch->getSpielDauer() << ";"
                  << hoerbuch->getHatBooklet() << ";"
                  << medium->istAusgeliehen() << ";"
                  << medium->getKundenId() << "\n";
         }
     }

     // Speichere die Kunden
     file << "Kunden\n";
     for (const auto& kunde : kunden) {
         file << kunde->getId() << ";"
              << kunde->getNachname() << "\n";
     }

     file.close();
     std::cout << "Daten wurden erfolgreich gespeichert.\n";
 }

 void Bibliothek::medienLaden()
 {


    std::ifstream datei("C:\\Users\\moham\\OneDrive\\Documents\\lj\\medien.txt",::std::ios::in);  // Datei öffnen
    if (!datei.is_open()) {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
            return;
    }
   bestand.clear();
    kunden.clear();

   std::string line;
   std::string section;

   while (std::getline(datei, line)) {
       if (line == "Bucher" || line == "CDs" || line == "Horbucher" || line == "Kunden") {
           section = line;
           continue;
       }

       std::stringstream ss(line);
       std::string item;
       std::vector<std::string> items;

       while (std::getline(ss, item, ';')) {
           items.push_back(item);
       }

       if (items.empty()) continue;

       if (section == "Bucher" && items.size() >= 6) {
           auto buch = std::make_shared<Buch>(
               items[1],                    // autor
               items[2],                    // titel
               std::stoi(items[3])         // seitenzahl
               );
           if (std::stoi(items[4])) {      // ist ausgeliehen
               buch->ausleihen(std::stoi(items[5])); // kundenId
           }
           bestand.push_back(buch);
       }
       else if (section == "CDs" && items.size() >= 6) {
           auto cd = std::make_shared<CD>(
               items[1],                    // autor
               items[2],                    // titel
               std::stoi(items[3])         // spielDauer
               );
           if (std::stoi(items[4])) {
               cd->ausleihen(std::stoi(items[5]));
           }
           bestand.push_back(cd);
       }
       else if (section == "Horbucher" && items.size() >= 8) {
           auto hoerbuch = std::make_shared<Hoerbuch>(
               items[1],                    // autor
               items[2],                    // titel
               std::stoi(items[3]),        // seitenzahl
               std::stoi(items[4]),
               std::stoi(items[5])
               );
           if (std::stoi(items[6])) {
               hoerbuch->ausleihen(std::stoi(items[7]));
           }
           bestand.push_back(hoerbuch);
       }
       else if (section == "Kunden" && items.size() >= 2) {
           kunden.push_back(std::make_shared<Kunde>(items[1]));
       }
   }

   datei.close();
   std::cout << "Daten wurden erfolgreich geladen.\n";

 }



