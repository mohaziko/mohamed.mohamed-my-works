#include "DragonPOILayer.h"
#include "drachenflug.h"
#include "filmstudio.h"
#include "nachtlager.h"
#include <iostream>
#include <QMessageBox>

DragonPOILayer::DragonPOILayer(Filmstudio* studio) : studio(studio) {}

// Gibt eine Teilmenge der POIs zurück, die im übergebenen Reiseplan vorkommen
map<string, POI*> DragonPOILayer::getPOIsFuerReiseplan(Reiseplan* plan) {

    // hier sollen die POIs eines Reiseplans in eine map gespeichert werden
    map<string, POI*> result;
    const auto& abschnitte = plan->getReiseabschnitte();

    for (auto* abschnitt : abschnitte) {
        POI* poi = findePOIAusReiseabschnitt(abschnitt);
        if (poi) {
            std::string name = poi->getName();
            result[name] = poi;
        }
    }

    return result;  // Rückgabe der gefundenen POIs
}

// Sucht einen POI mit passendem Namen aus der globalen POI-Liste
POI* DragonPOILayer::findePOIByName(const std::string& name) {
    const auto& pois = studio->getPoiMap();  // Alle POIs aus dem Filmtudio

    for (const auto& [key, poi] : pois) {
        if (poi->getName() == name) {
            return poi;
        }
    }

    return nullptr;
}

// Allgemeine Hilfsmethode, die einen Auswahl-Dialog mit Optionen anzeigt
QString DragonPOILayer::zeigePoiAuswahlDialog(QWidget* parent, const QString& titel, const QString& labelText,
                                              const QStringList& optionen, bool allowCustom) {
    if (allowCustom) {
        bool ok;
        QString eingabe = QInputDialog::getItem(parent, titel, labelText, optionen, 0, true, &ok);
        if (ok && !eingabe.isEmpty())
            return eingabe;
    } else {
        QString auswahl = QInputDialog::getItem(parent, titel, labelText, optionen, 0, false);
        if (!auswahl.isEmpty())
            return auswahl;
    }
    return QString();
}

// Öffnet einen Dialog zur Auswahl eines Ziel-POIs (z. B. für einen Flug)
QString DragonPOILayer::wähleZielPoi(QWidget* parent) {
    QStringList alleZiele;
    for (const auto& [_, poi] : studio->getPoiMap()) {
        alleZiele << QString::fromStdString(poi->getName());  // Alle POI-Namen in Liste sammeln
    }

    // Verwende die Hilfsmethode für den Auswahl-Dialog
    return zeigePoiAuswahlDialog(parent, "Flug", "Ziel auswählen:", alleZiele, false);
}

// Öffnet einen Dialog zur Auswahl eines Nachtlager-Ortes + zugehörigem Typ (z. B. Höhle)
std::pair<QString, QString> DragonPOILayer::wähleNachtlagerOrtUndTyp(QWidget* parent) {
    QStringList ortNamen;
    QMap<QString, QString> nameToTyp;

    // Sammle nur POIs vom Typ Höhle, Baumkrone oder Bergplateau
    for (const auto& [_, poi] : studio->getPoiMap()) {
        const std::string& typ = poi->getTyp();
        if (typ == "Höhle" || typ == "Baumkrone" || typ == "Bergplateau") {
            QString name = QString::fromStdString(poi->getName());
            ortNamen << name;
            nameToTyp[name] = QString::fromStdString(typ);
        }
    }

    // Auswahl mit Hilfsmethode
    QString ausgewählt = zeigePoiAuswahlDialog(parent, "Nachtlager", "Ort auswählen:", ortNamen, false);
    if (ausgewählt.isEmpty()) return {};  // Abgebrochen

    return { ausgewählt, nameToTyp[ausgewählt] };  // Rückgabe: Name und zugehöriger Typ
}

// Fügt einen neuen POI zur POI-Sammlung hinzu (z. B. beim Bearbeiten)
void DragonPOILayer::neuenPoiEintragen(POI* neuerPoi) {
    if (neuerPoi) {
        studio->addPoi(neuerPoi);
    }
}

POI* DragonPOILayer::findePOIAusReiseabschnitt(Drachenreise* abschnitt) {
    if (auto* flug = dynamic_cast<Drachenflug*>(abschnitt)) {
        // Wenn es ein Drachenflug ist, suche nach dem Ziel-POI
        return findePOIByName(flug->getZiel());
    } else if (auto* lager = dynamic_cast<Nachtlager*>(abschnitt)) {
        // Wenn es ein Nachtlager ist, suche nach dem Lager-POI
        return findePOIByName(lager->getLagerOrt());
    }
    return nullptr;  // Kein POI gefunden
}


