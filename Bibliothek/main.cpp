
#include "bibliothek.h"
#include "hoerbuch.h"
#include <iostream>

using namespace std;

int main() {
    Bibliothek bibliothek;


    int wahl;
    do {
             cout << "\n*********************************************************************************\n";
        std::cout << "**********************************Medienverwaltung*******************************\n";
             cout << "*********************************************************************************\n";
        std::cout << "1. Medium anlegen\n";
        std::cout << "2. Medium löschen\n";
        std::cout << "3. Bestand anzeigen\n";
        std::cout << "4. Bestand nach Autor anzeigen\n";
        std::cout << "5. Kunde anlegen\n";
        std::cout << "6. Medium ausleihen\n";
        std::cout << "7. Medium zurückgeben\n";
             cout << "8. Medium speichern" << endl;
             cout << "9. Medium laden" << endl;
        std::cout << "10.Kundenliste anzeigen\n";
        std::cout << "11.Medium empfehlen\n";
              cout << "12. Hörbuch-Booklet als verloren markieren\n";
        std::cout << "0. Beenden\n";
        std::cout << "Ihre Wahl: ";
        std::cin >> wahl;

        switch (wahl) {
        case 1:{
            bibliothek.mediumAnlegen();
        }
            break;
        case 2:{
            int id;
            std::cout << "Medium ID zum Löschen eingeben: ";
                    std::cin >> id;
            bibliothek.mediumLoeschen(id);
        }
            break;
        case 3:{
            bibliothek.bestandAnzeigen();
        }
            break;
        case 4:{
            bibliothek.bestandNachAutorAnzeigen();
        }
            break;
        case 5:{

            bibliothek.kundeAnlegen();
        }
            break;
        case 6:{
            bibliothek.mediumAusleihen();
        }
            break;
        case 7:{
            bibliothek.mediumZurueckgeben();
        }
            break;
        case 8:{
            bibliothek.medienSpeichern();
            cout<<"medium wird gespeichert\n";
        }
            break;
        case 9:{
            bibliothek.medienLaden();
        }break;
        case 10:{
             bibliothek.kundenlisteAnzeigen();
        }
            break;
        case 11:{
            bibliothek.mediumEmpfehlen();
        }break;
        case 12: {
            int id;
            cout << "Hörbuch ID eingeben: ";
            cin >> id;

            bool gefunden = false;
            for(const auto& medium : bibliothek.getBestand()) {
                if(medium->getID() == id) {
                    if(auto hoerbuch = dynamic_cast<Hoerbuch*>(medium.get())) {
                        hoerbuch->bookletVerloren();
                        cout << "Booklet-Status aktualisiert.\n";
                        gefunden = true;
                    } else {
                        cout << "Das ausgewählte Medium ist kein Hörbuch.\n";
                        gefunden = true;
                    }
                    break;
                }
            }

            if (!gefunden) {
                cout << "Medium nicht gefunden.\n";
            }
            break;
        }break;
        case 0:{
            std::cout << "Programm wird beendet.\n";
            cout<<"*******************************************************************************************\n";
            cout<<"******************************************sayonara*****************************************\n";
            cout<<"*******************************************************************************************\n";

        }
            break;
        default:{
            std::cout << "Ungültige Eingabe.\n";
        }break;
        }
    } while (wahl != 0);



    return 0;
}
